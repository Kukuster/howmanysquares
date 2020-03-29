#include <iostream>
#include <stdlib.h>
//#include <cstdlib>
#include <chrono>
#include <ctime>

#include "KukMagick.h"


using namespace Magick;
using namespace std;



// maximum allowed difference between length of sides for a square (maximum allowed ratio between any two sides of a square)
const float sidelength_error = 1.02; // essentially is "2% difference"

// maximum allowed deviation from exact 90 deg (pi/2) angle between sides for a square
//float sidesangle_error = 0.0349; // pi/90 = 2 deg
const float sidesangle_error = 0.01745; // pi/180 = 1 deg

// maximum allowed distance from adjoint endpoints of two adjacent sides of a square (ratio of sidelength)
const float sideendpoints_error = 0.02; // "2% of a sidelength"





int main(int argc, char const *argv[], char *env[])
{

    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::string date_time = std::ctime(&start_time);
    std::string timestamp = std::to_string(start_time);

    //std::cout << date_time;
    


    std::string HMSBIN_INPUT, HMSBIN_OUTPUT;
    try{
        HMSBIN_INPUT = getenv("HMSBIN_INPUT");
        HMSBIN_OUTPUT = getenv("HMSBIN_OUTPUT");
    }
    catch (...){
        std::cout << "Invalid environment variables HMSBIN_INPUT and HMSBIN_OUTPUT. They have to be defined as a file system path to a directory";
        throw 1;
        //return 1;
    }


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


    //Magick::Image squaresImage;

    // squaresImage.read(HMSBIN_INPUT+"/51.jpg");
    // Magick::Image squaresImage_edges_x(squaresImage);
    // Magick::Image squaresImage_edges_y(squaresImage);
    // Magick::Image squaresImage_edges_xyMean(squaresImage);

    // Magick::Image squaresImage_copy(squaresImage);
    // Magick::Image squaresImage_copy2(squaresImage);

    MagickLib::CompositeOperator plusComposite = MagickLib::PlusCompositeOp;

    // squaresImage.convolve(3, kernel_evenblur3x3);
    // squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "step01_evenblur3x3.jpg");

    // squaresImage.convolve(5, kernel_gaussianblur5x5_light146);
    // squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "step02_gaussianblur5x5_light146.jpg");

    // squaresImage.convolve(5, kernel_gaussianunsharp5x5_light146);
    // squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "step03_gaussianunsharp5x5_light146.jpg");

    //squaresImage.edge(5);
    //squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "step04_edge5.jpg");

    //squaresImage.convolve(3, kernel_evenblur3x3);

    //squaresImage.write(HMSBIN_OUTPUT + "/" + timestamp + "_51_evenblur3x3.jpg");

    //std::string pause2 = "pause during debug";
    /*
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    squaresImage.convolve(3, kernel_evenblur3x3);
    
    //squaresImage.convolve(3, kernel_gaussianblur3x3_light12);

    squaresImage.write(HMSBIN_OUTPUT + "/51_" + timestamp + "step01_7x_evenblur3x3.jpg");

    squaresImage_copy.convolve(3, kernel_evenblur3x3);
    squaresImage_copy.convolve(3, kernel_evenblur3x3);
    squaresImage_copy.convolve(3, kernel_gaussianblur3x3_light12);
    squaresImage_copy.convolve(3, kernel_gaussianblur3x3_light12);
    squaresImage_copy.convolve(3, kernel_gaussianblur3x3_light12);
    squaresImage_copy.convolve(3, kernel_gaussianblur3x3_light12);
    squaresImage_copy.write(HMSBIN_OUTPUT + "/51_" + timestamp + "copy_step01_someblur.jpg");
    squaresImage_copy2 = squaresImage_copy;
    squaresImage_copy.edge(1);
    squaresImage_copy.write(HMSBIN_OUTPUT + "/51_" + timestamp + "copy_step02_edge1.jpg");
    squaresImage_copy2.edge(2);
    squaresImage_copy2.write(HMSBIN_OUTPUT + "/51_" + timestamp + "copy2_step02_edge2.jpg");

    //mergeEdge.PlusCompositeOp();
    //const Magick::Image &squaresImage2const = squaresImage2;

    return 0;
    squaresImage_edges_x.composite(squaresImage_edges_y, 0, 0, plusComposite);
    squaresImage_edges = squaresImage_edges_x;

    //*/

    //squaresImage.composite(squaresImage2, 0, 0, plusComposite);
    //
    //
    //






/*
    Magick::Image preprocessedSquaresImage;
    Magick::Image preprocessedSquaresImage_edges_xyMean_x;
    Magick::Image preprocessedSquaresImage_edges_xyMean_y;
    Magick::Image preprocessedSquaresImage_edges_xyMean;
    Magick::Image preprocessedSquaresImage_edgesLaplacian;




    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edges_xyMean_x = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean_y = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage;

    preprocessedSquaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges);
    preprocessedSquaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges);
    preprocessedSquaresImage_edges_xyMean_x.composite(preprocessedSquaresImage_edges_xyMean_y, 0, 0, plusComposite);
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage_edges_xyMean_x;

    preprocessedSquaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesXYMean.jpg");




    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edges_xyMean_x = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean_y = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage;

    preprocessedSquaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges_strong);
    preprocessedSquaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges_strong);
    preprocessedSquaresImage_edges_xyMean_x.composite(preprocessedSquaresImage_edges_xyMean_y, 0, 0, plusComposite);
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage_edges_xyMean_x;

    preprocessedSquaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesXYMeanStrong.jpg");



    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(3, kernel_laplacian_one);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianOne.jpg");

    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(3, kernel_laplacian_two);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianTwo.jpg");

    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(5, kernel_laplacian_three);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianThree.jpg");

    //
    //

    



    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edges_xyMean_x = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean_y = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage;

    preprocessedSquaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges);
    preprocessedSquaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges);
    preprocessedSquaresImage_edges_xyMean_x.composite(preprocessedSquaresImage_edges_xyMean_y, 0, 0, plusComposite);
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage_edges_xyMean_x;

    preprocessedSquaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_smartblurred_edgesXYMean.jpg");

    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edges_xyMean_x = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean_y = preprocessedSquaresImage;
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage;

    preprocessedSquaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges_strong);
    preprocessedSquaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges_strong);
    preprocessedSquaresImage_edges_xyMean_x.composite(preprocessedSquaresImage_edges_xyMean_y, 0, 0, plusComposite);
    preprocessedSquaresImage_edges_xyMean = preprocessedSquaresImage_edges_xyMean_x;

    preprocessedSquaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesXYMeanStrong.jpg");

    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(3, kernel_laplacian_one);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianOne.jpg");

    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(3, kernel_laplacian_two);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianTwo.jpg");

    //preprocessedSquaresImage.read(HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg");
    preprocessedSquaresImage.read(HMSBIN_INPUT + "/51.jpg");
    preprocessedSquaresImage_edgesLaplacian = preprocessedSquaresImage;
    preprocessedSquaresImage_edgesLaplacian.convolve(5, kernel_laplacian_three);
    preprocessedSquaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_maximized_edgesLaplacianThree.jpg");


//*/
    //
    //cout << "hello before var definitions";
    //

    Magick::Image squaresImage;
    Magick::Image squaresImage_RGBRed;
    Magick::Image squaresImage_RGBGreen;
    Magick::Image squaresImage_RGBBlue;
    Magick::Image squaresImage_edges_xyMean_x;
    Magick::Image squaresImage_edges_xyMean_y;
    Magick::Image squaresImage_edges_xyMean;
    Magick::Image squaresImage_edgesLaplacian;
    Magick::Image squaresImage_edgesDefault;

    int imagesN = 1;
    int processingsN = 6;

    const std::string imagesList[imagesN] = {
        //HMSBIN_INPUT + "/51.jpg",
        //HMSBIN_INPUT + "/51.jpg",
        //HMSBIN_INPUT + "/51_ps_preprocessed_B.jpg",
        //HMSBIN_INPUT + "/51_steps_processing/51_maximize.jpg",
        HMSBIN_INPUT + "/testimages/test_noColorIntensityDifference2.png"
    };
    const std::string imagesListNames[imagesN] = {
        //"01original",
        //"02gaussBlurred",
        //"03smartBlurred",
        //"04maximized",
        "test_noColorIntensityDifference2"
    };
    const std::string processings[processingsN] = {
        "edgesXYMean",
        "edgesXYMeanStrong",
        "laplacianOne",
        "laplacianTwo",
        "laplacianThree",
        "defaultEdge0"
    };
    const std::string processingTypes[processingsN] = {
        "sobelMean",
        "sobelMean",
        "laplacian",
        "laplacian",
        "laplacian",
        "defaultEdge"
    };

    enum Processing {
        edgesXYMean,
        edgesXYMeanStrong,
        laplacianOne,
        laplacianTwo,
        laplacianThree
    };
    Processing processing = edgesXYMean;
    switch (processing){
        case edgesXYMean: break;
        case edgesXYMeanStrong: break;
        case laplacianOne: break;
        case laplacianTwo: break;
        case laplacianThree: break;
    }




    squaresImage.read(HMSBIN_INPUT + "/51.jpg");
    squaresImage_RGBRed = squaresImage;
    squaresImage_RGBGreen = squaresImage;
    squaresImage_RGBBlue = squaresImage;
    squaresImage_RGBRed.channel(Magick::RedChannel);
    squaresImage_RGBGreen.channel(Magick::GreenChannel);
    squaresImage_RGBBlue.channel(Magick::BlueChannel);


    if (false){

    for (int i=0; i<imagesN; i++){

        squaresImage.read(imagesList[i]);
        if (imagesListNames[i] == "02gaussBlurred"){
            squaresImage.convolve(5, kernel_gaussianblur5x5);
        }

        for (int j=0; j<processingsN; j++){

            if (processingTypes[j] == "sobelMean"){
                squaresImage_edges_xyMean_x = squaresImage;
                squaresImage_edges_xyMean_y = squaresImage;
                squaresImage_edges_xyMean = squaresImage;

                if (processings[j] == "edgesXYMean"){
                    squaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges_normalized);
                    squaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges_normalized);
                } else if (processings[j] == "edgesXYMeanStrong"){
                    squaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges);
                    squaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges);
                }

                squaresImage_edges_xyMean_x.composite(squaresImage_edges_xyMean_y, 0, 0, MagickLib::PlusCompositeOp);
                squaresImage_edges_xyMean = squaresImage_edges_xyMean_x;

                squaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_"+imagesListNames[i]+"_"+processings[j]+".jpg");
            

            } else if (processingTypes[j] == "laplacian") {
                squaresImage_edgesLaplacian = squaresImage;

                if (processings[j] == "laplacianOne"){
                    squaresImage_edgesLaplacian.convolve(3, kernel_laplacian_3x3_weak);
                } else if (processings[j] == "laplacianTwo"){
                    squaresImage_edgesLaplacian.convolve(3, kernel_laplacian_3x3);
                } else if (processings[j] == "laplacianThree"){
                    squaresImage_edgesLaplacian.convolve(5, kernel_laplacian_5x5);
                }

                squaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +imagesListNames[i]+"_"+processings[j]+".jpg");


            } else if (processingTypes[j] == "defaultEdge") {
                squaresImage_edgesDefault = squaresImage;

                if (processings[j] == "defaultEdge0"){
                    squaresImage_edgesDefault.edge(0);
                }

                squaresImage_edgesDefault.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +imagesListNames[i]+"_"+processings[j]+".jpg");

            }


        } // endfor j

    } // endfor i

    } // endif














    // RGB
    // processing each channel separately, then combine them for output

    if (false){

    for (int i=0; i<imagesN; i++){

        squaresImage.read(imagesList[i]);
        if (imagesListNames[i] == "02gaussBlurred"){
            squaresImage.convolve(5, kernel_gaussianblur5x5);
        }

        for (int j=0; j<processingsN; j++){

            if (processingTypes[j] == "sobelMean"){
                squaresImage_edges_xyMean_x = squaresImage;
                squaresImage_edges_xyMean_y = squaresImage;
                squaresImage_edges_xyMean = squaresImage;

                if (processings[j] == "edgesXYMean"){
                    squaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges_normalized);
                    squaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges_normalized);
                } else if (processings[j] == "edgesXYMeanStrong"){
                    squaresImage_edges_xyMean_x.convolve(3, kernel_sobel_x_edges);
                    squaresImage_edges_xyMean_y.convolve(3, kernel_sobel_y_edges);
                }

                squaresImage_edges_xyMean_x.composite(squaresImage_edges_xyMean_y, 0, 0, plusComposite);
                squaresImage_edges_xyMean = squaresImage_edges_xyMean_x;

                squaresImage_edges_xyMean.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_"+imagesListNames[i]+"_"+processings[j]+".jpg");
            

            } else if (processingTypes[j] == "laplacian") {
                squaresImage_edgesLaplacian = squaresImage;

                if (processings[j] == "laplacianOne"){
                    squaresImage_edgesLaplacian.convolve(3, kernel_laplacian_3x3_weak);
                } else if (processings[j] == "laplacianTwo"){
                    squaresImage_edgesLaplacian.convolve(3, kernel_laplacian_3x3);
                } else if (processings[j] == "laplacianThree"){
                    squaresImage_edgesLaplacian.convolve(5, kernel_laplacian_5x5);
                }

                squaresImage_edgesLaplacian.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" + imagesListNames[i] + "_" + processings[j] + ".jpg");


            } else if (processingTypes[j] == "defaultEdge") {
                squaresImage_edgesDefault = squaresImage;

                if (processings[j] == "defaultEdge0"){
                    squaresImage_edgesDefault.edge(0);
                }

                squaresImage_edgesDefault.write(HMSBIN_OUTPUT + "/51_" + timestamp + "_" +imagesListNames[i]+"_"+processings[j]+".jpg");

            }

        } // endfor j

    } // endfor i


    } //endif





















    //

    //

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "program finished"
              << "\n"
              //<< "finished computation at " << std::ctime(&end_time) << "\n"
              << "execution time: " << elapsed_seconds.count() << "s\n";

    return 0;

    //

    //

    //

    //

    //

    //

    //

    //

    // my_image.magick("png"); //no need to explicitly set it to PNG

    Magick::Image squaresImage_png(squaresImage);
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

    /*// Do this after a computation
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "program finished" << "\n"
              //<< "finished computation at " << std::ctime(&end_time) << "\n"
              << "execution time: " << elapsed_seconds.count() << "s\n";

    //*/

    return 0;
}
