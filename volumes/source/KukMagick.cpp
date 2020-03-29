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
 * @return offset indices in square kernel relative to the central element
 *  f.e. 0th, 4th and 7th elements in 3x3 kernel have offsets (-1,-1), (0,0) and (0,1) respectively
 *  @x and @y values have to be a whole number spanning [-kernel_order, kernel_order]
 * 
 */
signed short int* KukMagick::offset_values(unsigned short int kernel_size,
                                           unsigned short int kernel_order,
                                           unsigned short int kernel_index,
                                           signed short int *xy)
{
    signed short int res = kernel_index % kernel_size;

    //static signed short int xy[2];

    xy[0] = (signed short int)(res - kernel_order);
    xy[1] = (signed short int)( ((kernel_index - res) / kernel_size) - kernel_order );

    // static signed short int xy[2] =
    // {  (signed short int) ( x - kernel_order ),
    //    (signed short int) ( ((kernel_index - x) / kernel_size) - kernel_order )  };

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




//std::string KukMagick::timestamp;
//KukMagick::HMSBIN_INPUT = getenv("HMSBIN_INPUT"), KukMagick::HMSBIN_OUTPUT = getenv("HMSBIN_OUTPUT");


// class KukStopwatch
// {
//     private:
//         std::chrono::_V2::system_clock::time_point start;
//         std::time_t start_time;
//         std::string start_date_time;

//         std::chrono::_V2::system_clock::time_point split;
//         std::chrono::duration<double> elapsed_seconds;

//         std::chrono::_V2::system_clock::time_point end;
//         std::time_t end_time;

//     public:
//         std::string timestamp(std::time_t time);

//         void start(std::string text = "");
//         void split(std::string text = "split at %ss\n");
//         void end(std::string text = "execution time: %ss\n");

// };




// ===== class KukStopwatch ===== //

std::string KukMagick::KukStopwatch::getStart_timestamp(){
    return this->start_timestamp;
};
// void KukMagick::KukStopwatch::setStart_timestamp(){
//     this->start_timestamp = std::to_string(this->start_time);
// };

// // std::chrono::_V2::system_clock::time_point start = std::chrono::system_clock::now();
// auto start = std::chrono::system_clock::now();
// std::time_t start_time = std::chrono::system_clock::to_time_t(start);
// std::string date_time = std::ctime(&start_time);
// KukMagick::timestamp = std::to_string(start_time);


std::string KukMagick::KukStopwatch::timestamp(std::time_t time){
    return std::to_string(time);
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


// class KukMagician
// {
//     private:

//     /* not very */ private:
//         std::string timestamp;
//         std::string HMSBIN_INPUT, HMSBIN_OUTPUT;
//         KukStopwatch stopwatch;

//     public:
//         std::string getTimestamp();
//         void        setTimestamp();

//         std::string getHMSBIN_INPUT();
//         void        setHMSBIN_INPUT();

//         std::string getHMSBIN_OUTPUT();
//         void        setHMSBIN_OUTPUT();

//         KukStopwatch* stopwatch();
//         void stopwatch();

//         void initInputs();

//         std::ofstream kuklog(std::string name = "");
//         //void kuklog(std::string text);
//         //void kuklog(char* text);

// };

// ===== class KukMagician ===== //

KukMagician::KukMagician(){
  
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

// KukStopwatch KukMagick::KukMagician::getStopwatch(){
//   return this->stopwatch;
// }

// void KukMagick::KukMagician::setStopwatch(){
//   KukStopwatch * newstopwatch;
//   this->stopwatch = *newstopwatch;
// }






std::ofstream KukMagick::KukMagician::kuklog(std::string name)
{

    std::ofstream logfile;
    std::string s = this->getHMSBIN_OUTPUT() + "/" + this->stopwatch.getStart_timestamp() + "_" + name + ".log";
    logfile.open(s, std::ios_base::app);

    return logfile;

}



// ===== Blur filters ===== //

// void KukMagick::Image(){
//     Image();
// }

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


/*

void KukMagick::Image::smartBlur(){

    this->evenBlur3x3();
    this->gaussianBlur5x5();

    KukMagick::Image RGB_RedChannel(*this);
    KukMagick::Image RGB_GreenChannel(*this);
    KukMagick::Image RGB_BlueChannel(*this);


    const Magick::Image *image(this);
    const unsigned long image_columns = (long) image->columns();

    KukMagick::Image *convolve_image(this);
    //convolve_image = this;

    if (convolve_image == (Image *)NULL)
        return;
    //convolve_image->storage_class = DirectClass;
    //(this);
    
    long y, width;
    MagickPassFail status;

    for (y=0; y < (long) convolve_image->rows; y++)
      {
        const Magick::PixelPacket
          *__restrict__ p;

        Magick::PixelPacket
          *__restrict__ q;

        long
          x;

        MagickBool
          thread_status;

        thread_status=status;
        if (thread_status == MagickFail)
          continue;

        ///*
        //  Acquire rectangle of columns+width high, and width tall.
        //
        //size_t columns = 196; size_t rows = 162; 
        //Pixels view(*convolve_image);
        //MagickLib::PixelPacket *pixels = view.get(38, 36, columns, rows);

        p=AcquireImagePixels(image,-width/2,y-width/2,image->columns+width,width,
                             exception);
        ///*
        //  Set one row.
        //
        q=SetImagePixelsEx(convolve_image,0,y,convolve_image->columns,1,exception);
        if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
          thread_status=MagickFail;

        if (thread_status != MagickFail)
          {
            for (x=0; x < (long) convolve_image->columns; x++)
              {
                float_packet_t
                  pixel;


                const PixelPacket
                  * restrict r;

                long
                  u,
                  v;

                const float_quantum_t
                  * restrict k;

                r=p;
                pixel=zero;
                k=normal_kernel;
                if (is_grayscale && !matte)
                  {
                    ///* G /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          pixel.red+=k[u]*r[u].red;
                        k+= width;
                        r+=image->columns+width;
                      }
                    q->red=q->green=q->blue=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->opacity=OpaqueOpacity;
                  }
                else if (!matte)
                  {
                    ///* RGB /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          {
                            pixel.red+=k[u]*r[u].red;
                            pixel.green+=k[u]*r[u].green;
                            pixel.blue+=k[u]*r[u].blue;
                          }
                        k+=width;
                        r+=image->columns+width;
                      }
                    q->red=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->green=RoundFloatQuantumToIntQuantum(pixel.green);
                    q->blue=RoundFloatQuantumToIntQuantum(pixel.blue);
                    q->opacity=OpaqueOpacity;
                  }
                else
                  {
                    ///* RGBA /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          {
                            pixel.red+=k[u]*r[u].red;
                            pixel.green+=k[u]*r[u].green;
                            pixel.blue+=k[u]*r[u].blue;
                            pixel.opacity+=k[u]*r[u].opacity;
                          }
                        k+=width;
                        r+=image->columns+width;
                      }
                    q->red=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->green=RoundFloatQuantumToIntQuantum(pixel.green);
                    q->blue=RoundFloatQuantumToIntQuantum(pixel.blue);
                    q->opacity=RoundFloatQuantumToIntQuantum(pixel.opacity);
                  }
                p++;
                q++;
              }
            if (!SyncImagePixelsEx(convolve_image,exception))
              thread_status=MagickFail;
          }

        if (monitor_active)
          {
            unsigned long
              thread_row_count;

#if defined(HAVE_OPENMP)
#  pragma omp atomic
#endif
            row_count++;
#if defined(HAVE_OPENMP)
#  pragma omp flush (row_count)
#endif
            thread_row_count=row_count;
            if (QuantumTick(thread_row_count,image->rows))
              if (!MagickMonitorFormatted(thread_row_count,image->rows,exception,
                                          ConvolveImageText,
                                          convolve_image->filename,
                                          order))
                thread_status=MagickFail;
          }

        if (thread_status == MagickFail)
          {
            status=MagickFail;
#if defined(HAVE_OPENMP)
#  pragma omp flush (status)
#endif
          }
      }

  




    *this = RGB_RedChannel;

}
//*/

void KukMagick::Image::kukConvolve(Magick::Image * read_image,
                                   Magick::Image * writable_copy_image,
                                   const unsigned short int kernel_size,
                                   const double * kernel,
                                   const double kernel_sum)
{
  KukMagician Magician;
  std::ofstream logfile = Magician.kuklog("KukMagick");
  logfile << "hello from KukMagick::Image::kukConvolve()\n";

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

            (*(pixels_write+pixel_index)).red   = (unsigned short) abs((convolve_red   / kernel_sum));
            (*(pixels_write+pixel_index)).green = (unsigned short) abs((convolve_green / kernel_sum));
            (*(pixels_write+pixel_index)).blue  = (unsigned short) abs((convolve_blue  / kernel_sum));

            view_convolve.sync();

        } // for x
    } // for y


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
















/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%     C o n v o l v e I m a g e                                               %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  ConvolveImage() applies a custom convolution kernel to the image.
%
%  The format of the ConvolveImage method is:
%
%      Image *ConvolveImage(const Image *image,const unsigned int order,
%        const double *kernel,ExceptionInfo *exception)
%
%  A description of each parameter follows:
%
%    o image: The image.
%
%    o order: The number of columns and rows in the filter kernel.
%
%    o kernel: An array of double representing the convolution kernel.
%
%    o exception: Return any errors or warnings in this structure.
%
%
*/
/*
#define ConvolveImageText "[%s] Convolve: order %u..."
MagickExport Magick::Image *ConvolveImage(const Magick::Image *__restrict__ image,const unsigned int order,
                                  const double *__restrict__ kernel,MagickLib::ExceptionInfo *exception)
{
#if QuantumDepth < 32
  typedef float float_quantum_t;
  typedef MagickLib::FloatPixelPacket float_packet_t;
#  define RoundFloatQuantumToIntQuantum(value) RoundFloatToQuantum(value)
#else
  typedef double float_quantum_t;
  typedef DoublePixelPacket float_packet_t;
#  define RoundFloatQuantumToIntQuantum(value) RoundDoubleToQuantum(value)
#endif

  float_quantum_t
    *__restrict__ normal_kernel;

  Magick::Image
    *convolve_image;

  long
    width,
    y;

  MagickPassFail
    status;

  const MagickBool
    is_grayscale = image->is_grayscale;

  const MagickBool
    matte=((image->matte) || (image->colorspace == CMYKColorspace));

  ///*
    // Initialize convolve image attributes.
  //
  assert(image != (Magick::Image *) NULL);
  assert(image->signature == MagickSignature);
  assert(exception != (MagickLib::ExceptionInfo *) NULL);
  assert(exception->signature == MagickSignature);
  width=(long) order;
  if ((width % 2) == 0)
    Magick::ThrowImageException3(OptionError,UnableToConvolveImage,
                         KernelWidthMustBeAnOddNumber);
  if (((long) image->columns < width) || ((long) image->rows < width))
    ThrowImageException3(OptionError,UnableToConvolveImage,
                         ImageSmallerThanKernelWidth);
  convolve_image=CloneImage(image,image->columns,image->rows,MagickTrue,exception);
  if (convolve_image == (Image *) NULL)
    return((Image *) NULL);
  convolve_image->storage_class=DirectClass;
  {
    //*
    //   Build normalized kernel.

    //   0x0.25 --> 3x3
    //   0x0.5  --> 5x5
    //   0x1    --> 9x9
    //   0x2    --> 17x17
    //   0x3    --> 25x25
    //   0x4    --> 33x33
    //   0x5    --> 41x41
    //   0x6    --> 49x49
    //
    double
      normalize;

    register long
      i;

    normal_kernel=MagickAllocateAlignedMemory(float_quantum_t *,
                                              MAGICK_CACHE_LINE_SIZE,
                                              width*width*sizeof(float_quantum_t));
    if (normal_kernel == (float_quantum_t *) NULL)
      {
        DestroyImage(convolve_image);
        ThrowImageException(ResourceLimitError,MemoryAllocationFailed,
                            MagickMsg(OptionError,UnableToConvolveImage));
      }
    normalize=0.0;
    for (i=0; i < (width*width); i++)
      normalize+=kernel[i];
    if (AbsoluteValue(normalize) <= MagickEpsilon)
      normalize=1.0;
    normalize=1.0/normalize;
    for (i=0; i < (width*width); i++)
      {
        normal_kernel[i]=normalize*kernel[i];
      }
  }

  if (LogMagickEvent(TransformEvent,GetMagickModule(),
                     "  ConvolveImage with %ldx%ld kernel:",width,width))
    {
      ///*
      //  Log convolution matrix.
      //
      char
        cell_text[MaxTextExtent],
        row_text[MaxTextExtent];

      const double
        *k;

      long
        u,
        v;

      k=kernel;
      for (v=0; v < width; v++)
        {
          *row_text='\0';
          for (u=0; u < width; u++)
            {
              FormatString(cell_text,"%#12.4g",*k++);
              (void) strlcat(row_text,cell_text,sizeof(row_text));
              if (u%5 == 4)
                {
                  (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                        "   %.64s", row_text);
                  *row_text='\0';
                }
            }
          if (u > 5)
            (void) strlcat(row_text,"\n",sizeof(row_text));
          if (row_text[0] != '\0')
            (void) LogMagickEvent(TransformEvent,GetMagickModule(),
                                  "   %s", row_text);
        }
    }

  status=MagickPass;
  ///*
  //  Convolve image.
  //
  {
    unsigned long
      row_count=0;

    MagickBool
      monitor_active;

    float_packet_t
      zero;

    (void) memset(&zero,0,sizeof(float_packet_t));

    monitor_active=MagickMonitorActive();

#if defined(HAVE_OPENMP)
#  if defined(TUNE_OPENMP)
#    pragma omp parallel for schedule(runtime) shared(row_count, status)
#  else
#    if defined(USE_STATIC_SCHEDULING_ONLY)
#      pragma omp parallel for schedule(static,4) shared(row_count, status)
#    else
#      pragma omp parallel for schedule(guided) shared(row_count, status)
#    endif
#  endif
#endif
    for (y=0; y < (long) convolve_image->rows; y++)
      {
        const Magick::PixelPacket
          *__restrict__ p;

        Magick::PixelPacket
          *__restrict__ q;

        long
          x;

        MagickBool
          thread_status;

        thread_status=status;
        if (thread_status == MagickFail)
          continue;

        ///*
        //  Acquire rectangle of columns+width high, and width tall.
        //
        p=AcquireImagePixels(image,-width/2,y-width/2,image->columns+width,width,
                             exception);
        ///*
        //  Set one row.
        //
        q=SetImagePixelsEx(convolve_image,0,y,convolve_image->columns,1,exception);
        if ((p == (const PixelPacket *) NULL) || (q == (PixelPacket *) NULL))
          thread_status=MagickFail;

        if (thread_status != MagickFail)
          {
            for (x=0; x < (long) convolve_image->columns; x++)
              {
                float_packet_t
                  pixel;


                const PixelPacket
                  * restrict r;

                long
                  u,
                  v;

                const float_quantum_t
                  * restrict k;

                r=p;
                pixel=zero;
                k=normal_kernel;
                if (is_grayscale && !matte)
                  {
                    ///* G /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          pixel.red+=k[u]*r[u].red;
                        k+= width;
                        r+=image->columns+width;
                      }
                    q->red=q->green=q->blue=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->opacity=OpaqueOpacity;
                  }
                else if (!matte)
                  {
                    ///* RGB /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          {
                            pixel.red+=k[u]*r[u].red;
                            pixel.green+=k[u]*r[u].green;
                            pixel.blue+=k[u]*r[u].blue;
                          }
                        k+=width;
                        r+=image->columns+width;
                      }
                    q->red=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->green=RoundFloatQuantumToIntQuantum(pixel.green);
                    q->blue=RoundFloatQuantumToIntQuantum(pixel.blue);
                    q->opacity=OpaqueOpacity;
                  }
                else
                  {
                    ///* RGBA /
                    for (v=0; v < width; v++)
                      {
                        for (u=0; u < width; u++)
                          {
                            pixel.red+=k[u]*r[u].red;
                            pixel.green+=k[u]*r[u].green;
                            pixel.blue+=k[u]*r[u].blue;
                            pixel.opacity+=k[u]*r[u].opacity;
                          }
                        k+=width;
                        r+=image->columns+width;
                      }
                    q->red=RoundFloatQuantumToIntQuantum(pixel.red);
                    q->green=RoundFloatQuantumToIntQuantum(pixel.green);
                    q->blue=RoundFloatQuantumToIntQuantum(pixel.blue);
                    q->opacity=RoundFloatQuantumToIntQuantum(pixel.opacity);
                  }
                p++;
                q++;
              }
            if (!SyncImagePixelsEx(convolve_image,exception))
              thread_status=MagickFail;
          }

        if (monitor_active)
          {
            unsigned long
              thread_row_count;

#if defined(HAVE_OPENMP)
#  pragma omp atomic
#endif
            row_count++;
#if defined(HAVE_OPENMP)
#  pragma omp flush (row_count)
#endif
            thread_row_count=row_count;
            if (QuantumTick(thread_row_count,image->rows))
              if (!MagickMonitorFormatted(thread_row_count,image->rows,exception,
                                          ConvolveImageText,
                                          convolve_image->filename,
                                          order))
                thread_status=MagickFail;
          }

        if (thread_status == MagickFail)
          {
            status=MagickFail;
#if defined(HAVE_OPENMP)
#  pragma omp flush (status)
#endif
          }
      }
  }
  MagickFreeAlignedMemory(normal_kernel);
  if (MagickFail == status)
    {
      DestroyImage(convolve_image);
      convolve_image=(Image *) NULL;
    }
  else
    {
      convolve_image->is_grayscale=is_grayscale;
    }
  return(convolve_image);
}




//*/






