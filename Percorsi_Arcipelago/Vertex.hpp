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

template <class V> class Vertex {
    template<class U> friend class Graph;
    
private:
    static unsigned int currID;                 // contatore
    const unsigned int ID;                      // codice identificativo univoco del vertice
    Vertex<V> * parent;                         // pointer al padre
    int d;                                      // stima inferiore del peso del cammino massimo tra nodo sorgente e destinazione
    unsigned int dTime;                         // tempo in cui è stato scoperto il nodo (tempo inizio visita)
    unsigned int fTime;                         // tempo in cui è stata terminata la visita sul nodo
    V data;                                     // dati satelliti del vertice
    std::list <Vertex <V> *> * adjacencyList;   // lista di adiacenza del vertice
    unsigned short int color;                   // colore vertice
    
    // Metodi Set
    void setParent(Vertex<V> * newParent);
    void set_d(int new_d);
    void set_dTime(unsigned int new_dTime);
    void set_fTime(unsigned int new_fTime);
    void setData(V newData);
    void setAdjacencyList(std::list <Vertex <V> *> * newAdjacencyList);
    void setColor(unsigned short int newColor);
    
    // Metodi Get Privati
    std::list <Vertex <V> *> * getAdjacencyList();
    Vertex<V> * getParent();
    
    //Metodi Ulteriori
    void resetVertex();                                     // reset degli attributi del vertice
    void addVertexToAdjacencyList(Vertex<V> * newVertex);   // aggiunge newVertex alla lista di adiacenza del vertice sul quale viene invocato
    
public:
    // Costruttore
    Vertex(V data) : ID(this->currID++) {
        setParent(nullptr);
        set_d(std::numeric_limits<int>::min());
        set_dTime(std::numeric_limits<unsigned int>::min());
        set_fTime(std::numeric_limits<unsigned int>::min());
        setData(data);
        setAdjacencyList(new std::list<Vertex<V> *>);
        setColor(WHITE);
    }
    
    // Distruttore
    ~Vertex() {
        delete getAdjacencyList();
        this->currID--;
    }
    
    // Metodi Get Pubblici
    unsigned int getID();
    int get_d();
    unsigned int get_dTime();
    unsigned int get_fTime();
    V getData();
    unsigned short int getColor();
};

// Inizializzazione contatore
template <class V> unsigned int Vertex<V>::currID = 0;

// Implementazione Metodi Set
template <class V> void Vertex<V>::setParent(Vertex<V> * newParent) {
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

template <class V> void Vertex<V>::setAdjacencyList(std::list <Vertex <V> *> * newAdjacencyList) {
    this->adjacencyList = newAdjacencyList;
}

template <class V> void Vertex<V>::setColor(unsigned short int newColor) {
    this->color = newColor;
}

// Implementazione Metodi Get

template <class V> unsigned int Vertex<V>::getID() {
    return this->ID;
}

template <class V> Vertex<V> * Vertex<V>::getParent() {
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

template <class V> std::list <Vertex <V> *> * Vertex<V>::getAdjacencyList() {
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

template <class V> void Vertex<V>::addVertexToAdjacencyList(Vertex<V> * newVertex) {
    this->adjacencyList->push_back(newVertex);
}

#endif /* Vertex_hpp */
