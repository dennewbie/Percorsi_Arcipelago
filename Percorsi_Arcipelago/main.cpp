//
//  main.cpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 14/01/21.
//

#include "Archipelago.hpp"

/*
    N.B:
    Anche se fai tornare un ptr a un nodo per es. e lo metti a nullptr nel main per es.
    Non cambia quello che sta memorizzato nella classe. Valutare se rendere pubblici i
    metodi del tipo getParent(), getSource(), getDestination(), getVertices() e così via.
 */

int main() {
//    Vertex<int> * tempVertex_0 = new Vertex<int>(10);
//    Vertex<int> * tempVertex_1 = new Vertex<int>(20);
//    Vertex<int> * tempVertex_2 = new Vertex<int>(30);
//    Vertex<int> * tempVertex_3 = new Vertex<int>(40);
//    Vertex<int> * tempVertex_4 = new Vertex<int>(50);
//    Vertex<int> * tempVertex_5 = new Vertex<int>(60);
//
//    Edge<int> * tempEdge_0 = new Edge<int>(tempVertex_0, tempVertex_1, 5);
//    Edge<int> * tempEdge_1 = new Edge<int>(tempVertex_0, tempVertex_2, 3);
//    Edge<int> * tempEdge_2 = new Edge<int>(tempVertex_1, tempVertex_3, 6);
//    Edge<int> * tempEdge_3 = new Edge<int>(tempVertex_1, tempVertex_2, 2);
//    Edge<int> * tempEdge_4 = new Edge<int>(tempVertex_2, tempVertex_4, 4);
//    Edge<int> * tempEdge_5 = new Edge<int>(tempVertex_2, tempVertex_5, 2);
//    Edge<int> * tempEdge_6 = new Edge<int>(tempVertex_2, tempVertex_3, 7);
//    Edge<int> * tempEdge_7 = new Edge<int>(tempVertex_3, tempVertex_5, 1);
//    Edge<int> * tempEdge_8 = new Edge<int>(tempVertex_3, tempVertex_4, -1);
//    Edge<int> * tempEdge_9 = new Edge<int>(tempVertex_4, tempVertex_5, 2);
//
//    Graph<int> tempGraph;
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
//    tempGraph.getMaxCostPathsFromSource(tempVertex_1);
//
//    std::vector<Vertex<int> *> * vettore = tempGraph.getVertices();
//    vettore->clear();

//    tempGraph.getVertices()->clear();
//    tempGraph.getVertices()->push_back(tempVertex_0);

//    std::vector<std::string> * stringMaxPaths = tempGraph.getStringMaxCostPaths();
//    for (auto it: *stringMaxPaths) {
//        std::cout << it;
//    }
    const char * usrMenuMessage =   "\n\nBenvenuti nell'Arcipelago...\n\nLe isole e i ponti sono stati già caricati. "
                                    "Inserisci l'isola a partire \ndalla quale vuoi calcolare i percorsi col costo massimo "
                                    "verso tutte le \naltre isole dell'arcipelago.\n\nDigita un numero da 0 a (N - 1) "
                                    "dove N è il numero delle isole totali \npresenti nel file che hai caricato.\n\nDigita "
                                    "qui: ";
    
    const char * errorMenuMessage = "\n\n** Invalid input.  Try again... ***\n\n";
    const char * usrMenuContinueMessage = "Vuoi partire da un'altra isola? (Y = YES / N = NO).\nScegli: ";
    unsigned int usrSourceIsland;
    char usrContinue;
    
    Archipelago<int> tempArchipelago = Archipelago<int>("input.txt");
    
    do {
        std::cout << usrMenuMessage;
        while (!(std::cin >> usrSourceIsland)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMenuMessage << usrMenuMessage;
        }
        
        tempArchipelago.chooseSource(usrSourceIsland);
        if (tempArchipelago.isFileStreamOpen()) {
            if (tempArchipelago.calculateMaxCostPaths()) {
                tempArchipelago.printMaxCostPaths();
                std::cout << std::endl << std::endl;
            }
        }
        
        std::cout << usrMenuContinueMessage;
        while (!(std::cin >> usrContinue)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMenuMessage << usrMenuContinueMessage;
        }
    } while (usrContinue == 'Y' || usrContinue == 'y');
    return 0;
}
