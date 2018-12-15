from . import Component


class Button(Component):
    """
    Simple on/off button
    """
    def __init__(self, pin, position):
        super(Button, self).__init__(3, 7, position, "Button")
        self.status = False
        self.pins["digital"].append(pin)

    def draw(self):
        super(Button, self).draw()
        if self.status:
            self.win.addstr(2, 3, "X")

    def rx(self, pin):
        return ("HIGH" if self.status else "LOW")

    def switch(self):
        self.status = not self.status
        self.redraw = True
