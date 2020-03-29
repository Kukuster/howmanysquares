FROM ubuntu:18.04
WORKDIR /usr/src/howmanysquares
# c++ code will be mounted to /usr/src/howmanysquares/source
COPY . .
RUN chmod -fc a+x compile.sh

RUN apt-get -y update    &&    apt-get -y install clang graphicsmagick-libmagick-dev-compat    &&    ldconfig
# you likely want to run `apt-get -y autoremove` as well to remove old redundant libraries for around 50MB which are obsoleted by the new ones from the Magick++ installation 
# although, you probably don't want to do it in this docker image.
# because those obsolete libs are part of the image this one builds FROM, doing autoremove showed to increase image size by around 50MB.


CMD ["./compile.sh"]

#LABEL Name=compiler_clang Version=0.0.1
