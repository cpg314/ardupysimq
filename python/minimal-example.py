from ardupysimq.simulator import extract_ports, setup, loop
from ardupysimq.components import LCD

components = {}

def process_input(c):
    global components
    return

def main():
    global components
    ports = extract_ports("../cpp/src/config.h")
    setup()
    # Define components
    components = {
        "lcd": LCD(ports["LCD_PIN"], (2, 1))
    }
    while True:
        loop(process_input, components)

if __name__ == "__main__":
    main()
