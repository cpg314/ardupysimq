#!/usr/bin/env python3
import curses
import signal
import sys
import time
import zmq
import re
# from threading import Timer
from .process_messages import process_messages


# Global variables
screen = None
socket = None
drawn = False


# Signals
def close():
    global screen
    curses.nocbreak()
    screen.keypad(0)
    curses.echo()
    curses.endwin()


def signal_handler(signal, frame):
    close()
    sys.exit(0)


def extract_ports(filename):
    """
    Extract port from C header file
    """
    ports = {}
    with open(filename, "r") as f:
        c = f.read()
        for m in re.findall("#define (.*?) (\d+)", c):
            ports[m[0]] = int(m[1])
    return ports


def setup():
    global socket, screen
    # ZMQ
    context = zmq.Context()
    socket = context.socket(zmq.PAIR)
    socket.bind("tcp://*:55")
    # Curses
    screen = curses.initscr()
    curses.start_color()
    curses.noecho()
    curses.cbreak()
    curses.curs_set(0)
    screen.keypad(1)
    screen.nodelay(True)
    screen.immedok(True)
    signal.signal(signal.SIGINT, signal_handler)


def draw(components):
    global screen
    screen.clear()
    screen.border(0)
    for _, c in components.items():
        c.draw()


def loop(process_input, components):
    global screen, socket, drawn
    process_messages(socket, components)
    if not drawn:
        redraw = True
        drawn = True
    else:
        redraw = any([c.redraw for _, c in components.items()])
    # WDT
    if "wdt" in components and not components["wdt"].check():
        close()
        exit("Killed by WDT")
    # Draw
    if redraw:
        draw(components)
        redraw = False
    process_input(screen.getch())
    time.sleep(0.005)
