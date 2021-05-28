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

# Instalar dependencias desde apt
RUN apt-get update \
    && apt-get --yes --no-install-recommends install \
       build-essential make cmake git wget unzip \
       libgmp-dev libmpfr-dev libboost-dev \
       libcgal-qt5-dev libgtest-dev \
    && cd /usr/src/gtest/ \
    && cmake CMakeLists.txt \
    && make

# Descargar, compilar e instalar versión 5.2.1 de CGAL
RUN cd ~ \
    && wget --no-check-certificate https://github.com/CGAL/cgal/releases/download/v5.2.1/CGAL-5.2.1.zip \
    && unzip CGAL-5.2.1.zip \
    && cd ~/CGAL-5.2.1 \
    && cmake -B build -DCGAL_HEADER_ONLY=OFF -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --config Release \
    && cd ~/CGAL-5.2.1/build \
    && make install

# Copiar proyecto
RUN mkdir -p /home/laboratorio4

# Copia desde git
# RUN cd ~ \
#     && wget --no-check-certificate https://github.com/robz25/Laboratorio4_IE0724/archive/refs/heads/main.zip \
#     && unzip main.zip \
#     && mv -r ~/Laboratorio4_IE0724-main /home/laboratorio4

# Copia local
COPY include /home/laboratorio4/include
COPY src /home/laboratorio4/src
COPY test /home/laboratorio4/test
COPY CMakeLists.txt /home/laboratorio4/CMakeLists.txt

COPY puntos.txt /home/laboratorio4/puntos.txt
COPY 1puntosTest.txt /home/laboratorio4/1puntosTest.txt
COPY 2puntosTest.txt /home/laboratorio4/2puntosTest.txt

COPY puntosInvalidos1.txt /home/laboratorio4/puntosInvalidos1.txt
COPY puntosInvalidos2.txt /home/laboratorio4/puntosInvalidos2.txt
COPY puntosInvalidos3.txt /home/laboratorio4/puntosInvalidos3.txt

# Configurar y compilar el proyecto
RUN mkdir -p /home/laboratorio4 \
    && cd /home/laboratorio4 \
    && cmake -B /home/laboratorio4/build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build /home/laboratorio4/build --config Release

# Ejecutar tests
RUN cd /home/laboratorio4 && \
    ./build/Tests
