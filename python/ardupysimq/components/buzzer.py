from . import Component
import subprocess
import os


class Buzzer(Component):
    """
    Buzzer
    """

    def __init__(self, pin):
        super(Buzzer, self).__init__(3, 7, (0, 0), "Buzzer")
        self.pins["analog"].append(pin)
        self.p = None

    def write_analog(self, pin, value):
        super(Buzzer, self).write_analog(pin, value)
        if value == 0:
            self.p.terminate()
        else:
            self.p = subprocess.Popen(["play", "-n", "synth", "1000", "sin", str(value)], stdout=open(os.devnull, 'wb'), stderr=open(os.devnull, 'wb'))

    def draw(self):
        return

    def rx(self, pin):
        return
