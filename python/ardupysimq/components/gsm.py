from . import SerialComponent
import re
import arrow


class GSM(SerialComponent):
    """
    GSM module (with the AT protocol)
    """
    def __init__(self, rx, tx, position):
        super(GSM, self).__init__(7, 27, position, "GSM", [rx, tx])
        self.messages = []
        self.sendMessage = {"waiting": False, "to": "", "message": "-"}
        self.strength = 0

    def draw(self):
        self.win.addstr(1, 0, "Messages: " + str(len(self.messages)))
        self.win.addstr(2, 0, "Press m to add a message")
        self.win.addstr(3, 0, "Send to: " + self.sendMessage["to"])
        self.win.addstr(4, 0, "Message:")
        self.win.addstr(5, 0, self.sendMessage["message"])
        self.draw_name()
        self.redraw = False

    def _control(self, user, montant):
        return str(user + int(round(montant)) + 23).rjust(3, '0')

    def appendOK(self):
        self.append("OK\n")

    def tx(self, pin, m):
        if pin == self.pins["ss"][1]:
            super(GSM, self).tx(m)
        with open("gsm-log.txt", "a") as f:
            f.write("\n")
            f.write(self.bufTX)
            f.write("\n*****************\n")
            f.close()
        if "BEGIN" in m:
            self.append("+SIND: 4\r")
        elif "AT\r" in self.bufTX:
            self.appendOK()
            self.bufTX = ""
        # Text mode
        elif "AT+CMGF=1\r" in self.bufTX:
            self.appendOK()
            self.bufTX = ""
        # Signal strength
        elif "CSQ" in self.bufTX:
            self.append("+CSQ: 14,99\n\nOK\r")
            self.bufTX = ""
        # Read message
        elif "CMGR" in self.bufTX:
            r = re.findall("\+CMGR=(\d+)", self.bufTX)
            if len(r) == 0:
                return
            self.bufTX = ""
            i = int(r[0])
            for msg in self.messages:
                if msg["id"] == i:
                    self.append('+CMGR: "{status}",0,"{sender}","{date}"\r\n{message}\n'.format(**msg))
                    self.appendOK()
                    break
        # Clock
        elif "AT+CCLK?" in self.bufTX:
            self.append("+CCLK: \"{}\"\n\n".format(arrow.now().format("MM/DD/YY,HH:mm:ss+00")))
            self.appendOK()
            self.bufTX = ""
        # Delete message
        elif "CMGD" in self.bufTX:
            r = re.findall('\+CMGD=(\d+)',self.bufTX)
            if len(r) == 0:
                return
            self.bufTX = ""
            self.messages = [msg for msg in self.messages if msg["id"] != int(r[0])]
            self.appendOK()
            self.redraw = True
        # List all messages
        elif "CMGL=\"ALL\"" in self.bufTX:
            self.bufTX = ""
            for msg in self.messages:
                self.append('+CMGL: {id},0,"{status}","{sender}","{date}"\r\n{message}\n'.format(**msg))
            self.appendOK()
            self.redraw = True
        # Send message
        elif "CMGS" in self.bufTX and "\"\r" in self.bufTX:
            r = re.findall('CMGS=\"(\d+)\"', self.bufTX)
            self.sendMessage["to"] = r[0]
            self.bufTX = ""
            self.sendMessage["waiting"] = True
            self.append(">")
            self.redraw = True
        elif self.sendMessage["waiting"] and "\r" in self.bufTX:
            self.sendMessage["message"] = self.bufTX.replace("26\r", "")
            self.append("OK")
            self.sendMessage["waiting"] = False
            self.redraw = True

    # Add message
    def addMessage(self, m):
        self.messages.append({
            "id": len(self.messages),
            "status": "REC UNREAD",
            "sender": "+41760000000",
            "date": "11/01/31,17:34:03+04",
            "message": m})
        self.redraw = True
