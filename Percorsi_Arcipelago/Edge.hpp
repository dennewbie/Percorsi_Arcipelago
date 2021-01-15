//
//  Edge.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

#ifndef Edge_hpp
#define Edge_hpp

#include "Vertex.hpp"
#include <type_traits>
//template <class V> class Vertex; testing se va bene oppure com'è ora
// Non è possibile usare i Variable Template se non a partire dal C++ 14

template <class V> class Edge {
//    template<class U> friend class Graph;
private:
    static unsigned int currID;     // contatore
    const unsigned int ID;          // codice identificativo univoco dell'arco
    Vertex<V> * source;             // puntatore al vertice sorgente
    Vertex<V> * destination;        // puntatore al vertice destinazione
    int weight;                     // peso (costo) dell'arco
    
    // Metodi Set
    void setSource(Vertex<V> * newSource);
    void setDestination(Vertex<V> * newDestination);
    void setWeight(int newWeight);
    
    // Metodi Get Privati
    Vertex<V> * getSource();
    Vertex<V> * getDestination();
    
public:
    // Costruttore
    Edge(Vertex<V> * source, Vertex<V> * destination, int weight) : ID(this->currID++) {
        setSource(source);
        setDestination(destination);
        setWeight(weight);
    }
    
    // Distruttore
    ~Edge() { }
    
    // Metodi Get Pubblici
    unsigned int getID();
    int getWeight();
};


// Inizializzazione contatore Edge
template <class V> unsigned int Edge<V>::currID = 0;


// Implementazione Metodi Set
template <class V> void Edge<V>::setSource(Vertex<V> * newSource) {
    this->source = newSource;
}

template <class V> void Edge<V>::setDestination(Vertex<V> * newDestination) {
    this->destination = newDestination;
}

template <class V> void Edge<V>::setWeight(int newWeight) {
    this->weight = newWeight;
}


// Implementazione Metodi Get
template <class V> unsigned int Edge<V>::getID() {
    return this->ID;
}

template <class V> Vertex<V> * Edge<V>::getSource() {
    return this->source;
}

template <class V> Vertex<V> * Edge<V>::getDestination() {
    return this->destination;
}

template <class V> int Edge<V>::getWeight() {
    return this->weight;
}

#endif /* Edge_hpp */
