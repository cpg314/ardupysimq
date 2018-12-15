from ardupysimq.simulator import extract_ports, setup, loop
from ardupysimq.components import Button, Buzzer, Sensor, GSM, LCD, Relay, RFID, WDT
import random
import string

components = {}

def process_input(c):
    global components
    if c == ord('x'):
        components["button"].switch()
    elif c == ord('m'):
        components["gsm"].addMessage("Test")
    elif c == ord('r'):
        # components["rfid"].addTag("F5F0A84EE")
        tag = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(9))
        components["rfid"].addTag("\n{}\r".format(tag))

def main():
    global components
    ports = extract_ports("../cpp/src/config.h")    
    setup()
    # Define components
    components = {
        "lcd": LCD(ports["LCD_PIN"], (2, 1)),
        "wdt": WDT((29, 7)),
        "button": Button(ports["BUTTON_PIN"], (26, 1)),
        "buzzer": Buzzer(ports["BUZZER_PIN"]),
        "sensor": Sensor(ports["SENSOR_PIN"], (2, 7)),
        "gsm": GSM(ports["GSM_PIN_RX"], ports["GSM_PIN_TX"], (40, 1)),
        "relay": Relay(ports["RELAY_PIN"], (15, 7)),
        "rfid": RFID(ports["RFID_PIN_ENABLE"], ports["RFID_PIN_OUT"], (2, 12))
    }
    while True:
        loop(process_input, components)
        components["sensor"].update()

if __name__ == "__main__":
    main()
