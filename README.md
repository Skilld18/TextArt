use pdftoppm to convert docs 
use pdftotext to get text
use pdfimages to pull images

#to build
mkdir build
cd build
cmake ..
make
#to install
sudo cmake -P cmake_install.cmake
