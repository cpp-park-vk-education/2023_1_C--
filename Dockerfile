FROM ubuntu:20.04 AS builder

RUN apt -y update && \
    echo "tzdata "Geographic area" select 8" | debconf-set-selections && \
    apt install -y tzdata

RUN apt-get update && \
    apt-get install -y sudo && \
    sudo apt install -y build-essential

WORKDIR /src

RUN mkdir /src/server

RUN mkdir /QtWebApp

RUN sudo apt-get install -y qtbase5-dev
RUN sudo apt install -y qt5-qmake
RUN sudo apt install -y cmake
RUN sudo apt install -y libqt5sql5-psql

RUN sudo apt install -y wget unzip

RUN wget https://github.com/fffaraz/QtWebApp/archive/refs/tags/v1.8.6.zip

RUN mv ./*.zip /QtWebApp
RUN unzip /QtWebApp/*.zip -d /QtWebApp && rm -f /QtWebApp/*.zip


RUN cd /QtWebApp/QtWebApp-1.8.6/QtWebApp && mkdir build && cd ./build/ && qmake ../*.pro && make && cd /src
RUN cp -r /QtWebApp/QtWebApp-1.8.6/QtWebApp/build/libQtWebApp.so.1.8.6 /usr/local/lib/
RUN cp -r /QtWebApp/QtWebApp-1.8.6/QtWebApp/build/libQtWebApp.so.1 /usr/local/lib/

RUN cp -r /QtWebApp/QtWebApp-1.8.6/QtWebApp/ /usr/local/include

RUN cd /usr/local/include/QtWebApp/ && rm -r build doc Dox* *.pro && cd /src

COPY . /src/

RUN rm -rf ./build

RUN cmake -B ./build -S .

RUN cd ./build/server && make

CMD [ "./build/server/server" ]

EXPOSE 1488