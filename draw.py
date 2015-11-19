#!/usr/bin/python

import image 
import sys 
from PIL import Image 

class _Getch:
    """Gets a single character from standard input.  Does not echo to the screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()


getch = _Getch()


if len(sys.argv) < 2:
    print("This program needs a image file as an argument")
    exit()

im = Image.open(sys.argv[1]) 
horizontal = 1 
vertical = 1 
x = 0 
y = 0

while True:
    xBox1 = (im.size[0]/horizontal) * x
    xBox2 = (im.size[0]/horizontal) * (x+1)
    yBox1 = (im.size[1]/vertical) * y
    yBox2 = (im.size[1]/vertical) * (y+1)
    

    
    image.draw(im.crop((xBox1, yBox1, xBox2, yBox2)))
    
    userInput = getch()
    if userInput == 'q':
        exit()

    if userInput == '-':
        horizontal = max(horizontal-1,1)
        vertical = max(vertical-1,1)
    if userInput == '+':
        horizontal = horizontal + 1
        vertical = vertical + 1

    if userInput == 'j':
        y = min(y+1,vertical-1)
    if userInput == 'k':
        y = max(y - 1,0)
    if userInput == 'h':
        x = max(x - 1,0)
    if userInput == 'l':
        x = min(x + 1,horizontal -1)

