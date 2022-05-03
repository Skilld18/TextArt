use pdftoppm to convert docs 
use pdftotext to get text
use pdfimages to pull images

#use ffmpeg to convert video to images
ffmpeg -i "file" thumb%04d.png -hide_banner
#and a bash loop to play it
for i in *.png; do tput cup 0 0; draw $i; done

#to build
mkdir build
cd build
cmake ..
make
#to install
sudo cmake -P cmake_install.cmake


