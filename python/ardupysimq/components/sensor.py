from . import Component
import random
import time


class Sensor(Component):
    """
    Analog sensor
    """
    def __init__(self, pin, position):
        super(Sensor, self).__init__(3, 9, position, "Sensor")
        self.value = 0
        self.lastUpdate = -100
        self.pins["analog"].append(pin)

    def get_analog(self, pin):
        super(Sensor, self).get_analog(pin)
        return str(self.value)

    def draw(self):
        super(Sensor, self).draw()
        self.win.addstr(2, 2, str(self.value))

    def update(self):
        if time.time() - self.lastUpdate > 3:
            self.value = random.randint(0, 800)
            self.lastUpdate = time.time()
            self.redraw = True
