//
//  Archipelago.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

#ifndef Archipelago_hpp
#define Archipelago_hpp

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#define streamNotOpenSuccessfully 100
#define invalidUserSourceIsland 200

template <class V> class Archipelago {
private:
    Graph<V> * graph;
    Vertex<V> * source;
    std::string inputFilePath;
    std::ifstream * inputFileStream;
    
    // Metodi Set
    void setGraph(Graph<V> * newGraph);
    void setSource(Vertex<V> * newSource);
    void setInputFilePath(std::string newInputFilePath);
    void setInputFileStream(std::ifstream * newInputFileStream);
    bool checkSource(unsigned int source);
    
    // Metodi Get Privati
    Graph<V> * getGraph();          // può andare pubblico
    Vertex<V> * getSource();        // può andare pubblico
    std::string getInputFilePath();
    std::ifstream * getInputFileStream();
    
    // Metodi Ulteriori Privati
    void printError(unsigned short int errorCode);
    bool openInputFileStream();
    void closeInputFileStream();
    void buidGraph();
    void chooseSource(unsigned int source);
    
public:
    // Costruttore
    Archipelago(std::string inputFilePath, unsigned int source) {
        setInputFilePath(inputFilePath);
        setInputFileStream(new std::ifstream);
        if (!(openInputFileStream())) {
            printError(streamNotOpenSuccessfully);
            return;
        }
        
        setGraph(new Graph<V>);
        buidGraph();
        
        if (checkSource(source)) {
            setSource(getGraph()->getVertices()->at(source));
        }
    }
    
    // Distruttore
    ~Archipelago() {
        closeInputFileStream();
        delete getInputFileStream();
        delete getGraph();
    }
    
    // Metodi Ulteriori Pubblici
    void addIsland(Vertex<V> * newIsland);
    void addBridge(Edge<V> * newBridge);
    void calculateMaxCostPaths();
    void printMaxCostPaths();
};


// Implementazione Metodi Set
template <class V> void Archipelago<V>::setGraph(Graph<V> * newGraph) {
    this->graph = newGraph;
}

template <class V> void Archipelago<V>::setSource(Vertex<V> * newSource) {
    this->source = newSource;
}

template <class V> void Archipelago<V>::setInputFilePath(std::string newInputFilePath) {
    this->inputFilePath = newInputFilePath;
}

template <class V> void Archipelago<V>::setInputFileStream(std::ifstream * newInputFileStream) {
    this->inputFileStream = newInputFileStream;
}


// Implementazione Metodi Get
template <class V> Graph<V> * Archipelago<V>::getGraph() {
    return this->graph;
}

template <class V> Vertex<V> * Archipelago<V>::getSource() {
    return this->source;
}

template <class V> std::string Archipelago<V>::getInputFilePath() {
    return this->inputFilePath;
}

template <class V> std::ifstream * Archipelago<V>::getInputFileStream() {
    return this->inputFileStream;
}


// Implementazione Metodi Ulteriori
template <class V> void Archipelago<V>::printError(unsigned short int errorCode) {
    switch (errorCode) {
        case streamNotOpenSuccessfully:
            std::cout << "\nInput Stream Not Open Successfully...\n";
            break;
        case invalidUserSourceIsland:
            std::cout << "\nSource island not valid. Please try again...\n";
            break;
        default:
            std::cout << "\nGeneric Error...\n";
            break;
    }
}

template <class V> bool Archipelago<V>::openInputFileStream() {
    getInputFileStream()->open(getInputFilePath().c_str(), std::ifstream::in);
    if (getInputFileStream()->fail()) return false;
    
    return true;
}

template <class V> void Archipelago<V>::closeInputFileStream() {
    getInputFileStream()->close();
}

template <class V> void Archipelago<V>::buidGraph() {
    while (!(getInputFileStream()->is_open())) {
        openInputFileStream();
        if (!(getInputFileStream()->is_open())) printError(streamNotOpenSuccessfully);
    }
    
    int nIsland, nBridge;
    *inputFileStream >> nIsland >> nBridge;
    
    for (auto i = 0; i < nIsland; i++) {
        Vertex<V> * newIsland = new Vertex<V>(i);
        addIsland(newIsland);
    }
    
    unsigned int firstIsland, secondIsland;
    int weight;
    
    for (auto i = 0; i < nBridge; i++) {
        *inputFileStream >> firstIsland >> secondIsland >> weight;
        Edge<V> * newBridge = new Edge<V>(getGraph()->getVertices()->at(firstIsland), getGraph()->getVertices()->at(secondIsland), weight);
        addBridge(newBridge);
    }
    
}

template <class V> void Archipelago<V>::addIsland(Vertex<V> * newIsland) {
    getGraph()->addVertex(newIsland);
}

template <class V> void Archipelago<V>::addBridge(Edge<V> * newBridge) {
    getGraph()->addEdge(newBridge);
}

template <class V> void Archipelago<V>::calculateMaxCostPaths() {
    if (!(getSource())) {
        printError(invalidUserSourceIsland);
        return;
    }
    
    getGraph()->getMaxCostPathsFromSource(getSource());
}

template <class V> void Archipelago<V>::printMaxCostPaths() {
    for (auto it: *(getGraph()->getStringMaxCostPaths())) std::cout << it << std::endl;
}

template <class V> void Archipelago<V>::chooseSource(unsigned int source) {
    if (checkSource(source)) setSource(getGraph()->getVertices()->at(source));
}

template <class V> bool Archipelago<V>::checkSource(unsigned int source) {
    if (source >= getGraph()->getVertices()->size()) {
        printError(invalidUserSourceIsland);
        return false;
    }
    
    return true;
}

#endif /* Archipelago_hpp */
