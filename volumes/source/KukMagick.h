#ifndef _KukMagick_h
#define _KukMagick_h

#include <Magick++.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cassert>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <vector>

namespace KukMagick {

    using namespace Magick;

    class KukStopwatch
    {
        public:
            KukStopwatch();

        private:
            std::time_t start_time;
            std::string start_date_time;

            std::chrono::_V2::system_clock::time_point split_timepoint;
            std::chrono::duration<double> elapsed_seconds;

            std::chrono::_V2::system_clock::time_point end_timepoint;
            std::time_t end_time;

        /* not very */ private:
            std::chrono::_V2::system_clock::time_point  start_timepoint;
            std::string                                 start_timestamp;

        public:
            std::string timestamp(std::time_t time);

            std::chrono::_V2::system_clock::time_point  getStart_timepoint();
            std::string                                 getStart_timestamp();

            void set    (std::chrono::_V2::system_clock::time_point start_timepoint);
            void start  (const char *text = "");
            void split  (const char *text = "split at %ss\n");
            void end    (const char *text = "execution time: %ss\n");

    };

    class KukMagician
    {
        public:
            KukMagician();
            KukStopwatch stopwatch;

        private:

        /* not very */ private:
            std::chrono::_V2::system_clock::time_point timepoint;
            std::string timestamp;
            std::string HMSBIN_INPUT, HMSBIN_OUTPUT;
            //std::unordered_map<std::string, std::string> VAR;
            ////Magician.VAR['']

            //KukStopwatch stopwatch;
            //KukSpellbook spellbook;

        public:
            std::string getTimestamp();
            void        setTimestamp(std::time_t time);
            void        setTimestamp(std::string timestamp);
            void        setTimestamp(char * timestamp);

            std::string getHMSBIN_INPUT();
            void        setHMSBIN_INPUT(char * HMSBIN_INPUT);
            void        setHMSBIN_INPUT(std::string HMSBIN_INPUT);

            std::string getHMSBIN_OUTPUT();
            void        setHMSBIN_OUTPUT(char * HMSBIN_OUTPUT);
            void        setHMSBIN_OUTPUT(std::string HMSBIN_OUTPUT);

            //KukStopwatch getStopwatch();
            //void         setStopwatch();

            //KukSpellbook* spellbook();
            //void spellbook();

            void initInputs();

            std::ofstream kuklog(std::string name = "");
            //void kuklog(std::string text);
            //void kuklog(char* text);

    };

    class KukSpellbook
    {
        
        public:
            static std::string format(const char *fmt, ...)
            {
                va_list args;
                va_start(args, fmt);
                std::vector<char> v(1024);
                while (true)
                {
                    va_list args2;
                    va_copy(args2, args);
                    int res = vsnprintf(v.data(), v.size(), fmt, args2);
                    if ((res >= 0) && (res < static_cast<int>(v.size())))
                    {
                        va_end(args);
                        va_end(args2);
                        return std::string(v.data());
                    }
                    size_t size;
                    if (res < 0)
                        size = v.size() * 2;
                    else
                        size = static_cast<size_t>(res) + 1;
                    v.clear();
                    v.resize(size);
                    va_end(args2);
                }
            }
            //std::string str = format("I have %d apples and %d oranges, so I have %d fruits", apples, oranges, apples + oranges);

    };



    signed short int *offset_values(unsigned short int kernel_size,
                                    unsigned short int kernel_order,
                                    unsigned short int kernel_index,
                                    signed short int *xy);

    unsigned short int kernel_index(unsigned short int kernel_size,
                                    unsigned short int kernel_order,
                                    signed short int x,
                                    signed short int y);


    std::string format(const char *fmt, ...);

    float   round_to_decpoint( float number, int precision);
    double  round_to_decpoint(double number, int precision);

    std::string f2str(double number);
    std::string f2str(float  number);


    class Image: public Magick::Image
    {
    public:
        void evenBlur3x3();
        void evenBlur5x5();

        void gaussianBlur3x3();
        void gaussianBlur3x3_1_2();
        void gaussianBlur5x5();
        void gaussianBlur5x5_1_4_6();
        void gaussianBlur5x5_1_2_4();
        void gaussianBlur7x7();
        void gaussianBlur7x7_1_6_15_20();
        void gaussianBlur7x7_1_2_4_8();

        void smartBlur();


        void gaussianUnSharp5x5();


        void sobelEdges(); // not void. Should somehow return edges and angles
        //void sobelEdges_normalized(); // not void. Should somehow return edges and angles
        void meanGradientEdges();
        void meanGradientEdges_normalized();

        void laplacianEdges3x3_weak();
        void laplacianEdges3x3();
        void laplacianEdges5x5_weak();
        void laplacianEdges5x5();


        // Image *kukConvolve(const Image * __restrict__ image,const unsigned int order,
        //                           const double * __restrict__ kernel);
        
        void kukConvolve(Magick::Image * __restrict__ read_image,
                         Magick::Image * writable_copy_image, 
                         const unsigned short int kernel_size,
                         const double * __restrict__ kernel,
                         const double kernel_sum
                         );


    };


} // namespace KukMagick





const double kernel_evenblur3x3[9] = {
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
};
const double kernel_evenblur5x5[25] = {
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0,
};
const double kernel_gaussianblur3x3[9] = {
    1.0, 2.0, 1.0,
    2.0, 4.0, 2.0,
    1.0, 2.0, 1.0,
};
const double kernel_gaussianblur5x5_1_2_4[25] = {
    1.0, 2.0, 4.0, 2.0, 1.0,
    2.0, 4.0, 8.0, 4.0, 2.0,
    4.0, 8.0, 16., 8.0, 4.0,
    2.0, 4.0, 8.0, 4.0, 2.0,
    1.0, 2.0, 4.0, 2.0, 1.0,
};
const double kernel_gaussianblur5x5[25] = {
    1.0, 4.0, 6.0, 4.0, 1.0,
    4.0, 16., 24., 16., 4.0,
    6.0, 24., 36., 24., 6.0,
    4.0, 16., 24., 16., 4.0,
    1.0, 4.0, 6.0, 4.0, 1.0,
};
const double kernel_gaussianblur7x7_1_2_4_8[49] = {
    1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 1.0,
    2.0, 4.0, 8.0, 16., 8.0, 4.0, 2.0,
    4.0, 8.0, 16., 32., 16., 8.0, 4.0,
    8.0, 16., 32., 64., 32., 16., 8.0,
    4.0, 8.0, 16., 32., 16., 8.0, 4.0,
    2.0, 4.0, 8.0, 16., 8.0, 4.0, 2.0,
    1.0, 2.0, 4.0, 8.0, 4.0, 2.0, 1.0,
};
const double kernel_gaussianblur7x7[49] = {
     1,   6,  15,  20,  15,   6,   1,
     6,  36,  90, 120,  90,  36,   6,
    15,  90, 225, 300, 225,  90,  15,
    20, 120, 300, 400, 300, 120,  20,
    15,  90, 225, 300, 225,  90,  15,
     6,  36,  90, 120,  90,  36,   6,
     1,   6,  15,  20,  15,   6,   1,
};
// 476  =  256+256-36  =  2*256 - 36  =  2* (1+4+6+4+1)^2 - 6*6
const double kernel_gaussianunsharp5x5[25] = {
    1.0,  4.0,  6.0,  4.0,  1.0,
    4.0,  16.,  24.,  16.,  4.0,
    6.0,  24., -476,  24.,  6.0,
    4.0,  16.,  24.,  16.,  4.0,
    1.0,  4.0,  6.0,  4.0,  1.0,
};



const double kernel_sobel_x_edges_normalized[9] = {
    -0.25,  0,  0.25,
    -0.50,  0,  0.50,
    -0.25,  0,  0.25,
};
const double kernel_sobel_y_edges_normalized[9] = {
    -0.25, -0.50, -0.25,
      0,     0,     0,
     0.25,  0.50,  0.25,
};
const double kernel_sobel_x_edges[9] = {
    -1,  0,  1,
    -2,  0,  2,
    -1,  0,  1,
};
const double kernel_sobel_y_edges[9] = {
    -1, -2, -1,
     0,  0,  0,
     1,  2,  1,
};

const double kernel_laplacian_3x3_weak[9] = {
     0, -1,  0,
    -1,  4, -1,
     0, -1,  0,
};
const double kernel_laplacian_3x3[9] = {
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1,
};
const double kernel_laplacian_5x5_weak[25] = {
     0,  0, -1,  0,  0,
     0, -1, -1, -1,  0,
    -1, -1, 12, -1, -1,
     0, -1, -1, -1,  0,
     0,  0, -1,  0,  0,
};
const double kernel_laplacian_5x5[25] = {
    -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1,
    -1, -1, 24, -1, -1,
    -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1,
};







// ===== Lost constants ===== //

const int QuantumRange = 65535;
// From official Magick++ documentation:
//
// << In any case, Magick++ provides the applications with the 'QuantumRange' constant which always
//    specifies the number of quantizing levels - 1 as available on the particular version of the library
//    that is being used (e.g. for a library version compiled with 8 bits per Quantum component the
//    QuantumRange constant is 255). >>
// 
// http://www.multipole.org/discourse-server/viewtopic.php?t=32486
//







#endif /* _KukMagick_h */

