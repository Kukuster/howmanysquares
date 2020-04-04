#include "KukMagick.h"

using namespace KukMagick;

// ===== Functions for kernel convolution ===== //

/**
 * 
 * Converts 1-d index of value of 2-d square kernel to @x and @y offset indices, such that (0,0) represents the central kernel element
 * 
 * `unsigned short` type of kernel_index limits it to 65535 and therefore limits kernel size to maximum of 256x256
 * 
 * @kernel_size is a length of one side of a kernel
 *  for example: 3 for 3x3 kernel, 5 for 5x5 kernel, etc
 *  required to be an odd natural number
 * 
 * @kernel_order is calculated as follows: (kernel_size-1)/2
 *  Such that it equals 0,1,2,3,... for 1x1,3x3,5x5,7x7,... kernel
 *  required to be a natural number or a zero
 * 
 * @kernel_index is 1-d index of value in a kernel
 *  f.e.: 0,1,2,3,4,5,6,7,8 are indices left to right & top to bottom in a 3x3 kernel
 *  required to be a natural number or a zero
 * 
 * @xy (pointer to an array[2]) are x and y offset indices in square kernel relative to the central element
 *  f.e. 0th, 4th and 7th elements in 3x3 kernel have offsets (-1,-1), (0,0) and (0,1) respectively
 *  @x and @y values have to be a whole number spanning [-kernel_order, kernel_order]
 * 
 * @return @xy, pointer to an array[2], the values are changed in the function and the pointer is returned
 * 
 */
signed short int* KukMagick::offset_values(unsigned short int kernel_size,
                                           unsigned short int kernel_order,
                                           unsigned short int kernel_index,
                                           signed short int *xy)
{
    signed short int res = kernel_index % kernel_size;

    xy[0] = (signed short int)(res - kernel_order);
    xy[1] = (signed short int)( ((kernel_index - res) / kernel_size) - kernel_order );

    return xy;
}

/**
 * 
 * Converts @x and @y offset indices of a 2-d square kernel to 1-d index, such that (0,0) represents the central kernel element
 * 
 * `unsigned short` type of kernel_index limits it to 65535 and therefore limits kernel size to maximum of 256x256
 * 
 * @kernel_size is a length of one side of a kernel
 *  for example: 3 for 3x3 kernel, 5 for 5x5 kernel, etc
 *  required to be an odd natural number
 * 
 * @kernel_order is calculated as follows: (kernel_size-1)/2
 *  Such that it equals 0,1,2,3,... for 1x1,3x3,5x5,7x7,... kernel
 *  required to be a natural number or a zero
 * 
 * @x and @y are 2-d offset values in a kernel
 *  f.e.: (-1,-1), (0,-1), (1,-1),
 *        (-1,0),  (0,0),  (1,0),
 *        (-1,1),  (0,1),  (1,1) 
 *  are offset indices that correspond to 0,1,2,3,4,5,6,7,8 1-d indices respectively left to right & top to bottom in a 3x3 kernel
 *  required to be whole numbers spanning [-kernel_order, kernel_order]
 * 
 * @return 1-d index in square kernel counting left to right & top to bottom
 *  f.e. (-1,-1), (0,0) and (0,1) in 3x3 kernel represent 0th, 4th and 7th elements respectively
 *  return value has to be a whole number spanning [0, kernel_size^2)
 * 
 */
unsigned short int KukMagick::kernel_index(unsigned short int kernel_size,
                                           unsigned short int kernel_order,
                                           signed short int x,
                                           signed short int y)
{
    return (x+kernel_order) + (y+kernel_order)*kernel_size;
}



std::string KukMagick::format(const char *fmt, ...)
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



float   KukMagick::round_to_decpoint( float number, int precision){
    return (float) round( number * pow(10,precision) ) / pow(10,precision);
}

double  KukMagick::round_to_decpoint(double number, int precision){
    return         round( number * pow(10,precision) ) / pow(10,precision);
}



std::string KukMagick::f2str(float number){

    std::string str{std::to_string(number)};
    int offset{1};
    if (str.find_last_not_of('0') == str.find('.')) {
        offset = 0;
    }
    str.erase(str.find_last_not_of('0') + offset, std::string::npos);
    return str;

    // //leaves trailing dot if whole
    // std::string str = std::to_string(number);
    // str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    // return str;
}

std::string KukMagick::f2str(double number){
  
    std::string str{std::to_string(number)};
    int offset{1};
    if (str.find_last_not_of('0') == str.find('.')) {
        offset = 0;
    }
    str.erase(str.find_last_not_of('0') + offset, std::string::npos);
    return str;

    // //leaves trailing dot if whole
    // std::string str = std::to_string(number);
    // str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    // return str;
}


// ===== class KukStopwatch ===== //

KukMagick::KukStopwatch::KukStopwatch()
{
}

std::chrono::_V2::system_clock::time_point KukMagick::KukStopwatch::getStart_timepoint()
{
    return this->start_timepoint;
};

std::string KukMagick::KukStopwatch::getStart_timestamp(){
    return this->start_timestamp;
};

std::string KukMagick::KukStopwatch::timestamp(std::time_t time){
    return std::to_string(time);
}

void KukMagick::KukStopwatch::set(std::chrono::_V2::system_clock::time_point start_timepoint){
  this->start_timepoint = start_timepoint;
  this->start_time = std::chrono::system_clock::to_time_t(this->start_timepoint);
  this->start_date_time = std::ctime(&(this->start_time));
  this->start_timestamp = std::to_string(this->start_time);
}

void KukMagick::KukStopwatch::start(const char * text){
    this->start_timepoint = std::chrono::system_clock::now();
    this->start_time = std::chrono::system_clock::to_time_t(this->start_timepoint);
    this->start_date_time = std::ctime(&(this->start_time));
    this->start_timestamp = std::to_string(this->start_time);

    std::cout << text;
}

void KukMagick::KukStopwatch::split(const char * text){
    this->split_timepoint = std::chrono::system_clock::now();

    this->elapsed_seconds = this->split_timepoint - this->start_timepoint;

    const int LEN = 13;
    char elapsed_char[LEN];
    snprintf(elapsed_char, LEN, "%f", this->elapsed_seconds.count());

    std::cout << format(text, elapsed_char);
}

void KukMagick::KukStopwatch::end(const char * text){
    this->end_timepoint = std::chrono::system_clock::now();
    this->end_time = std::chrono::system_clock::to_time_t(this->end_timepoint);

    this->elapsed_seconds = this->end_timepoint - this->start_timepoint;

    const int LEN = 13;
    char elapsed_char[LEN];
    snprintf(elapsed_char, LEN, "%f", this->elapsed_seconds.count());

    std::cout << format(text, elapsed_char);
}

            // void end(std::string text = "execution time: %ss\n");

            // std::chrono::_V2::system_clock::time_point end;
            // std::time_t end_time;



// ===== class KukMagician ===== //

KukMagician::KukMagician(){
    try{
        HMSBIN_INPUT =      getenv("HMSBIN_INPUT");
        HMSBIN_OUTPUT =     getenv("HMSBIN_OUTPUT");
        this->setHMSBIN_INPUT  ( HMSBIN_INPUT  );
        this->setHMSBIN_OUTPUT ( HMSBIN_OUTPUT );
    }
    catch (...){
        std::cout << "Invalid environment variables HMSBIN_INPUT and HMSBIN_OUTPUT. They have to be defined as a file system path to a directory";
        throw 1;
    }

    this->stopwatch.start();
    
    this->timepoint = this->stopwatch.getStart_timepoint();
    this->timestamp = this->stopwatch.getStart_timestamp();
    //std::string start_timestamp = this->stopwatch.getStart_timestamp();
    //this->setTimestamp(start_timestamp);

}


std::string KukMagick::KukMagician::getHMSBIN_INPUT(){
  return this->HMSBIN_INPUT;
}
void        KukMagick::KukMagician::setHMSBIN_INPUT(char * HMSBIN_INPUT){
  this->HMSBIN_INPUT = std::string(HMSBIN_INPUT);
}
void        KukMagick::KukMagician::setHMSBIN_INPUT(std::string HMSBIN_INPUT){
  this->HMSBIN_INPUT = HMSBIN_INPUT;
}

std::string KukMagick::KukMagician::getHMSBIN_OUTPUT(){
  return this->HMSBIN_OUTPUT;
}
void        KukMagick::KukMagician::setHMSBIN_OUTPUT(char * HMSBIN_OUTPUT){
  this->HMSBIN_OUTPUT = std::string(HMSBIN_OUTPUT);
}
void        KukMagick::KukMagician::setHMSBIN_OUTPUT(std::string HMSBIN_OUTPUT){
  this->HMSBIN_OUTPUT = HMSBIN_OUTPUT;
}





void KukMagick::KukMagician::setTimestamp(std::time_t time){
  this->timestamp = std::to_string(time);
}
void KukMagick::KukMagician::setTimestamp(std::string timestamp){
  this->timestamp = timestamp;
}
void KukMagick::KukMagician::setTimestamp(char * timestamp){
  this->timestamp = std::string(timestamp);
}






std::ofstream KukMagick::KukMagician::kuklog(std::string name)
{

    std::ofstream logfile;
    std::string s = this->getHMSBIN_OUTPUT() + "/" + this->stopwatch.getStart_timestamp() + "_" + name + ".log";
    logfile.open(s, std::ios_base::app);

    return logfile;

}



// ===== Blur filters ===== //


void KukMagick::Image::evenBlur3x3(){
    this->convolve(3, kernel_evenblur3x3);
}
void KukMagick::Image::evenBlur5x5(){
    this->convolve(5, kernel_evenblur5x5);
}

void KukMagick::Image::gaussianBlur3x3(){
    this->gaussianBlur3x3_1_2();
}
void KukMagick::Image::gaussianBlur3x3_1_2(){
    this->convolve(3, kernel_gaussianblur3x3);
}
void KukMagick::Image::gaussianBlur5x5(){
    this->gaussianBlur5x5_1_4_6();
}
void KukMagick::Image::gaussianBlur5x5_1_4_6(){
    this->convolve(5, kernel_gaussianblur5x5);
}
void KukMagick::Image::gaussianBlur5x5_1_2_4(){
    this->convolve(5, kernel_gaussianblur5x5_1_2_4);
}
void KukMagick::Image::gaussianBlur7x7(){
    this->gaussianBlur7x7_1_6_15_20();
}
void KukMagick::Image::gaussianBlur7x7_1_6_15_20(){
    this->convolve(7, kernel_gaussianblur7x7);
}
void KukMagick::Image::gaussianBlur7x7_1_2_4_8(){
    this->convolve(7, kernel_gaussianblur7x7_1_2_4_8);
}




void KukMagick::Image::kukConvolve(Magick::Image * read_image,
                                   Magick::Image * writable_copy_image,
                                   const unsigned short int kernel_size,
                                   const double * kernel,
                                   const double kernel_sum)
{
    KukMagician Magician;
    KukStopwatch Stopwatch;
    std::ofstream logfile = Magician.kuklog("Convolve");
    //logfile   << "hello from KukMagick::Image::kukConvolve()\n";
    std::ofstream logfile2 = Magician.kuklog("log2");

    const unsigned short int kernel_count = kernel_size * kernel_size - 1;
    const unsigned short int kernel_order = (kernel_size - 1) / 2;


    Pixels view(*read_image);
    Pixels view_convolve(*writable_copy_image);
    // use view.sync(); to verify that changes are commited to squaresImage_convolve

    size_t total_x = (*read_image).columns(),
           total_y = (*read_image).rows();

    const Magick::PixelPacket *pixels_read = view.getConst(0, 0, total_x, total_y);

    Magick::PixelPacket *pixels_write = view_convolve.get(0, 0, total_x, total_y);

    ssize_t y,x,i;
    signed short int xy_offsets[2] = {};
    signed long int pixel_index;
    signed long int offset_pixel_index;

    signed long int convolve_red, convolve_green, convolve_blue;

    logfile << "============================================================\n";
    logfile << "=----------------------------------------------------------=\n";
    logfile << "=----------- looping through central pixels.... -----------=\n";
    logfile << "=----------------------------------------------------------=\n";
    logfile << "============================================================\n";
    logfile << "\n";

    const int max_x_length = (std::to_string(total_x-1)).length();
    const int max_y_length = (std::to_string(total_y-1)).length();
    const int max_i_length = max_x_length+max_y_length;
    std::string *sx;
    std::string *sy;
    std::string *zi;
    const int spaces_before_kernel = 20 + max_i_length + max_y_length + max_x_length;
    const int spaces_kernel_shift = 2;
    const std::string sbk(spaces_before_kernel, ' ');
    const std::string sks(spaces_kernel_shift,  ' ');
    std::string logstr;

    int spaces_kernelsum = f2str(kernel_sum).length();
    int spaces_for_kernelsum = 12;
    int spaces_after_kernelsum = spaces_for_kernelsum - spaces_kernelsum;
    //int spaces_kernelsum = f2str(kernel_sum_).length();
    std::string *sk;
    std::string *sak;

    Stopwatch.start();
    // Loop through pixels, where the full kernel fits.
    // leaves a `kernel_order`-wide "frame" of pixels unprocessed 
    for (y = kernel_order; y < total_y-kernel_order ; ++y){
        for (x = kernel_order; x < total_x-kernel_order; ++x){

            convolve_red = 0, convolve_green = 0, convolve_blue = 0;
            pixel_index = y*total_x + x;

            for (i=0; i<=kernel_count; i++){ // i < const kernel_count

                // rewrites xy_offsets
                offset_values(kernel_size, kernel_order, i, xy_offsets);

                offset_pixel_index = pixel_index + xy_offsets[1]*total_x + xy_offsets[0];

                convolve_red    += (*(pixels_read+offset_pixel_index)).red   * kernel[i];
                convolve_green  += (*(pixels_read+offset_pixel_index)).green * kernel[i];
                convolve_blue   += (*(pixels_read+offset_pixel_index)).blue  * kernel[i];

            }

            //std::cout << "x=" << x << ", std::to_string(x).length() = " << std::to_string(x).length();
            //std::cout << "y=" << y << ", std::to_string(y).length() = " << std::to_string(y).length();
            //std::cout << "pixel_index=" << pixel_index << ", std::to_string(pixel_index).length() = " << std::to_string(pixel_index).length();
            sx = new std::string(max_x_length - std::to_string(x).length(), ' ');
            sy = new std::string(max_y_length - std::to_string(y).length(), ' ');
            zi = new std::string(max_i_length - std::to_string(pixel_index).length(), '0');

            //logfile << KukMagick::format("#%s%s [%s%s, %s%s]  kernel_sum = %s",
            //                            &zi,pixel_index, x,&sx, y,&sy, kernel_sum);
            
            logstr  = std::string("#")+
                      *zi+
                      std::to_string(pixel_index)+
                      " ["+*sx+std::to_string(x)+
                      ", "+*sy+std::to_string(y)+"] "+
                      "kernel_sum = "+f2str(kernel_sum);

            logfile << logstr << "\n";

            (*(pixels_write+pixel_index)).red   = (unsigned short) abs((convolve_red   / kernel_sum));
            (*(pixels_write+pixel_index)).green = (unsigned short) abs((convolve_green / kernel_sum));
            (*(pixels_write+pixel_index)).blue  = (unsigned short) abs((convolve_blue  / kernel_sum));

            view_convolve.sync();

        } // for x
    } // for y
    Stopwatch.end("loop through central pixels done in %ss\n");

    logfile << "\n\n\n\n\n\n\n\n\n";
    logfile << "============================================================\n";
    logfile << "=----------------------------------------------------------=\n";
    logfile << "=------------ looping through frame pixels.... ------------=\n";
    logfile << "=----------------------------------------------------------=\n";
    logfile << "============================================================\n";
    logfile << "\n";

    //if (true){
    double kernel_sum_;

    logfile << "------------------------------------------------------------\n";
    logfile << "------------ Top and bottom parts (and corners) ------------\n";
    logfile << "------------------------------------------------------------\n";
    Stopwatch.start();
    int ker_el_length[kernel_count+1];
    for (i = 0; i < kernel_count+1; ++i){
        ker_el_length[i] = static_cast<int>(f2str(kernel[i]).length());   // !!! casting size_t to int !!!
    }
    const int * kerlenmax = std::max_element(ker_el_length, ker_el_length+kernel_count+1);
    logfile << "kerlenmax = " << *kerlenmax << "\n\n";

    std::string kerelem;
    std::string *spaces;

    //const double * kermax = std::max_element(kernel, kernel+kernel_count+1);


    // Top and bottom parts of the "frame", including corners
    // { y = [0, kernel_order) ⋃ [total_y-kernel_order, total_y) }
    //  ×
    // { x = [0, total_x) }
    // 
    for (y = 0; y < total_y; ++y){
        if (y == kernel_order) { y = total_y-kernel_order; }

        for (x = 0; x < total_x; ++x){
            
            kernel_sum_ = 0;
            convolve_red = 0, convolve_green = 0, convolve_blue = 0;
            pixel_index = y*total_x + x;

            for (i=0; i<=kernel_count; i++){ // i < const kernel_count

                // rewrites xy_offsets
                offset_values(kernel_size, kernel_order, i, xy_offsets);

                if (
                x+xy_offsets[0] >= 0 && x+xy_offsets[0] < total_x
                &&
                y+xy_offsets[1] >= 0 && y+xy_offsets[1] < total_y){

                    offset_pixel_index = pixel_index + xy_offsets[1]*total_x + xy_offsets[0];

                    convolve_red    += (*(pixels_read+offset_pixel_index)).red   * kernel[i];
                    convolve_green  += (*(pixels_read+offset_pixel_index)).green * kernel[i];
                    convolve_blue   += (*(pixels_read+offset_pixel_index)).blue  * kernel[i];

                    kernel_sum_ += kernel[i];
                }

            } // for i

            logstr = "";
            bool logfile2cond = (y == 385 && (x == 0 || x == 1 || x == 2)) ||
                                (y == 0 && (x == 385));
            if(logfile2cond){
                zi = new std::string(max_i_length - std::to_string(pixel_index).length(), '0');
                logfile2 << "\n#" + *zi + std::to_string(pixel_index) + " \n";
            }

            for (i=0; i<=kernel_count; i++){ // log
                // rewrites xy_offsets
                offset_values(kernel_size, kernel_order, i, xy_offsets);
                
                if (
                x+xy_offsets[0] >= 0 && x+xy_offsets[0] < total_x
                &&
                y+xy_offsets[1] >= 0 && y+xy_offsets[1] < total_y){
                    kerelem = f2str(kernel[i]);
                } else {
                    kerelem = "~";
                }

                spaces_kernelsum = f2str(kernel_sum_).length();
                spaces_after_kernelsum = spaces_for_kernelsum - spaces_kernelsum;
                sk  = new std::string(spaces_kernelsum,       ' ');
                sak = new std::string(spaces_after_kernelsum, ' ');
                
                if (i == kernel_size*kernel_order){ // when on the first element of the middle row
                    sx = new std::string(max_x_length - std::to_string(x).length(), ' ');
                    sy = new std::string(max_y_length - std::to_string(y).length(), ' ');
                    zi = new std::string(max_i_length - std::to_string(pixel_index).length(), '0');

                    logstr += "\n"+
                              std::string("#")+
                              *zi+
                              std::to_string(pixel_index)+
                              " ["+*sx+std::to_string(x)+
                              ", "+*sy+std::to_string(y)+"] "+
                              "kernel_sum = "+f2str(kernel_sum_)+
                              *sak;
                    
                    logstr += sks+" |";
                    
                    if (logfile2cond){
                      logfile2 << "|sbk|="+std::to_string(sbk.length())+" |sks|="+std::to_string(sks.length())
                               << " kernel_sum_="+f2str(kernel_sum_)
                               << " spaces_kernelsum="+std::to_string(spaces_kernelsum)
                               << " |sk|=" +std::to_string((*sk).length())
                               << " |sak|=" +std::to_string((*sak).length())
                               << " |#zi+pixel_index+sx+x+sy+y+kernel_sum|="+
                               std::to_string(
                                   ("\n"+
                                   std::string("#")+
                                   *zi+
                                   std::to_string(pixel_index)+
                                   " ["+*sx+std::to_string(x)+
                                   ", "+*sy+std::to_string(y)+"] "+
                                   "kernel_sum = "+f2str(kernel_sum_)+
                                   sks).length())
                               << "\n";
                    }

                } else if (i%kernel_size==0){ // when on the first element of a row
                    logstr += "\n" + sbk + *sk + *sak + sks + " |";

                    if (logfile2cond){
                      logfile2 << "|sbk|=" + std::to_string(sbk.length()) + " |sks|=" + std::to_string(sks.length())
                               << " kernel_sum_=" + f2str(kernel_sum_)
                               << " spaces_kernelsum=" + std::to_string(spaces_kernelsum)
                               << " |sk|=" + std::to_string((*sk).length())
                               << " |sak|=" + std::to_string((*sak).length())
                               << " |sbk+sk+sks|=" +
                                      std::to_string(("\n" + sbk + *sk + sks).length())
                               << "\n";
                    }

                }

                //if (xy_offsets[0] == 0 && xy_offsets[1] == 0){
                //    kerelem = "[" + kerelem + "]";
                //} else {
                //    kerelem = " " + kerelem + " ";
                //}

                spaces = new std::string(*kerlenmax - kerelem.length(), ' ');
                logstr += *spaces + kerelem;

                if (i%kernel_size==kernel_size-1){ // when on the last element of a row
                    logstr += "|";
                } else {
                    logstr += ", ";
                }

            } // for i (log)

            logstr += "\n";
            logfile << logstr;

            (*(pixels_write+pixel_index)).red   = (unsigned short) abs((convolve_red   / kernel_sum_));
            (*(pixels_write+pixel_index)).green = (unsigned short) abs((convolve_green / kernel_sum_));
            (*(pixels_write+pixel_index)).blue  = (unsigned short) abs((convolve_blue  / kernel_sum_));

            view_convolve.sync();
            
        } // for x
    } // for y

    logfile << "\n\n\n";
    logfile << "------------------------------------------------------------\n";
    logfile << "------------------- Left and right parts -------------------\n";
    logfile << "------------------------------------------------------------\n";
    logfile << "\n";

    // Left and right parts of the "frame"
    // { y = [kernel_order, total_y-kernel_order) }
    //  ×
    // { x = [0, kernel_order) ⋃ [total_x-kernel_order, total_x] }
    //
    for (x = 0; x < total_x; ++x){
        if (x == kernel_order) { x = total_x-kernel_order; }

        for (y = kernel_order; y < total_y-kernel_order; ++y){

            kernel_sum_ = 0;
            convolve_red = 0, convolve_green = 0, convolve_blue = 0;
            pixel_index = y*total_x + x;

            for (i=0; i<=kernel_count; i++){ // i < const kernel_count

                // rewrites xy_offsets
                offset_values(kernel_size, kernel_order, i, xy_offsets);

                if (
                x+xy_offsets[0] >= 0 && x+xy_offsets[0] < total_x
                &&
                y+xy_offsets[1] >= 0 && y+xy_offsets[1] < total_y){

                    offset_pixel_index = pixel_index + xy_offsets[1]*total_x + xy_offsets[0];

                    convolve_red    += (*(pixels_read+offset_pixel_index)).red   * kernel[i];
                    convolve_green  += (*(pixels_read+offset_pixel_index)).green * kernel[i];
                    convolve_blue   += (*(pixels_read+offset_pixel_index)).blue  * kernel[i];

                    kernel_sum_ += kernel[i];
                }

            } // for i

            logstr = "";

            for (i=0; i<=kernel_count; i++){ // log
                // rewrites xy_offsets
                offset_values(kernel_size, kernel_order, i, xy_offsets);
                
                if (
                x+xy_offsets[0] >= 0 && x+xy_offsets[0] < total_x
                &&
                y+xy_offsets[1] >= 0 && y+xy_offsets[1] < total_y){
                    kerelem = f2str(kernel[i]);
                } else {
                    kerelem = "~";
                }

                spaces_kernelsum = f2str(kernel_sum_).length();
                spaces_after_kernelsum = spaces_for_kernelsum - spaces_kernelsum;
                sk  = new std::string(spaces_kernelsum,       ' ');
                sak = new std::string(spaces_after_kernelsum, ' ');
                
                if (i == kernel_size*kernel_order){ // when on the first element of the middle row
                    sx = new std::string(max_x_length - std::to_string(x).length(), ' ');
                    sy = new std::string(max_y_length - std::to_string(y).length(), ' ');
                    zi = new std::string(max_i_length - std::to_string(pixel_index).length(), '0');

                    logstr += "\n"+
                              std::string("#")+
                              *zi+
                              std::to_string(pixel_index)+
                              " ["+*sx+std::to_string(x)+
                              ", "+*sy+std::to_string(y)+"] "+
                              "kernel_sum = "+f2str(kernel_sum_)+
                              *sak;
                    
                    logstr += sks+" |";

                } else if (i%kernel_size==0){ // when on the first element of a row
                    logstr += "\n" + sbk + *sk + *sak + sks + " |";

                }

                spaces = new std::string(*kerlenmax - kerelem.length(), ' ');
                logstr += *spaces + kerelem;

                if (i%kernel_size==kernel_size-1){ // when on the last element of a row
                    logstr += "|";
                } else {
                    logstr += ", ";
                }

            } // for i (log)

            logstr += "\n";
            logfile << logstr;

            (*(pixels_write+pixel_index)).red   = (unsigned short) abs((convolve_red   / kernel_sum_));
            (*(pixels_write+pixel_index)).green = (unsigned short) abs((convolve_green / kernel_sum_));
            (*(pixels_write+pixel_index)).blue  = (unsigned short) abs((convolve_blue  / kernel_sum_));

            view_convolve.sync();


        } // for y
    } // for x

    Stopwatch.end("loop through  frame  pixels done in %ss\n");



    //} // if true/false






    return void();
}




// ===== Unsharp ===== //


void KukMagick::Image::gaussianUnSharp5x5(){
    this->convolve(5, kernel_gaussianunsharp5x5);
}




// ===== Edge detection ===== //


void KukMagick::Image::sobelEdges(){
    KukMagick::Image copyof(*this);

    this->convolve(3, kernel_sobel_x_edges);
    copyof.convolve(3, kernel_sobel_y_edges);

    

}


void KukMagick::Image::meanGradientEdges(){
    KukMagick::Image copyof(*this);

    this->convolve(3, kernel_sobel_x_edges);
    copyof.convolve(3, kernel_sobel_y_edges);

    this->composite(copyof, 0, 0, MagickLib::PlusCompositeOp);
}
void KukMagick::Image::meanGradientEdges_normalized(){
    KukMagick::Image copyof(*this);

    this->convolve(3, kernel_sobel_x_edges_normalized);
    copyof.convolve(3, kernel_sobel_y_edges_normalized);

    this->composite(copyof, 0, 0, MagickLib::PlusCompositeOp);
}

void KukMagick::Image::laplacianEdges3x3_weak(){
    this->convolve(3, kernel_laplacian_3x3_weak);
}
void KukMagick::Image::laplacianEdges3x3(){
    this->convolve(3, kernel_laplacian_3x3);
}
void KukMagick::Image::laplacianEdges5x5_weak(){
    this->convolve(5, kernel_laplacian_5x5_weak);
}
void KukMagick::Image::laplacianEdges5x5(){
    this->convolve(5, kernel_laplacian_5x5);
}







