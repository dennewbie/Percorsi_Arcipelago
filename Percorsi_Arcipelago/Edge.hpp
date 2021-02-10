//
//  Edge.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

#ifndef Edge_hpp
#define Edge_hpp

template <class V> class Vertex;

template <class V> class Edge {
private:
    static unsigned int currID;     // Contatore
    const unsigned int ID;          // Codice identificativo univoco dell'arco
    Vertex<V> * source;             // Puntatore al vertice sorgente
    Vertex<V> * destination;        // Puntatore al vertice destinazione
    int weight;                     // Peso (costo) dell'arco
    
    // Metodi Set
    void setSource(Vertex<V> * newSource);
    void setDestination(Vertex<V> * newDestination);
    void setWeight(int newWeight);
    
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
    Vertex<V> * getSource();
    Vertex<V> * getDestination();
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
