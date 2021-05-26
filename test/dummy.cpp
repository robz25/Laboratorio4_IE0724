#include "CGALBridge.hpp"
#include "Punto.hpp"
#include "Util.hpp"
#include "gtest/gtest.h"

// Prueba negativa:
// Se ejecutarán las funciones para generar el diagrama de Voronoi con entradas
// inválidas, y corroborar que las funciones devuelvan un código de error. Se
// debe usar: 1-Lista de tamaño inválido (lista sin números para Voronoi, y
// lista con menos de 3 números para Convex Hull).
TEST(Prueba3, item1) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos1.txt", true),
               std::invalid_argument);
}
// 2-Lista con números inválidos: caracteresno numéricos.
TEST(Prueba3, item2) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos2.txt", true),
               std::invalid_argument);
}
// 3-Lista con puntos inválidos: puntos sin el formato aceptado.
TEST(Prueba3, item3) {
  EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("./puntosInvalidos3.txt", true),
               std::invalid_argument);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
