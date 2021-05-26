#include "CGALBridge.hpp"
#include "Punto.hpp"
#include "Util.hpp"
#include "gtest/gtest.h"

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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
