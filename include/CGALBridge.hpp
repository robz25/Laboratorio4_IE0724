#ifndef CGALBRIDGE_CLASS
#define CGALBRIDGE_CLASS

// includes for drawing the Voronoi Diagram
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/draw_voronoi_diagram_2.h>

// typedefs for defining the adaptor
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DT> AT;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DT> AP;
typedef CGAL::Voronoi_diagram_2<DT, AT, AP> VD;

// typedef for the result type of the point location
typedef AT::Site_2 Site_2;

#include <CGAL/Qt/Basic_viewer_qt.h>
#include <CGAL/Qt/init_ogl_context.h>
#include <CGAL/Random.h>
#include <CGAL/Triangulation_utils_2.h>
#include <CGAL/Voronoi_diagram_2/Accessor.h>
#include <CGAL/Voronoi_diagram_2/Face.h>
#include <CGAL/Voronoi_diagram_2/Handle_adaptor.h>
#include <CGAL/Voronoi_diagram_2/Vertex.h>
#include <CGAL/Voronoi_diagram_2/basic.h>
#include <CGAL/license/Voronoi_diagram_2.h>

#include <fstream>

#include "Punto.hpp"

/**
 * @Author: Emilio Rojas
 * @Desc: CGALBridge uses the CGAL library to solve the voronoi diagraming.
 */
class CGALBridge {
 private:
  /**
   * @brief Obtiene un vector con los puntos presentes en cada linea del archivo
   * indicado.
   *
   * @param archivo Ruta al archivo que contiene los puntos.
   * @return std::vector<Punto>* Vector con puntos parseados.
   */
  static std::vector<Punto> *obtenerPuntos(std::string archivo,
                                           bool throwOnWarning = false) {
    std::ifstream infile(archivo);
    std::string linea;
    std::vector<Punto> *puntos = new std::vector<Punto>();
    int i = 0;
    while (std::getline(infile, linea)) {
      i++;  // permite indicar el número de línea en caso de advertencia.
      // Ignora lineas vacias
      if (linea.empty()) {
        continue;
      }
      std::istringstream iss(linea);
      try {
        Punto *punto = new Punto(
            linea);  // Crea un punto si el formato de la línea es aceptado.
        puntos->push_back(*punto);  // Agrega el punto al vector.
      } catch (const std::exception &e) {
        if (throwOnWarning) {
          throw std::invalid_argument(
              "Formato inválido encontrado en el archivo " + archivo + ", línea: " + std::to_string(i) + ".");
        } else {
          // Ignorar línea e imprimir advetencia.
          std::cerr << "Advertencia: Línea " << i << " del archivo " << archivo
                    << ": " << e.what() << "Contenido: " << linea << std::endl;
          continue;
        }
      }
    }
    return puntos;
  }

 public:
  /**
   * @brief Dibuja un diagrama de voronoi en una nueva ventana. Es una copia de
   * la función disponible en la libraría CGAL.
   *
   * @tparam DG Deluanay Graph
   * @tparam AT Adaptation Trait.
   * @tparam AP Adaptation Policy.
   * @param av2 Diagrama de voronoi.
   * @param title Titulo de la ventana.
   * @param nofill Rellenar áreas de color.
   * @param draw_voronoi_vertices Dibujar puntos de voronoi.
   * @param draw_dual_vertices Dibujar vértices en el gráfico.
   */
  template <class DG, class AT, class AP>
  static void dibujar(const CGAL_VORONOI_TYPE &av2,
                      const char *title = "Diagrama de Voronoi",
                      bool nofill = true, bool draw_voronoi_vertices = false,
                      bool draw_dual_vertices = true,
                      const char *saveAs = "diagrama.png") {
    CGAL::Qt::init_ogl_context(4, 3);
    int argc = 1;
    const char *argv[2] = {"voronoi_2_viewer", "\0"};
    QApplication app(argc, const_cast<char **>(argv));
    CGAL::DefaultColorFunctorV2 fcolor;
    CGAL::SimpleVoronoiDiagram2ViewerQt<CGAL_VORONOI_TYPE,
                                        CGAL::DefaultColorFunctorV2>
        mainwindow(app.activeWindow(), av2, title, nofill,
                   draw_voronoi_vertices, draw_dual_vertices, fcolor);
    mainwindow.grab().save(saveAs);
  }

  /**
   * @brief Crea un diagrama de voronoi a partir de un archivo con el formato
   * descrito en la especificación del proyecto.
   *
   * @param archivo Ruta al archivo de entrada.
   * @return VD Diagrama de voronoi.
   */
  static VD crearDiagramaVoronoi(std::string archivo,
                                 bool throwOnWarning = false) {
    VD vd;
    Site_2 t;
    std::vector<Punto> *puntos;
    try {
      puntos = CGALBridge::obtenerPuntos(archivo, throwOnWarning);
    } catch (const std::exception &e) {
      throw std::invalid_argument(e.what());
    }
    if (puntos->size() == 0) {
      throw std::invalid_argument("No se encontraron puntos en el archivo.");
    }
    for (auto it = puntos->begin(); it != puntos->end(); ++it) {
      std::istringstream iss(std::to_string(it->getX()) + " " +
                             std::to_string(it->getY()));
      iss >> t;
      vd.insert(t);
    }
    return vd;
  }
};

#endif
