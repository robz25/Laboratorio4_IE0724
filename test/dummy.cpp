#include "gtest/gtest.h"

#include "Util.hpp"

#include "Punto.hpp"
#include "CGALBridge.hpp"
#include <time.h>
#include <fstream>
#include <iostream>

// Positive testing: use valid input parameter: status should be 0
TEST(Util, positive) {
    int status = false;
    status = Util::isInt("5");
    EXPECT_EQ(status, true);
}


//./exe --gtest_repeat=10
//
TEST(Prueba2, positive){

//	int result = 0;i

	std::ofstream archivoPuntos;
        archivoPuntos.open("puntosTest.txt");
        float limInferior = -100;
        float limSuperior = 100;
        srand (time(NULL));
        int cantPuntos = rand()%100 +3;
        for(int c = 0;c < cantPuntos;c++){
                float x = float(rand())/float((RAND_MAX))*(limSuperior - limInferior) + limInferior;
                float y = float(rand())/float((RAND_MAX))*(limSuperior - limInferior) + limInferior;
                archivoPuntos << std::to_string(x) + ", "+std::to_string(y)+"\n";
        }
        archivoPuntos.close();

	EXPECT_THROW(CGALBridge::crearDiagramaVoronoi("puntosTest.txt", true),
               std::runtime_error);
//	CGALBridge::crearDiagramaVoronoi("puntosTest.txt");

//	EXPECT_EQ(result, 0);	
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
