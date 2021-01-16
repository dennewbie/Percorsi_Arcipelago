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
#include <sstream>
#include <stack>
#include "Vertex.hpp"
#include "Edge.hpp"

template <class V> class Graph {
    template <class T> friend class Archipelago;
private:
    std::vector<Vertex<V> *> * vertices;        // Vector di Vertici
    std::vector<Edge<V> *> * edges;             // Vector di Archi
    unsigned int time;                          // Tempo (usato come contatore nelle visite)
    std::vector<std::string> * stringMaxCostPaths;  /*
                                                     Puntatore a Vector di stringhe, dove ogni stringa contiene il percorso
                                                     con la massima qualità tra il nodo sorgente e un nodo destinazione
                                                     */
    
    // Metodi Set
    void setVertices(std::vector<Vertex<V> *> * newVertices);
    void setEdges(std::vector<Edge<V> *> * newEdges);
    void setTime(unsigned int newTime);
    void setStringMaxCostPaths(std::vector<std::string> * newStringMaxPaths);
    
    // Metodi Get
    std::vector<Vertex<V> *> * getVertices();   // può andare pubblico
    std::vector<Edge<V> *> * getEdges();        // può andare pubblico
    unsigned int getTime();                     // può andare pubblico
    std::vector<std::string> * getStringMaxCostPaths();

    // Metodi Ulteriori Privati
    void addVertex(Vertex<V> * vertexToAdd);
        // Aggiunge il "vertexToAdd" al Grafo
    void addEdge(Edge<V> * edgeToAdd);
        // Aggiunge l' "edgeToAdd"   al Grafo
    void resetVerticesProperties();
        // Resetta le proprietà di tutti i vertici v del Grafo
    std::stack<Vertex<V> *> getTopologicalOrderStack();
        // Restituisce uno stack contenente i vertici ordinati con l'ordinamento topologico
    void DFS_visitTopologicalOrder(Vertex<V> * vertex, std::stack<Vertex<V> *> * inputStack);
        // Visita per generare l'ordinamento topologico
    void relax(Edge<V> * edgeToRelax);
        // Verifica se la stima di cammino di peso massimo può essere aggiornata
    void getMaxCostPathsFromSource(Vertex<V> * source);
        // Calcola i cammini di peso massimo da una determinata sorgente a tutti gli altri vertici del grafo
    void getMaxCostPathToDestination(Vertex<V> * source, Vertex<V> * destination);
        // Calcola il cammino di peso massimo da una determinata sorgente a una determinata destinazione
    
public:
    // Costrutrore
    Graph() {
        setTime(0);
        setVertices(new std::vector<Vertex<V> *>);
        setEdges(new std::vector<Edge<V> *>);
        setStringMaxCostPaths(new std::vector<std::string>);
    }
    
    // Distruttore
    ~Graph() {
        for (auto i = 0; i < getVertices()->size(); i++) delete getVertices()->at(i);
        getVertices()->clear();
        delete getVertices();
        
        for (auto i = 0; i < getEdges()->size(); i++) delete getEdges()->at(i);
        getEdges()->clear();
        delete getEdges();
        
        delete getStringMaxCostPaths();
    }
    
    // Per testarli mettendolo pubblici
//    // Metodi Get
//    std::vector<Vertex<V> *> * getVertices();
//    std::vector<Edge<V> *> * getEdges();
//    unsigned int getTime();
//    std::vector<std::string> * getStringMaxCostPaths();
//
//    // Metodi Ulteriori
//    void addVertex(Vertex<V> * vertexToAdd);
//        // Aggiunge il "vertexToAdd" al Grafo
//    void addEdge(Edge<V> * edgeToAdd);
//        // Aggiunge l' "edgeToAdd"   al Grafo
//    void resetVerticesProperties();
//        // Resetta le proprietà di tutti i vertici v del Grafo
//    std::stack<Vertex<V> *> getTopologicalOrderStack();
//        // Restituisce uno stack contenente i vertici ordinati con l'ordinamento topologico
//    void DFS_visitTopologicalOrder(Vertex<V> * vertex, std::stack<Vertex<V> *> * inputStack);
//        // Visita per generare l'ordinamento topologico
//    void relax(Edge<V> * edgeToRelax);
//        // Verifica se la stima di cammino di peso massimo può essere aggiornata
//    void getMaxCostPathsFromSource(Vertex<V> * source);
//        // Calcola i cammini di peso massimo da una determinata sorgente a tutti gli altri vertici del grafo
//    void getMaxCostPathToDestination(Vertex<V> * source, Vertex<V> * destination);
//        // Calcola il cammino di peso massimo da una determinata sorgente a una determinata destinazione
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

template <class V> void Graph<V>::setStringMaxCostPaths(std::vector<std::string> * newStringMaxCostPaths) {
    this->stringMaxCostPaths = newStringMaxCostPaths;
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

template <class V> std::vector<std::string> * Graph<V>::getStringMaxCostPaths() {
    return this->stringMaxCostPaths;
}


// Implementazione Metodi Ulteriori
template <class V> void Graph<V>::addVertex(Vertex<V> * vertexToAdd) {
    getVertices()->push_back(vertexToAdd);
}

template <class V> void Graph<V>::addEdge(Edge<V> * edgeToAdd) {
    getEdges()->push_back(edgeToAdd);
    getVertices()->at(edgeToAdd->getSource()->getID())->addEdgeToAdjacencyList(edgeToAdd);
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
        if (adjacentNodeToVertex->getDestination()->getColor() == WHITE) {
            adjacentNodeToVertex->getDestination()->setParent(vertex);
            DFS_visitTopologicalOrder(adjacentNodeToVertex->getDestination(), inputStack);
        }
    }
    
    vertex->setColor(BLACK);
    setTime(getTime() + 1);
    vertex->set_fTime(getTime());
    inputStack->push(vertex);
}

template <class V> void Graph<V>::relax(Edge<V> * edgeToRelax) {
    Vertex<V> * u = edgeToRelax->getSource();
    Vertex<V> * v = edgeToRelax->getDestination();
    int weight = edgeToRelax->getWeight();
    
    if (u->get_d() + weight == (std::numeric_limits<int>::min()) + weight) return;
    
    if (v->get_d() < u->get_d() + weight) {
        v->set_d(u->get_d() + weight);
        v->setParent(u);
    }
}

template <class V> void Graph<V>::getMaxCostPathsFromSource(Vertex<V> * source) {
    std::stack<Vertex<V> *> stackTopologicalOrder = getTopologicalOrderStack();
    source->set_d(0);
    source->setParent(nullptr);
    
    while (!(stackTopologicalOrder.empty())) {
        Vertex<V> * vertex = stackTopologicalOrder.top();
        stackTopologicalOrder.pop();
        
        for (auto & adjacentEdgeToVertex: *(vertex->getAdjacencyList())) {
            relax(adjacentEdgeToVertex);
        }
    }
    
    for (auto & singleNode: *(getVertices())) getMaxCostPathToDestination(source, singleNode);
}

// Qui capire se va usato il campo ID o il campo data, quando si costruisce la stringa col path
// Pensa se non vengono inseriti in ordine crescente come sulle fotocopie della traccia e quindi non puoi sfruttare gli ID
template <class V> void Graph<V>::getMaxCostPathToDestination(Vertex<V> * source, Vertex<V> * destination) {
    std::stringstream pathFromSourceToDestination("", std::ios_base::app | std::ios_base::out);

    std::stack<std::string> stringMaxPathsStack;
    if (destination->get_d() == std::numeric_limits<int>::min()) {
        stringMaxPathsStack.push("-∞");
    } else {
        stringMaxPathsStack.push(std::to_string(destination->get_d()));
    }
    
    stringMaxPathsStack.push("   ");
    
    Vertex<V> * current = destination;

    if (current->getParent() == nullptr) {
        std::string temp = "->";
        temp.append(std::to_string(current->getID()));
        stringMaxPathsStack.push(temp);
    } else {
        while (current->getParent() != nullptr) {
            std::string temp = "->";
            temp.append(std::to_string(current->getID()));
            stringMaxPathsStack.push(temp);
            current = current->getParent();
        }
    }
    
    pathFromSourceToDestination << "\n------------------------------\n" << source->getID();
    
    while (!(stringMaxPathsStack.empty())) {
        pathFromSourceToDestination << stringMaxPathsStack.top();
        stringMaxPathsStack.pop();
    }
    
    pathFromSourceToDestination << "\n\n";
    getStringMaxCostPaths()->push_back(pathFromSourceToDestination.str());
}

#endif /* Graph_hpp */
