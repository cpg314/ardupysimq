from . import Component


class Relay(Component):
    """
    Relay (on a digital pin)
    """

    def __init__(self, pin, position):
        super(Relay, self).__init__(3, 9, position, "Relay")
        self.status = False
        self.pins["digital"].append(pin)

    def draw(self):
        super(Relay, self).draw()
        self.win.addstr(2, 2, "-----" if self.status else "--/--")

    def tx(self, pin, s):
        if self.status != s:
            self.status = s
            self.redraw = True
