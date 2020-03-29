#include <iostream>
//#include <cstdlib>

//#include "KukMagick.h"
#include "KukMagician.h"
//#include "KukMagick.cpp"

using namespace std;
using namespace Magick;
using namespace KukMagick;



// maximum allowed difference between length of sides for a square (maximum allowed ratio between any two sides of a square)
const float sidelength_error = 1.02; // essentially is "2% difference"

// maximum allowed deviation from exact 90 deg (pi/2) angle between sides for a square
//float sidesangle_error = 0.0349; // pi/90 = 2 deg
const float sidesangle_error = 0.01745; // pi/180 = 1 deg

// maximum allowed distance from adjoint endpoints of two adjacent sides of a square (ratio of sidelength)
const float sideendpoints_error = 0.02; // "2% of a sidelength"




int main(int argc, char const *argv[], char *env[]){


    KukMagician Magician;
    Magician.stopwatch.start();
    std::string start_timestamp = Magician.stopwatch.getStart_timestamp();
    Magician.setTimestamp(start_timestamp);

    std::string HMSBIN_INPUT, HMSBIN_OUTPUT;

    //

    try{
        HMSBIN_INPUT =      getenv("HMSBIN_INPUT");
        HMSBIN_OUTPUT =     getenv("HMSBIN_OUTPUT");
        Magician.setHMSBIN_INPUT  ( HMSBIN_INPUT  );
        Magician.setHMSBIN_OUTPUT ( HMSBIN_OUTPUT );
        //Magician.setHMSBIN_INPUT  ( getenv("HMSBIN_INPUT")  );
        //Magician.setHMSBIN_OUTPUT ( getenv("HMSBIN_OUTPUT") );
        //HMSBIN_INPUT = Magician.getHMSBIN_INPUT();
        //HMSBIN_OUTPUT = Magician.getHMSBIN_OUTPUT();
    }
    catch (...){
        std::cout << "Invalid environment variables HMSBIN_INPUT and HMSBIN_OUTPUT. They have to be defined as a file system path to a directory";
        throw 1;
    }

    InitializeMagick(NULL);

    //

    ofstream logfile = Magician.kuklog();

    logfile << "hello from main()\n";

    //

    //
    //Magician.stopwatch.end();
    //return 0;
    //

    //

    // KukMagick::Image squaresImage;
    // KukMagick::Image squaresImage_copy;

    // squaresImage.read(HMSBIN_INPUT + "/51.jpg");
    // squaresImage.read(HMSBIN_INPUT + "/testimages/test_noColorIntensityDifference2.png");
    // //squaresImage.meanGradientEdges();
    // //squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"edges_meanGradient"+".jpg");

    // squaresImage.evenBlur3x3();
    // squaresImage.gaussianBlur5x5();

    //
    
    //
    
    /*

    squaresImage.type();

    KukMagick::Image squaresImage_RGBRed(squaresImage);
    KukMagick::Image squaresImage_RGBGreen(squaresImage);
    KukMagick::Image squaresImage_RGBBlue(squaresImage);

    squaresImage_RGBRed.channel(Magick::RedChannel);
    squaresImage_RGBGreen.channel(Magick::GreenChannel);
    squaresImage_RGBBlue.channel(Magick::BlueChannel);

    squaresImage_RGBRed.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"01RedChannel"+".jpg");
    squaresImage_RGBGreen.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"01GreenChannel"+".jpg");
    squaresImage_RGBBlue.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"01BlueChannel"+".jpg");
    
    squaresImage_RGBRed.meanGradientEdges_normalized();
    squaresImage_RGBGreen.meanGradientEdges_normalized();
    squaresImage_RGBBlue.meanGradientEdges_normalized();

    squaresImage_RGBRed.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"02RedChannel_meanGradientEdges"+".jpg");
    squaresImage_RGBGreen.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"02GreenChannel_meanGradientEdges"+".jpg");
    squaresImage_RGBBlue.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"02BlueChannel_meanGradientEdges"+".jpg");
    
    squaresImage_RGBRed.composite(squaresImage_RGBGreen,0,0,MagickLib::LightenCompositeOp);
    squaresImage_RGBBlue.composite(squaresImage_RGBRed,0,0,MagickLib::LightenCompositeOp);

    squaresImage = squaresImage_RGBBlue;

    squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +"original"+"_"+"03rgbLightenCompositeOp_meanGradientEdges"+".jpg");

    //*/

    /*


    // Create base image 
    Magick::Image image(Geometry(254,218), "white");


    // Set the image type to TrueColor DirectClass representation.
    image.type(MagickLib::TrueColorType);
    // Ensure that there is only one reference to underlying image 
    // If this is not done, then image pixels will not be modified.
    image.modifyImage();

    // Allocate pixel view 
    Pixels view(image);

    // Set all pixels in region anchored at 38x36, with size 160x230 to green. 
    size_t columns = 196; size_t rows = 162; 
    Color green("green");
    //Quantum *pixels = view.get(38,36,columns,rows);
    MagickLib::PixelPacket *pixels = view.get(38,36,columns,rows);
    for ( ssize_t row = 0; row < rows ; ++row ) {
        for ( ssize_t column = 0; column < columns ; ++column ) {
            *pixels++ = green;
        }
    }
    // Save changes to image.
    view.sync();

    // Set all pixels in region anchored at 86x72, with size 108x67 to yellow. 
    columns = 108; rows = 67; 
    Color yellow("yellow"); 
    pixels = view.get(86,72,columns,rows); 
    for ( ssize_t row = 0; row < rows ; ++row ) {
        for ( ssize_t column = 0; column < columns ; ++column ) {
            *pixels++ = yellow;
        }
    }
    view.sync();

    // Set pixel at position 108,94 to red 
    Color red("red");
    pixels = view.get(108,94,1,1);
    *pixels++ = red;

    // Save changes to image.
    view.sync();
    image.write(HMSBIN_OUTPUT + "/testimagelogo_"+timestamp+".png");

    //*/

    //

    //
    
    //

    //

    // Blur convolution
    logfile << "reading images, initializing Magick++ variables..." << "\n";
    KukMagick::Image squaresImage;
    squaresImage.read(HMSBIN_INPUT + "/51.jpg");
    Magick::Image squaresImage_convolve;
    squaresImage_convolve.read(HMSBIN_INPUT + "/51.jpg");
    Magick::Image squaresImage_convolve_copy;
    squaresImage_convolve_copy.read(HMSBIN_INPUT + "/51.jpg");

    const unsigned short int kernel_size = 3;
    const unsigned short int kernel_count = kernel_size*kernel_size - 1;
    const unsigned short int kernel_order = (kernel_size-1)/2;

    logfile << "kernel_size = " << kernel_size << ", " << "kernel_count = " << kernel_count << ", " << "kernel_order = " << kernel_order << "\n";

    const double kernel[9] = {
         1,  2,  1,
         2,  4,  2,
         1,  2,  1,
    };
    //const double kernel_sum = 8; // sum of abs value of all values divided by 2
    const double kernel_sum = 16;

    squaresImage.kukConvolve(&squaresImage_convolve_copy, &squaresImage_convolve, kernel_size, kernel, kernel_sum);

    //squaresImage.gaussianBlur3x3();
    //squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" + "original" + "_" + "gaussianBlur3x3" + ".jpg");

    squaresImage_convolve.write(HMSBIN_OUTPUT + "/51_" + start_timestamp + "_" + "original" + "_" + "kukConvolve" + ".jpg");

    //

    Magician.stopwatch.end();
    return 0;

    //

    //

    /*

    // Blur convolution
    logfile << "reading images, initializing Magick++ variables..." << "\n";
    KukMagick::Image squaresImage;
    squaresImage.read(HMSBIN_INPUT + "/51.jpg");
    Magick::Image *squaresImage_convolve = nullptr;
    (*squaresImage_convolve).read(HMSBIN_INPUT + "/51.jpg");
    Magick::Image *squaresImage_convolve_copy = nullptr;
    (*squaresImage_convolve_copy).read(HMSBIN_INPUT + "/51.jpg");

    const unsigned short int kernel_size = 3;
    const unsigned short int kernel_count = kernel_size*kernel_size - 1;
    const unsigned short int kernel_order = (kernel_size-1)/2;

    logfile << "kernel_size = " << kernel_size << ", " << "kernel_count = " << kernel_count << ", " << "kernel_order = " << kernel_order << "\n";

    const double kernel[9] = {
         1,  2,  1,
         2,  4,  2,
         1,  2,  1,
    };
    //const double kernel_sum = 8; // sum of abs value of all values divided by 2
    const double kernel_sum = 16;

    squaresImage.kukConvolve(squaresImage_convolve_copy, squaresImage_convolve, kernel_size, kernel, kernel_sum);

    //squaresImage.gaussianBlur3x3();
    //squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" + "original" + "_" + "gaussianBlur3x3" + ".jpg");

    (*squaresImage_convolve).write(HMSBIN_OUTPUT + "/51_" + start_timestamp + "_" + "original" + "_" + "kukConvolve" + ".jpg");

    //

    /* 
    //*/

    Magician.stopwatch.end();
    return 0;

}
