#!/usr/bin/python
import os
import sys

from PIL import Image
    
def draw(im):
   #get terminal size
   rows, columns = os.popen('stty size', 'r').read().split()
   size = (int(rows), int(columns))
   #Have to rotate img tdue to iterator setup
   im = im.rotate(90)
   #*2 deals with the fact that unicode blockchars are 2x1 rectables
   im = im.resize((im.size[0],im.size[1]*2))
   #thumbnail scales while perserving aspect ratio
   im.thumbnail(size)

   for x in range(im.size[0]):
      for y in range(im.size[1]-1,-1,-1):
         pixelColour = im.getpixel(((x,y)))
         #escape code for rgb colour + red + green + blue + unicode box character + escape code for rgb colour
         sys.stdout.write(("\x1b[38;2;" + str(pixelColour[0]) + ";" + str(pixelColour[1]) + ";" + str(pixelColour[2]) + "m" + u'\u2588' + "\x1b[0m").encode('utf-8'))
      sys.stdout.write("\n")
