from . import SerialComponent
import random
import string


class RFID(SerialComponent):
    """
    RFID component
    """
    def __init__(self, pin_enable, pin_out, position):
        super(RFID, self).__init__(4, 25, position, "RFID", [pin_out, 255])
        self.status = False
        self.pins["digital"].append(pin_enable)

    def draw(self):
        self.win.addstr(1, 0, "Status: {}".format(self.status))
        self.win.addstr(2, 0, "Press R to approach a tag")
        self.win.addstr(3, 0, "Queue size: {}".format(self.size()))
        self.draw_name()
        self.redraw = False

    def enable(self):
        self.status = True

    def disable(self):
        self.status = False

    def tx(self, pin, s):
        self.redraw = True
        if not s:  # !
            self.enable()
        else:
            self.disable()

    def addTag(self, tag):
        # Random noise
        # for c in range(0, 10):
        #     self.append(random.choice(string.ascii_uppercase))
        for c in "\n{}\r".format(tag):
            self.append(c)
        self.redraw = True
