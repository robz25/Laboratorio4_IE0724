# Definimos OS base
FROM ubuntu:20.04

ENV TZ=America/Costa_Rica
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime \
    && echo $TZ > /etc/timezone

# Algo de información
LABEL version="1.0"
LABEL description="Custom docker image for a Gtest example"

# Choose user root
USER root
RUN apt-get update \
    && apt-get --yes --no-install-recommends install \
       build-essential make cmake git wget \
       libgmp-dev libmpfr-dev libboost-dev \
       libcgal-qt5-dev libgtest-dev \
    && cd /usr/src/gtest/ \
    && cmake CMakeLists.txt \
    && make
    
RUN cd ~ && wget https://github.com/CGAL/cgal/releases/download/v5.2.1/CGAL-5.2.1.zip && \
    unzip CGAL-5.2.1.zip && \
    cd ~/CGAL-5.2.1 && \
    cmake -B build -DCGAL_HEADER_ONLY=OFF -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release && \
    cd ~/CGAL-5.2.1/build && sudo make install

# Crear carpeta del proyecto
RUN mkdir -p /home/laboratorio4/ && cd /home/laboratorio4/ && /
    git clone https://github.com/robz25/Laboratorio4_IE0724.git .

