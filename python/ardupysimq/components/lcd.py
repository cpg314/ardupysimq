from . import SerialComponent


class LCD(SerialComponent):
    """
    Serial LCD (e.g. Sparkfun SerLCD)
    """
    def __init__(self, pin, position):
        super(LCD, self).__init__(4, 20, position, "LCD", [255, pin])
        self.backlight = False
        self.lines = ["", ""]
        self.received = []

    def tx(self, pin, s):
        self.received.append(s)
        if self.received[-2:] == ["124", "140"]:  # Backlight on
            self.backlight = True
            self.received = []
            self.redraw = True
        elif self.received[-2:] == ["124", "128"]:  # Backlight off
            self.backlight = False
            self.received = []
            self.redraw = True
        elif self.received[-3:-1] == ["254", "128"]:  # Set first line
            self.lines[0] = self.received[-1]
            self.received = []
            self.redraw = True
        elif self.received[-3:-1] == ["254", "192"]:  # Set second line
            self.lines[1] = self.received[-1]
            self.received = []
            self.redraw = True
        elif self.received[-2:] == ["254", "1"]:
            self.lines = ["", ""]
            self.received = []
            self.redraw = True

    def draw(self):
        super(LCD, self).draw()
        if self.backlight:
            self.win.addstr(0, 5, "(backlit)")
            for i in range(0, 2):
                self.win.addstr(2 + i, 2, self.lines[i])
