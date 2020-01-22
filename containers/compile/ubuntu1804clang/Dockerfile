FROM ubuntu:18.04
WORKDIR /usr/src/howmanysquares
# code will be mounted to the /usr/src/howmanysquares/hellomagick_cpp 
COPY . .

RUN apt-get -y update    &&    apt-get -y install clang graphicsmagick-libmagick-dev-compat    &&    ldconfig


# for stability and compatibility reasons,
# because it's the GraphicsMagick++-config command is what gives actual exact keys required for proper compilation of a C++ with Magick++ library,
# and because output of this command substantially depends on the platform,
# it was decided to calculate those keys beforehand during the building of the image
RUN touch compile    &&    chmod -Rfc 775 compile    &&    echo '#!/bin/bash' > compile    &&    magickkeys=`GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs`    &&    echo 'clang++ -o ./hmsbin/showsquares ./hellomagick_cpp/hellomagick.cpp ' $magickkeys >> compile

CMD ["./compile"]

#LABEL Name=helloworld_cppclang Version=0.0.1
