//
//  main.cpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 14/01/21.
//

#include <iostream>
//#include "Edge.hpp"
//#include "Vertex.hpp"
#include "Graph.hpp"

int main() {
    Vertex<int> * tempVertex_0 = new Vertex<int>(10);
    Vertex<int> * tempVertex_1 = new Vertex<int>(20);
    Vertex<int> * tempVertex_2 = new Vertex<int>(30);
    Vertex<int> * tempVertex_3 = new Vertex<int>(40);
    Vertex<int> * tempVertex_4 = new Vertex<int>(50);
    Vertex<int> * tempVertex_5 = new Vertex<int>(60);
    
    Edge<int> * tempEdge_0 = new Edge<int>(tempVertex_0, tempVertex_1, 5);
    Edge<int> * tempEdge_1 = new Edge<int>(tempVertex_0, tempVertex_2, 3);
    Edge<int> * tempEdge_2 = new Edge<int>(tempVertex_1, tempVertex_3, 6);
    Edge<int> * tempEdge_3 = new Edge<int>(tempVertex_1, tempVertex_2, 2);
    Edge<int> * tempEdge_4 = new Edge<int>(tempVertex_2, tempVertex_4, 4);
    Edge<int> * tempEdge_5 = new Edge<int>(tempVertex_2, tempVertex_5, 2);
    Edge<int> * tempEdge_6 = new Edge<int>(tempVertex_2, tempVertex_3, 7);
    Edge<int> * tempEdge_7 = new Edge<int>(tempVertex_3, tempVertex_5, 1);
    Edge<int> * tempEdge_8 = new Edge<int>(tempVertex_3, tempVertex_4, -1);
    Edge<int> * tempEdge_9 = new Edge<int>(tempVertex_4, tempVertex_5, 2);
    
    Graph<int> tempGraph;
//    tempGraph.addVertex(tempVertex_0);
//    tempGraph.addVertex(tempVertex_1);
//    tempGraph.addVertex(tempVertex_2);
//    tempGraph.addVertex(tempVertex_3);
//    tempGraph.addVertex(tempVertex_4);
//    tempGraph.addVertex(tempVertex_5);
//
//    tempGraph.addEdge(tempEdge_0);
//    tempGraph.addEdge(tempEdge_1);
//    tempGraph.addEdge(tempEdge_2);
//    tempGraph.addEdge(tempEdge_3);
//    tempGraph.addEdge(tempEdge_4);
//    tempGraph.addEdge(tempEdge_5);
//    tempGraph.addEdge(tempEdge_6);
//    tempGraph.addEdge(tempEdge_7);
//    tempGraph.addEdge(tempEdge_8);
//    tempGraph.addEdge(tempEdge_9);
//    tempGraph.getMaxPaths(tempVertex_1);
//
//
//    std::vector<std::string> stringMaxPaths = tempGraph.getStringMaxPaths();
//    for (auto it: stringMaxPaths) {
//        std::cout << it;
//    }
    return 0;
}
