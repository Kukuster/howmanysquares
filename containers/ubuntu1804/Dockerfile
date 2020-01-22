FROM ubuntu:18.04
RUN apt-get -y update && apt-get install -y
WORKDIR /usr/src/helloworld
COPY . .
CMD ["./helloworld/helloworld"]

#LABEL Name=helloworld_cppclang Version=0.0.1
