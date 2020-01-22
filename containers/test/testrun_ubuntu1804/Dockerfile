FROM ubuntu:18.04
#RUN apt-get -y update && apt-get install -y
WORKDIR /usr/src/howmanysquares
COPY . .

# Magick++ 
# graphicsmagick-libmagick-dev-compat
RUN apt-get -y update    &&    apt-get -y install graphicsmagick-libmagick-dev-compat libjpeg62    &&    ldconfig

CMD ["./hmsbin/showsquares"]

#LABEL Name=howmanysquares Version=0.0.1
