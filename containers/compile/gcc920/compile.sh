#!/bin/bash
# for stability and compatibility reasons,
# because it's the GraphicsMagick++-config command is what gives actual exact keys required for proper compilation of a C++ with Magick++ library,
# and because output of this command substantially depends on the platform,
# it was decided to calculate those keys beforehand during the building of the image

source="./source/showsquares.cpp ./source/KukMagick.cpp ./source/KukMagician.cpp"
output="./hmsbin/showsquares"
magickkeys=`GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`

TIMEFORMAT='compilation time: %3Rs'
time {
    g++ -o $output $source $magickkeys
 }

