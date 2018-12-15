from . import Component
from queue import Queue


class SerialComponent(Component):
    """
    Generic serial component
    """
    def __init__(self, h, w, position, name, pins):
        super(SerialComponent, self).__init__(h, w, position, name)
        self.pins["ss"] = pins
        self.buf = Queue()
        self.bufTX = ""

    def flush(self):
        self.buf = Queue()

    def read(self):
        return self.buf.get()

    def size(self):
        return self.buf.qsize()

    def append(self, c):
        for cc in c:
            self.buf.put(cc)

    def tx(self, m):
        self.bufTX += m

    def rx(self, message):
        if message == "AVAILABLE":
            return str(self.size())
        elif message == "READ":
            return self.read()
        elif message == "FLUSH":
            self.flush()
            self.redraw = True
