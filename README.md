<h1> Proyecto1_IE0724 </h1>

<h2> Curso: Laboratorio de programación IE - 0724</h2>

<h2> Tema: Creación de un contenedor de Docker para ejecución de pruebas unitarias automatizadas mediante GTest en C++ </h2>

<h2>Integrantes:</h2>

<p>
  <ul>
    <li> Robin González Ricz, B43011.           </li>
    <li> Jonathan Ramírez Hernández, B55730.    </li>
    <li> Emilio Javier Rojas Álvarez, B15680.   </li>
  </ul>
</p>

<hr>

<h3>Ejecutar Pruebas</h3>  

Luego de haber compilado, desde la raiz del proyecto, ejecutar:
```
./build/Tests
```

<h3>Ejecutar Pruebas con Docker</h3>
```
docker build . --file Dockerfile --tag img
```


## Tabla de contenidos
* [Síntesis del funcionamiento del programa](#program-info)
* [Instrucciones de compilación y ejecución](#instructions)
* [Pasos a seguir con una instalación limpia de ubuntu 20.04 mínima.](#ubuntu)
* [Requerimientos mínimos del sistema](#requisitos)

<h3> Requerimientos mínimos del sistema </h3>
<p>
  <ul>
    <li> Ubuntu versión 20.04.2 LTS           </li>
    <li> g++ versión 9.3.0                    </li>
    <li> CMake 3.16.3                         </li>
    <li> CGAL 5.2.1                           </li>
    <li> QT versión 5.12.8                    </li>
  </ul>
</p>


<h3>  Síntesis del funcionamiento del programa  </h3>
  <p >
      Se tiene un dockerfile encargado de generar un contenedor con todos los requisitos de entorno para ejecutar nuestro código
  </p>

  <p>
      Se integra Gtest mediante un Cmake y con comandos RUN se realiza la compulación del código fuente y ejecución de pruebas tras la creación del contenedor
  </p>


<h3> Instrucciones de compilación y ejecución </h3>
<h3>Ejecutar Pruebas</h3>  

Luego de haber compilado, desde la raiz del proyecto, ejecutar:
```
./build/Tests
```

<h3>Ejecutar Pruebas con Docker</h3>
```
docker build . --file Dockerfile --tag img
```

  <p>
      Para la compilación y ejecución del programa es necesario tener instalada la herramienta de automatización de código CMake.
      Se debe descargar el repositorio y dentro de la carpeta en la que están incluidos los directorios de "include" y "src" ejecutar las siguientes
      instrucciones en la consola (terminal) de comandos:
  </p>

  ```
  mkdir build && cd build
  cmake ..
  make
  ./Proyecto1 ../[nombre_del_archivo].txt
  ```

  <p>
      Ejemplo de la última instrucción del ejecutable:
                  ./Proyecto1 ../entrada1.txt
  </p>



  <h3>Pasos a seguir con una instalación limpia de ubuntu 20.04 mínima. </h3>

 - Se requiere interfaz gráfica, se usa la interfaz por defecto, gnome.
 - Instalar todas las actualizaciones.
 - En una terminal.
   - Instalar programas y librerías requeridas:
     ```
     sudo apt install -y build-essential make cmake git
     sudo apt install -y libgmp-dev libmpfr-dev libboost-dev libcgal-qt5-dev
     ```
   - Descargar y descomprimir CGAL 5.2.1:
     ```
     cd ~
     wget https://github.com/CGAL/cgal/releases/download/v5.2.1/CGAL-5.2.1.zip
     unzip CGAL-5.2.1.zip
     ```
   - Compilar e instalar CGAL 5.2.1:
     ```
     cd ~/CGAL-5.2.1
     cmake -B build -DCGAL_HEADER_ONLY=OFF -DCMAKE_BUILD_TYPE=Release
     cmake --build build --config Release
     cd build
     sudo make install
     ```
   - Descargar el proyecto:
     ```
     cd ~
     git clone https://github.com/robz25/Proyecto1_IE0724.git
     ```
   - Compilar el proyecto:
     ```
     cd ~/Proyecto1_IE0724
     cmake -B build -DCMAKE_BUILD_TYPE=Release
     cmake --build build --config Release
     ```
   - Ejecutar el proyecto:
     ```
     cd ~/Proyecto1_IE0724/build
     ./Proyecto1 ../puntos.txt
     ```
     También es posible hacer uso del script de bash adjunto que sirve para hacer la compilación y ejecución automática.  
