#include <draw/draw.h>
#include <iostream>
#include <fstream>


int main(int argc, const char *argv[])
{
    if ( argc > 1 )
    {
      return draw(argv[1]);
   }
   else
   {
       std::ofstream myfile;
       myfile.open ("/tmp/draw.txt");
       for (std::string line; std::getline(std::cin, line);) {
         myfile << line << "\n";
       }
       myfile.close();
       return draw("/tmp/draw.txt");
   }
}
