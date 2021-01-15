//
//  main.cpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 14/01/21.
//

#include <iostream>
#include "Edge.hpp"
//#include "Vertex.hpp"

int main() {
    Vertex<int> * tempVertex_1 = new Vertex<int>(5);
    Vertex<int> * tempVertex_2 = new Vertex<int>(6);
    Vertex<int> * tempVertex_3 = new Vertex<int>(7);
    Vertex<int> * tempVertex_4 = new Vertex<int>(8);
    
    Edge<int> * tempEdge_1 = new Edge<int>(tempVertex_1, tempVertex_2, 2);

    return 0;
}
