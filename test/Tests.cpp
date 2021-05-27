#include <bitset>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

#include "CGALBridge.hpp"
#include "Punto.hpp"
#include "Util.hpp"
#include "gtest/gtest.h"

struct datos {
  std::string contenido;
};
struct datos puntos_archivo;

/* Función para determinar si se trata de un float o no*/
static bool float_gtest(const std::string& s) {
  float num;
  double fractpart, intpart;
  std::stringstream ss;
  ss << s;
  ss >> num;

  fractpart = modf(num, &intpart);
  if ((!fractpart) > 0) {
    if (num == 0) {
      if (std::bitset<8>(s.c_str()[0]) == 48) {
        return 1;
      } else {
        return 0;
      }
    } else {
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

  /* Se prueba si el procesamiento de datos es correcto */
  std::ifstream infile(puntos_archivo.contenido);
  std::string linea;
  int status_1, status_2;

  while (std::getline(infile, linea)) {
    std::istringstream iss(linea);
    std::string str_0;

    while (std::getline(iss, str_0, ',')) {
      status_1 = false;
      status_2 = false;
      /* Chequear si es un float con la función por testear (del código fuente).
       */
      status_1 = Util::isFloat(str_0);
      /* Chequear si es un float con la función del creador del test. */
      status_2 = float_gtest(str_0);
      EXPECT_EQ(status_1, status_2);
    }
  }
}

// Prueba negativa:
// Se ejecutarán las funciones para generar el diagrama de Voronoi con entradas
// inválidas, y corroborar que las funciones devuelvan un código de error. Se
// debe usar:
// 1-Lista de tamaño inválido (lista sin números).
TEST(Prueba3, tamano_invalido) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos1.txt", true),
               std::invalid_argument);
}
// 2-Lista con números inválidos: caracteres no numéricos.
TEST(Prueba3, caracteres_no_numericos) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos2.txt", true),
               std::invalid_argument);
}
// 3-Lista con puntos inválidos: puntos sin el formato aceptado.
TEST(Prueba3, numeros_sin_formato_valido) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos3.txt", true),
               std::invalid_argument);
}

int main(int argc, char** argv) {
  puntos_archivo.contenido = "./puntos.txt";
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}