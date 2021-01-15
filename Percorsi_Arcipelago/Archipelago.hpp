//
//  Archipelago.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

#ifndef Archipelago_hpp
#define Archipelago_hpp

#include "Graph.hpp"
#include <fstream>

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
    
    // Metodi Get Privati
    Graph<V> * getGraph();
    Vertex<V> * getSource();
    std::string getInputFilePath();
    std::ifstream * getInputFileStream();
    
    // Metodi Ulteriori Privati
    void closeInputFileStream();
public:
    // Costruttore
    Archipelago() { }
    
    // Distruttore
    ~Archipelago() { }
    
    // Metodi Ulteriori Pubblici
    
};


// Implementazione Metodi Set
template <class V> void Archipelago<V>::setGraph(Graph<V> * newGraph) {
    this->graph = newGraph;
}

template <class V> void Archipelago<V>::setSource(Vertex<V> * newSource) {
    this->source = newSource;
}

template <class V> void Archipelago<V>::setInputFilePath(std::string newInputFilePath) {
    this->inputFilePath = inputFilePath;
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


#endif /* Archipelago_hpp */
