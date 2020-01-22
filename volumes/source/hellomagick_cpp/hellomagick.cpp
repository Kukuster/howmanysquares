#include <iostream>
#include <stdlib.h>
//#include <cstdlib>
//sudo apt install graphicsmagick-libmagick-dev-compat libjpeg62    &&    ldconfig
#include <Magick++.h>
//using namespace std;
using namespace Magick;


int main(int argc, char const *argv[], char *env[])
{

    std::cout << "Hello world!!!" << std::endl;
    std::string HMSBIN_INPUT;
    std::string HMSBIN_OUTPUT;
    try{
        HMSBIN_INPUT = getenv("HMSBIN_INPUT");
        HMSBIN_OUTPUT = getenv("HMSBIN_OUTPUT");
    }
    catch (...){
        std::cout << "Environment variables HMSBIN_INPUT and HMSBIN_OUTPUT have to be defined as a file system path to a directory";
        throw 1;
        //return 1;
    }
    std::cout << HMSBIN_INPUT << std::endl;
    std::cout << HMSBIN_OUTPUT << std::endl;

    std::cout << "Testing debugger" << std::endl;



    InitializeMagick(NULL);

        // create an empty-canvas image
        //this is *not* a "blank" image, it's completely empty as its canvas has 0x0 dimnesions
        //Image empty_image();
        //Image blank_image(Geometry(640, 480), Color(QuantumRange, QuantumRange, QuantumRange, 0));
        //Image blank_image("640x480", "white");
        //implementation of curves

        /*
    // create a blank image canvas with 640x480 size and 'white' color as background:
    Magick::Image blank_image( Geometry(640, 480), Color(QuantumRange, QuantumRange, QuantumRange, 0));
    // or also, by using the automatic C++ type conversions for the arguments:
    Magick::Image blank_image("640x480", "white")
    */

    Image squaresImage;
    squaresImage.read(HMSBIN_INPUT+"/51_copy.jpg");
    // my_image.magick("png"); //no need to explicitly set it to PNG

    Image squaresImage_png(squaresImage);
    squaresImage_png.write(HMSBIN_OUTPUT+"/51.png"); // will be automatically converted to PNG

    squaresImage.modifyImage(); //Ensure that there is only one reference to
                                // underlying image; if this is not done, then the
                                // image pixels *may* remain unmodified. [???]

    Pixels squaresImage_pixelCache(squaresImage);

    //Quantum* pixels;
    MagickLib::PixelPacket *pixels;

    int start_x = 50, start_y = 50, size_x = 150, size_y = 150;
    pixels = squaresImage_pixelCache.get(start_x, start_y, size_x, size_y);

    *(pixels + 1) = Color(0, 0, 0, 127);
    *(pixels + 2) = Color(0, 0, 0, 127);
    *(pixels + 3) = Color(0, 0, 0, 127);
    *(pixels + 4) = Color(0, 0, 0, 127);
    *(pixels + 5) = Color(0, 0, 0, 127);
    *(pixels + 6) = Color(0, 0, 0, 127);
    *(pixels + 7) = Color(0, 0, 0, 127);
    *(pixels + 8) = Color(0, 0, 0, 127);
    *(pixels + 9) = Color(0, 0, 0, 127);
    *(pixels + 10) = Color(0, 0, 0, 127);
    *(pixels + 11) = Color(0, 0, 0, 127);
    *(pixels + 12) = Color(0, 0, 0, 127);

    squaresImage_pixelCache.sync();

    squaresImage.write(HMSBIN_OUTPUT+"/51_processed.jpg");

    /*
    for (int i = 0; i < argc; ++i)
    {
        std::string teststring = "a parameter #";
        std::cout << teststring << i << std::endl;
        //std::string my_str = argv[i]; //produces error, because, apparently, c++ string cannot be assigned to c *char value
        std::cout << argv[i] << std::endl;
    }
    //*/

    return 0;
}
