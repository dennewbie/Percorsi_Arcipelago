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
private:
    std::vector<Vertex<V> *> * vertices;        // Puntatore a Vector di Vertici
    std::vector<Edge<V> *> * edges;             // Puntatore a Vector di Archi
    unsigned int time;                          // Tempo (per segnare tempi di inizio e fine delle visite)
    std::vector<std::string> * stringMaxCostPaths;  /*
                                                     Puntatore a Vector di stringhe, dove ogni stringa contiene il percorso
                                                     con la massima qualità tra il nodo sorgente e un nodo destinazione
                                                     */
    
    // Metodi Set
    void setVertices(std::vector<Vertex<V> *> * newVertices);
    void setEdges(std::vector<Edge<V> *> * newEdges);
    void setTime(unsigned int newTime);
    void setStringMaxCostPaths(std::vector<std::string> * newStringMaxPaths);
    
    // Metodi Ulteriori Privati
    void resetVerticesProperties();
        // Resetta le proprietà di tutti i vertici v del Grafo
    std::stack<Vertex<V> *> getTopologicalOrderStack();
        // Restituisce uno stack contenente i vertici ordinati con l'ordinamento topologico
    void DFS_visitTopologicalOrder(Vertex<V> * vertex, std::stack<Vertex<V> *> * inputStack);
        // Visita DFS usata per generare l'ordinamento topologico
    void relax(Edge<V> * edgeToRelax);
        // Verifica se la stima di cammino di peso massimo può essere aggiornata
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
    
    // Metodi Get Pubblici
    std::vector<Vertex<V> *> * getVertices();
    std::vector<Edge<V> *> * getEdges();
    unsigned int getTime();
    std::vector<std::string> * getStringMaxCostPaths();
    
    // Metodi Ulteriori Pubblici
    void addVertex(Vertex<V> * vertexToAdd);
        // Aggiunge il "vertexToAdd" al Grafo
    void addEdge(Edge<V> * edgeToAdd);
        // Aggiunge l' "edgeToAdd"   al Grafo
    bool getMaxCostPathsFromSource(Vertex<V> * source);
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

/*
    Metodo fondamentale per ottenre l'ordinaento topologico col quale andare a rilassare
    gli archi uscenti dei vertici del grafo G.
 */
template <class V> std::stack<Vertex<V> *> Graph<V>::getTopologicalOrderStack() {
    std::stack<Vertex<V> *> stackDFS_topologicalOrder;
    resetVerticesProperties();
    
    for (auto & singleVertex: *(getVertices())) {
        if (singleVertex->getColor() == WHITE) {
            DFS_visitTopologicalOrder(singleVertex, &stackDFS_topologicalOrder);
        }
    }
    
    return stackDFS_topologicalOrder;
}

/*
    Visita DFS modificata in maniera tale che alla fine della visita di ogni nodo,
    ne fa il push sullo stack.
 */
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

/*
    1. Si puliscono i dati di ogni vertice
    2. Si ottiene l'ordinamento topologico dei vertici di G
    3. Fin quando lo stack non è vuoto, rilassa gli archi uscenti del vertice u estratto
       dallo stack
    4. Verifica se è possibile rilassare ulteriormente gli archi. In tal caso, vi è
       un ciclo di peso positivo. Non è possibile determinare i cammini massimi da
       sorgente singola
    5. Genera stringhe formattate contenenti ognuna il cammino massimo e il costo di esso
 */
template <class V> bool Graph<V>::getMaxCostPathsFromSource(Vertex<V> * source) {
    getStringMaxCostPaths()->clear();
    setTime(0);
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
    
    for (auto & singleEdge: *(getEdges())) {
        Vertex<V> * u = singleEdge->getSource();
        Vertex<V> * v = singleEdge->getDestination();
        int weight = singleEdge->getWeight();
        
        if (u->get_d() + weight == (std::numeric_limits<int>::min()) + weight) continue;
        if (v->get_d() < u->get_d() + weight) return false;
    }
    
    for (auto & singleNode: *(getVertices())) getMaxCostPathToDestination(source, singleNode);
    return true;
}

template <class V> void Graph<V>::getMaxCostPathToDestination(Vertex<V> * source, Vertex<V> * destination) {
    std::stringstream pathFromSourceToDestination("", std::ios_base::app | std::ios_base::out);

    std::stack<std::string> stringMaxPathsStack;
    if (destination->get_d() == std::numeric_limits<int>::min()) {
        stringMaxPathsStack.push("-INF");
    } else {
        stringMaxPathsStack.push(std::to_string(destination->get_d()));
    }
    
    stringMaxPathsStack.push("   ");
    
    Vertex<V> * current = destination;

    if (current->getParent() == nullptr || destination->get_d() == std::numeric_limits<int>::min()) {
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
    
    pathFromSourceToDestination << "------------------------------" << std::endl << source->getID();
    
    while (!(stringMaxPathsStack.empty())) {
        pathFromSourceToDestination << stringMaxPathsStack.top();
        stringMaxPathsStack.pop();
    }
    
    pathFromSourceToDestination << std::endl << std::endl;
    getStringMaxCostPaths()->push_back(pathFromSourceToDestination.str());
}

#endif /* Graph_hpp */
