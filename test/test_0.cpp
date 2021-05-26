#include "gtest/gtest.h"
#include <string>
#include <bitset>
#include <iostream>
#include <sstream>
#include <cmath> 
#include "Util.hpp"

struct datos{
  std::string contenido;
};
struct datos puntos_archivo;

/* Función para determinar si se trata de un float o no*/
static bool float_gtest(const std::string& s){
    float num;
    double fractpart, intpart;
    std::stringstream ss;
    ss << s;
    ss >> num;

    fractpart = modf (num , &intpart); 
    if((!fractpart)>0){
        if(num == 0){
            if(std::bitset<8>(s.c_str()[0]) == 48){
                return 1;
            }
            else{
                return 0;
            }   
        }
        else{
            return 1;
        }
    } else {
        return 1;
    }
}

// Positive testing: use valid input parameter: status should be 0
TEST(fileExists, positive) {

  /* Se prueba si el archivo ingresado es válido */
    int status_0 = false;
    status_0 = Util::fileExists(puntos_archivo.contenido);
    EXPECT_EQ(status_0, true);

    std::ifstream infile(puntos_archivo.contenido);
    std::string linea;
    int status_1, status_2;
  
    while (std::getline(infile, linea)) {
      std::istringstream iss(linea);
      std::string str_0;
      std::cout<<linea<<std::endl;

      while(std::getline(iss, str_0 , ',')){
        status_1 = false;
        status_2 = false;
        /* Chequear si es un float con la función por testear (del código fuente). */
        status_1 = Util::isFloat(str_0);
        /* Chequear si es un float con la función del creador del test. */
        status_2 = float_gtest(str_0);
        EXPECT_EQ(status_1, status_2);
      }
    }
}

int main(int argc, char **argv) {

  std::string archivo;

  // El primer argumento es el ejecutable, por lo que se requieren 2 argumentos
  // como mínimo.
  if (argc < 2) {
    std::cerr << "Error: Se requiere un argumento que indique la ruta del "
                 "archivo que contiene la lista de puntos."
              << std::endl;
    return 1;
  } else {
    if (argc > 2) {
      std::cerr
          << "Advertencia: Argumentos ignorados, solo se acepta un argumento."
          << std::endl;
    }
    archivo = argv[1];
  }
  if (!Util::fileExists(archivo)) {
    std::cerr
        << "Error: La ruta del archivo no es correcta, el archivo no existe."
        << std::endl;
    return 1;
  }

  puntos_archivo.contenido = archivo; 
  /* Gtest*/
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
