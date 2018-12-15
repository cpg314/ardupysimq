from . import Component
import time


class WDT(Component):
    """
    Watchdog timer
    """

    def __init__(self, position):
        super(WDT, self).__init__(3, 9, position, "WDT")
        self.enabled = False
        self.reset()
        self.interval = 4

    def draw(self):
        self.draw_name()
        self.win.addstr(1, 0, "ON ({}s)".format(self.interval) if self.enabled else "OFF")
        self.redraw = False

    def process_message(self, m):
        if "RST" in m:
            self.reset()
        elif "ON" in m:
            self.enable(int(m.split(' ')[2]))
            self.redraw = True
        elif "OFF" in m:
            self.disable(self)
            self.redraw = True

    def enable(self, interval):
        self.interval = interval
        self.reset()
        self.enabled = True

    def disable(self):
        self.enabled = False

    def reset(self):
        self.last_reset = time.time()

    def check(self):
        if not self.enabled:
            return True
        return time.time() - self.last_reset < self.interval
