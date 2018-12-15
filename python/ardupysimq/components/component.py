import curses


class Component(object):
    """
    Generic component
    """
    def __init__(self, h, w, position, name):
        self.x, self.y = position
        self.win = curses.newwin(h + 1, w, self.y, self.x)
        self.win.immedok(True)
        self.box = curses.newwin(h, w, self.y + 1, self.x)
        self.box.immedok(True)
        self.name = name
        self.pins = {"digital": [], "analog": [], "ss": None}
        self.redraw = False

    def check_analog(self, pin):
        if pin not in self.pins["analog"]:
            exit(1)

    def get_analog(self, pin):
        self.check_analog(pin)

    def write_analog(self, pin, value):
        self.check_analog(pin)

    def tx(self, pin, m):
        return

    def draw(self):
        self.win.clear()
        self.box.clear()
        self.box.box()
        self.draw_name()
        self.redraw = False

    def draw_name(self):
        self.win.addstr(0, 0, self.name, curses.A_BOLD)
