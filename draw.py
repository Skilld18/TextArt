#!/usr/bin/python

import image
import sys
from PIL import Image

if len(sys.argv) < 2:
    print("This program needs a image file as an argument")
    exit()

im = Image.open(sys.argv[1])
image.draw(im)
