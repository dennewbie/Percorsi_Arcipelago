//
//  Archipelago.hpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 15/01/21.
//

/*
    *************************************************************************************************
    *                                                                                               *
    *                               Percorsi nell'Arcipelago                                        *
    *                                                                                               *
    *   Dopo il terribile terremoto del Dicembre 2019, a seguito di ingenti investimenti economici, *
    *   la regina dell'arcipelago di Grapha-Nui è riuscita a ripristinare i collegamenti tra le     *
    *   isole. È ora necessario incentivare il turismo nell’arcipelago per rimpinguare le casse     *
    *   del governo ed a tal fine il Primo Ministro vuole sapere quali collegamenti tra le isole    *  
    *   pubblicizzare maggiormente.                                                                 *
    *   Viene nuovamente convocata la famosa consulente informatica                                 *
    *   Ros Walker con il compito di calcolare i percorsi che massimizzano la soddisfazione dei     *
    *   turisti, partendo da una generica isola verso tutte le altre isole. Ros ha a disposizione   *
    *   la piantina dell’arcipelago con la rete di collegamenti tra le isole. Per ogni              *
    *   collegamento la piantina specifica la direzione ed un valore (anche negativo) che misura    *
    *   la qualità del collegamento.                                                                *
    *                                                                                               *
    *   Dati di input:                                                                              *
    *   È assegnato un file di testo contenente nel primo rigo due interi separati da uno spazio:   *
    *   il numero N delle isole (numerate da 0 ad N-1) ed il numero P dei ponti.                    *
    *   I successivi P righi contengono ciascuno tre numeri I1, I2 e Q per indicare che è           *
    *   possibile raggiungere l’isola I2 dall’isola I1 dove Q rappresenta la qualità del            *
    *   collegamento. I collegamenti tra le isole non danno origine a cicli.                        *
    *                                                                                               *
    *   Dati di output                                                                              *
    *   Determinare i percorsi con la massima qualità totale tra l’isola sorgente e tutte le        *
    *   altre isole.                                                                                *
    *                                                                                               *
    *   Assunzioni                                                                                  *
    *   2 ≤ N ≤ 1000                                                                                *
    *   1 ≤ P ≤ 10000                                                                               *
    *   Q[i] ∈ Z per ogni collegamento                                                              *
    *                                                                                               *
    *   Esempio:                                                                                    *
    *   input.txt                                                                                   *
    *   6 10                                                                                        *
    *   0 1 5                                                                                       *
    *   0 2 3                                                                                       *
    *   1 3 6                                                                                       *
    *   1 2 2                                                                                       *
    *   2 4 4                                                                                       *
    *   2 5 2                                                                                       *
    *   2 3 7                                                                                       *
    *   3 5 1                                                                                       *
    *   3 4 -1                                                                                      *
    *   4 5 -2                                                                                      *
    *   Output (partendo dall’isola 1):                                                             *
    *   1->0 −∞                                                                                     *
    *   1->1 0                                                                                      *
    *   1->2 2                                                                                      *
    *   1->3 9                                                                                      *
    *   1->4 8                                                                                      *
    *   1->5 10                                                                                     *
    *                                                                                               *
    *************************************************************************************************
 */

#ifndef Archipelago_hpp
#define Archipelago_hpp

#include "Graph.hpp"
#include <iostream>
#include <fstream>
#define streamNotOpenSuccessfully 100   //  Codice di errore relativo alla mancata apertura dello stream di input
#define invalidUserSourceIsland 200     /*
                                            Codice di errore relativo alla scelta non valida di un isola sorgente
                                            da parte dell'utente
                                        */
#define positiveCyclePresence 300       /*
                                            Codice di errore che segnala la presenza di un ciclo di peso positivo
                                            all'interno del grafo che in base alla traccia dovrebbe essere un DAG.

                                        */
                                        
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
    void printError(unsigned short int errorCode);  // Stampa gli errori che possono verificarsi
    bool openInputFileStream();                     // Apre lo stream di input
    void closeInputFileStream();                    // Chiude lo stream di input
    void buildGraph();                              // Costruisce il grafo rappresentante l'arcipelago
    bool checkSource(unsigned int source);          // Verifica se la sorgente scelta dall'utente è valida
    
public:
    // Costruttore
    Archipelago(std::string inputFilePath) {
        setInputFilePath(inputFilePath);
        setInputFileStream(new std::ifstream);
        if (!(openInputFileStream())) {
            printError(streamNotOpenSuccessfully);
            exit(EXIT_FAILURE);
        }
        
        setGraph(new Graph<V>);
        buildGraph();
    }
    
    // Distruttore
    ~Archipelago() {
        closeInputFileStream();
        delete getInputFileStream();
        delete getGraph();
    }
    
    // Metodi Ulteriori Pubblici
    void addIsland(Vertex<V> * newIsland);      // Permette di aggiungere una nuova isola all'arcipelago
    void addBridge(Edge<V> * newBridge);        // Permette di aggiungere un nuovo ponte all'arcipelago
    bool calculateMaxCostPaths();               /*
                                                    Calcola i percorsi dal costo massimo da sorgente unica nell'arcipelago.
                                                    Se non è possibile calcolarli, restituisce false. Altrimenti restituisce true.
                                                    Questo dipende rispettivamente dalla presenza o meno di cicli di peso positivo.
                                                 */
    void printMaxCostPaths();                   // Stampa i percorsi dal costo massimo da sorgente unica nell'arcipelago
    void chooseSource(unsigned int source);     /*
                                                    Permette all'utente di scegliere la sorgente
                                                    (isola dell'arcipelago) a partire dalla quale
                                                    calcolare i percorsi dal costo massimo verso ogni
                                                    altra isola dell'arcipelago
                                                 */
    bool isFileStreamOpen();                    // Verifica se lo stream è aperto
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
            std::cout << std::endl << "Input Stream Not Open Successfully..." << std::endl;
            break;
        case invalidUserSourceIsland:
            std::cout << std::endl << "Source island not valid. Please try again..." << std::endl;
            break;
        case positiveCyclePresence:
            std::cout << std::endl << "There's a positive cycle in the input DAG. Please check it and try again..." << std::endl;
            break;
        default:
            std::cout << std::endl << "Generic Error..." << std::endl;
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

/*
    1. Si apre lo stream
    2. Si legge il numero di isole e il numero dei collegamenti
    3. Si generano tante isole quante ne sono state lette
    4. Si generano tanti collegamenti quanti ne sono stati letti
 
 */
template <class V> void Archipelago<V>::buildGraph() {
    if (!(getInputFileStream()->is_open())) {
        openInputFileStream();
        if (!(getInputFileStream()->is_open())) {
            printError(streamNotOpenSuccessfully);
            std::cout << "\n...Abort\n";
            exit(EXIT_FAILURE);
        }
    }
    
    int nIsland, nBridge;
    *inputFileStream >> nIsland >> nBridge;
    
    for (unsigned int i = 0; i < nIsland; i++) {
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

template <class V> bool Archipelago<V>::calculateMaxCostPaths() {
    if (!(getSource()) || !(checkSource(getSource()->getID()))) {
        printError(invalidUserSourceIsland);
        return false;
    }
    
    if (!(getGraph()->getMaxCostPathsFromSource(getSource()))) {
        printError(positiveCyclePresence);
        return false;
    }
    return true;
}

template <class V> void Archipelago<V>::printMaxCostPaths() {
    for (auto it: *(getGraph()->getStringMaxCostPaths())) std::cout << it << std::endl;
}

template <class V> void Archipelago<V>::chooseSource(unsigned int source) {
    setSource(nullptr);
    if (checkSource(source)) setSource(getGraph()->getVertices()->at(source));
}

template <class V> bool Archipelago<V>::checkSource(unsigned int source) {
    if (source >= getGraph()->getVertices()->size()) return false;
    if (source < 0) return false;
    
    return true;
}

template <class V> bool Archipelago<V>::isFileStreamOpen() {
    return (getInputFileStream()->is_open()) ? true : false;
}

#endif /* Archipelago_hpp */
