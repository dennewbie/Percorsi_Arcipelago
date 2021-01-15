//
//  Graph.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <string>
#include <stack>
#include "Vertex.hpp"
#include "Edge.hpp"

template <class V> class Graph {
private:
    std::vector<Vertex<V> *> * vertices;        // Vector di Vertici
    std::vector<Edge<V> *> * edges;             // Vector di Archi
    unsigned int time;                          // Tempo (usato come contatore nelle visite)
    std::vector<std::string> stringMaxPaths;    /*
                                                   Vector di stringhe, dove ogni stringa contiene il percorso con la
                                                   massima qualità tra il nodo sorgente e un nodo destinazione
                                                */
    
    // Metodi Set
    void setVertices(std::vector<Vertex<V> *> * newVertices);
    void setEdges(std::vector<Edge<V> *> * newEdges);
    void setTime(unsigned int newTime);
    void setStringPaths(std::vector<std::string> newStringPaths);
    
    // Metodi Get
    std::vector<Vertex<V> *> * getVertices();
    std::vector<Edge<V> *> * getEdges();
    unsigned int getTime();
    std::vector<std::string> getStringPaths();
    
    // Metodi Ulteriori
    void addVertex(Vertex<V> * vertexToAdd);    // Aggiunge il "vertexToAdd" al Grafo
    void addEdge(Edge<V> * edgeToAdd);          // Aggiunge l' "edgeToAdd"   al Grafo
    void resetVerticesProperties();             // Resetta le proprietà di tutti i vertici v del Grafo
    std::stack<Vertex<V> *> getTopologicalOrderStack();
    void DFS_visitTopologicalOrder(Vertex<V> * vertex, std::stack<Vertex<V> *> * inputStack);
    void relax(Vertex<V> * source, Vertex<V> * destination);
    void getMaxPaths(Vertex<V> * source);
    
public:
    // Costrutrore
    Graph() {
        setTime(0);
        setVertices(new std::vector<Vertex<V> *>);
        setEdges(new std::vector<Edge<V> *>);
    }
    
    // Distruttore
    ~Graph() {
        for (auto i = 0; i < getVertices()->size(); i++) delete getVertices()->at(i);
        getVertices()->clear();
        delete getVertices();
        
        for (auto i = 0; i < getEdges()->size(); i++) delete getEdges()->at(i);
        getEdges()->clear();
        delete getEdges();
    }
};


// Implementazione Metodi Set
template <class V> void Graph<V>::setVertices(std::vector<Vertex<V> *> * newVertices) {
    this->vertices = newVertices;
}

template <class V> void Graph<V>::setEdges(std::vector<Edge<V> *> * newEdges) {
    this->edges = newEdges;
}

template <class V> void Graph<V>::setTime(unsigned int newTime) {
    this->time = newTime;
}

template <class V> void Graph<V>::setStringPaths(std::vector<std::string> newStringPaths) {
    this->stringPaths = newStringPaths;
}


// Implementazione Metodi Get
template <class V> std::vector<Vertex<V> *> * Graph<V>::getVertices() {
    return this->vertices;
}

template <class V> std::vector<Edge<V> *> * Graph<V>::getEdges() {
    return this->edges;
}

template <class V> unsigned int Graph<V>::getTime() {
    return this->time;
}

template <class V> std::vector<std::string> Graph<V>::getStringPaths() {
    return this->stringPaths;
}


// Metodi Ulteriori
template <class V> void Graph<V>::addVertex(Vertex<V> * vertexToAdd) {
    getVertices()->push_back(vertexToAdd);
}

template <class V> void Graph<V>::addEdge(Edge<V> * edgeToAdd) {
    getEdges()->push_back(edgeToAdd);
}

template <class V> void Graph<V>::resetVerticesProperties() {
    for (auto & singleVertex: *(getVertices())) singleVertex->resetVertex();
}

template <class V> std::stack<Vertex<V> *> Graph<V>::getTopologicalOrderStack() {
    std::stack<Vertex<V> *> stackDFS_topologicalOrder;
    resetVerticesProperties();
    
    for (auto & singleNode: *(getVertices())) {
        if (singleNode->getColor() == WHITE) {
            DFS_visitTopologicalOrder(singleNode, &stackDFS_topologicalOrder);
        }
    }
    
    setTime(0);
    return stackDFS_topologicalOrder;
}

template <class V> void Graph<V>::DFS_visitTopologicalOrder(Vertex<V> * vertex, std::stack<Vertex<V> *> * inputStack) {
    vertex->setColor(GRAY);
    setTime(getTime() + 1);
    vertex->set_dTime(getTime());
    
    for (auto & adjacentNodeToVertex: *(vertex->getAdjacencyList())) {
        if (adjacentNodeToVertex->getColor() == WHITE) {
            //            std::cout << "\n" << adjacentNodeToU->getData();
            adjacentNodeToVertex->setParent(vertex);
            DFS_visitTopologicalOrder(adjacentNodeToVertex, inputStack);
        }
    }
    
    vertex->setColor(BLACK);
    setTime(getTime() + 1);
    vertex->set_fTime(getTime());
    inputStack->push(vertex);
}

template <class V> void Graph<V>::relax(Vertex<V> * source, Vertex<V> * destination) {
    
}

template <class V> void Graph<V>::getMaxPaths(Vertex<V> * source) {
    std::stack<Vertex<V> *> stackTopologicalOrder = getTopologicalOrderStack();
    
    while (!(stackTopologicalOrder.empty())) {
        Vertex<V> * vertex = stackTopologicalOrder.top();
        stackTopologicalOrder.pop();
        
        for (auto & adjacentNodeToVertex: *(vertex->getAdjacencyList())) {
            
        }
    }
}

#endif /* Graph_hpp */
