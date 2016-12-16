# TextArt
A C++ library and program meant for displaying coloured images, videos, and documents in the terminal.

COMPILATION:
cmake .
make

INSTALL
sudo ln -s `pwd`/draw /usr/bin/draw

Example usage:
![sunflower](https://raw.githubusercontent.com/Skilld18/TextArt/master/sunflowers.jpg)
can be displayed in the terminal like this:
draw sunflower.jpg -par

![sunflower-screenshot](https://raw.githubusercontent.com/Skilld18/TextArt/master/sunflowers-screenshot.png)

Flags
-image, -doc, -dir, -txt        force filetype
manually force the program to interpret a file a certain way. This is especially useful since the file type
detection is somewhat lacking

-par        preserve aspect ratio

-i      interactive move
when this mode is on key presses trigger live updates
-/+ zoom in and out
h,j,k,l pan
<,> adjust pan speed
f,b forward/back frames(back is not implemented for video)

