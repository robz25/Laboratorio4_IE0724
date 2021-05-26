#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

#include "CGALBridge.hpp"
#include "Punto.hpp"
#include "Util.hpp"

/**
 * @brief Programa principal.
 *
 * @return int .
 */
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

  try {
    CGALBridge::dibujar(CGALBridge::crearDiagramaVoronoi(archivo,true));
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
