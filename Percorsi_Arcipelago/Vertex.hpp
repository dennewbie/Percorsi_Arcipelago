//
//  Vertex.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 14/01/21.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <list>
#include <limits>

#define WHITE 1
#define GRAY  2
#define BLACK 3

template <class V> class Edge;

template <class V> class Vertex {
    template <class T> friend class Graph;
    
private:
    static unsigned int currID;                 // Contatore
    const unsigned int ID;                      // Codice identificativo univoco del vertice
    Vertex<V> * parent;                         // Pointer al padre
    int d;                                      // Stima inferiore del peso del cammino massimo tra nodo sorgente e destinazione
    unsigned int dTime;                         // Tempo in cui è stato scoperto il nodo (tempo inizio visita)
    unsigned int fTime;                         // Tempo in cui è stata terminata la visita sul nodo
    V data;                                     // Dati satelliti del vertice
    std::list <Edge<V> *> * adjacencyList;      // Lista di adiacenza del vertice
    unsigned short int color;                   // Colore vertice
    
    // Metodi Set
    void setParent(Vertex <V> * newParent);
    void set_d(int new_d);
    void set_dTime(unsigned int new_dTime);
    void set_fTime(unsigned int new_fTime);
    void setData(V newData);
    void setAdjacencyList(std::list <Edge <V> *> * newAdjacencyList);
    void setColor(unsigned short int newColor);
    
    // Metodi Get Privati
    std::list <Edge <V> *> * getAdjacencyList();
    Vertex<V> * getParent();
    
    //Metodi Ulteriori Privati
    void resetVertex();                                     // Reset degli attributi del vertice
    void addEdgeToAdjacencyList(Edge <V> * newEdge);        // Aggiunge newEdge alla lista di adiacenza del vertice sul quale viene invocato
    
public:
    // Costruttore
    Vertex(V data) : ID(this->currID++) {
        setParent(nullptr);
        set_d(std::numeric_limits<int>::min());
        set_dTime(std::numeric_limits<unsigned int>::min());
        set_fTime(std::numeric_limits<unsigned int>::min());
        setData(data);
        setAdjacencyList(new std::list<Edge <V> *>);
        setColor(WHITE);
    }
    
    // Distruttore
    ~Vertex() {
        delete getAdjacencyList();
//        this->currID--; altrimenti abbiamo stessi ID per più vertici
    }
    
    // Metodi Get Pubblici
    unsigned int getID();
    int get_d();
    unsigned int get_dTime();
    unsigned int get_fTime();
    V getData();
    unsigned short int getColor();
};


// Inizializzazione contatore Vertex
template <class V> unsigned int Vertex<V>::currID = 0;


// Implementazione Metodi Set
template <class V> void Vertex<V>::setParent(Vertex <V> * newParent) {
    this->parent = newParent;
}

template <class V> void Vertex<V>::set_d(int new_d) {
    this->d = new_d;
}

template <class V> void Vertex<V>::set_dTime(unsigned int new_dTime) {
    this->dTime = new_dTime;
}

template <class V> void Vertex<V>::set_fTime(unsigned int new_fTime) {
    this->fTime = new_fTime;
}

template <class V> void Vertex<V>::setData(V newData) {
    this->data = newData;
}

template <class V> void Vertex<V>::setAdjacencyList(std::list <Edge <V> *> * newAdjacencyList) {
    this->adjacencyList = newAdjacencyList;
}

template <class V> void Vertex<V>::setColor(unsigned short int newColor) {
    this->color = newColor;
}


// Implementazione Metodi Get
template <class V> unsigned int Vertex<V>::getID() {
    return this->ID;
}

template <class V> Vertex <V> * Vertex<V>::getParent() {
    return this->parent;
}

template <class V> int Vertex<V>::get_d() {
    return this->d;
}

template <class V> unsigned int Vertex<V>::get_dTime() {
    return this->dTime;
}

template <class V> unsigned int Vertex<V>::get_fTime() {
    return this->fTime;
}

template <class V> V Vertex<V>::getData() {
    return this->data;
}

template <class V> std::list <Edge <V> *> * Vertex<V>::getAdjacencyList() {
    return this->adjacencyList;
}

template <class V> unsigned short int Vertex<V>::getColor() {
    return this->color;
}

// Implementazione Metodi Ulteriori
template <class V> void Vertex<V>::resetVertex() {
    setParent(nullptr);
    set_d(std::numeric_limits<int>::min());
    set_dTime(std::numeric_limits<unsigned int>::min());
    set_fTime(std::numeric_limits<unsigned int>::min());
    setColor(WHITE);
}

template <class V> void Vertex<V>::addEdgeToAdjacencyList(Edge <V> * newEdge) {
    getAdjacencyList()->push_back(newEdge);
}

#endif /* Vertex_hpp */
