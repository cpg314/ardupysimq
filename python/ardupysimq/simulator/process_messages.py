import zmq


class MessageProcessor(object):
    def process_message(self, m, socket, components):
        pass


class MessageProcessorSerial(MessageProcessor):
    def process_message(self, m, socket, components):
        """
        Message format:
        SSPINRX-pin-AVAILABLE (read)
        SSPINRX-pin-FLUSH (read)
        SSPINRX-pin-READ (read)
        SSPINTX-pin-message (write)
        """
        m = m.replace("SSPIN", "")
        m = m.split("-")
        pin_type = (0 if m[0] == "RX" else 1)
        pin = int(m[1])
        message = m[2]
        for _, c in components.items():
            if c.pins["ss"] is not None and pin == c.pins["ss"][pin_type]:
                # Read
                if pin_type == 0:
                    r = c.rx(message)
                    # if type(r)==bool:
                    #     return r
                    # elif r!=None:
                    if r is not None:
                        socket.send_string(r)
                # Write
                else:
                    c.tx(pin, message)


class MessageProcessorDigital(MessageProcessor):
    def process_message(self, m, socket, components):
        """
        Message format:
        DPINi-message
        """
        s = m.split("-")
        pin = int(s[0].replace("DPIN", ''))
        # Write
        if s[1] == "1" or s[1] == "0":
            msg = (s[1] == "1")
            for _, c in components.items():
                if pin in c.pins["digital"]:
                    c.tx(pin, msg)
        # Read
        else:
            for _, c in components.items():
                if pin in c.pins["digital"]:
                    socket.send_string(c.rx(pin))


class MessageProcessorAnalog(MessageProcessor):
    def process_message(self, m, socket, components):
        """
        Message format:
        APINi (read)
        APINi-value (write)
        """
        m = m.replace("APIN", "").split("-")
        pin = int(m[0])
        # print pin,m,len(m)
        for _, c in components.items():
            if pin in c.pins["analog"]:
                # Read
                if len(m) == 1:
                    socket.send_string(str(c.get_analog(pin)))
                # Write
                else:
                    c.write_analog(pin, int(m[1]))


def process_messages(socket, components):
    try:
        m = socket.recv(flags=zmq.NOBLOCK).decode("utf-8")
        # with open("messages.txt", "a") as f:
        #     f.write(m + "\n")
        # Serial pins
        if "SSPIN" in m:
            MessageProcessorSerial().process_message(m, socket, components)
        # Digital
        elif "DPIN" in m:
            MessageProcessorDigital().process_message(m, socket, components)
        # Analog
        elif "APIN" in m:
            MessageProcessorAnalog().process_message(m, socket, components)
        elif "WDT" in m:
            if "wdt" in components.keys():
                return components["wdt"].process_message(m)
        return False
    except zmq.ZMQError as e:
        return False
