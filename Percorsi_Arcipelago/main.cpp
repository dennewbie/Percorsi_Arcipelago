//
//  main.cpp
//  Percorsi_Arcipelago
//
//  Created by Denny Caruso on 14/01/21.
//

/*
    Se lanciato da xCode:
    Per abilitare l'abilità di individuazione del file all'interno della cartella del progetto:
    Product -> Scheme -> Edit Scheme...
        Run -> Options -> Use custom working directory... e selezionare la cartella nella quale
        è situato il file di input.txt
    All'avvio concedere il permesso a xCode di leggere i file su disco.
 */

#include "Archipelago.hpp"

int main() {
    const char * usrMenuMessage =   "\n\nBenvenuti nell'Arcipelago di Grapha-Nui...\n\nLe isole e i ponti verranno caricati a breve. "
                                    "Inserisci l'isola a partire \ndalla quale vuoi calcolare i percorsi col costo massimo "
                                    "verso tutte le \naltre isole dell'arcipelago.\n\nDigita un numero da 0 a (N - 1) "
                                    "dove N è il numero delle isole totali \npresenti nel file che hai caricato.\n\nDigita "
                                    "qui: ";
    
    const char * errorMenuMessage = "\n\n** Invalid input.  Try again... ***\n\n";
    const char * usrMenuContinueMessage = "Vuoi partire da un'altra isola? (Y = YES / N = NO).\nScegli: ";
    unsigned int usrSourceIsland;
    char usrContinue;
    
    Archipelago<unsigned int> tempArchipelago = Archipelago<unsigned int>("input_2.txt");
    
    do {
        std::cout << usrMenuMessage;
        while (!(std::cin >> usrSourceIsland)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMenuMessage << usrMenuMessage;
        }
        
        tempArchipelago.chooseSource(usrSourceIsland);
        if (tempArchipelago.isFileStreamOpen()) {
            if (tempArchipelago.calculateMaxCostPaths()) {
                tempArchipelago.printMaxCostPaths();
                std::cout << std::endl << std::endl;
            }
        }
        
        std::cout << usrMenuContinueMessage;
        while (!(std::cin >> usrContinue)){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMenuMessage << usrMenuContinueMessage;
        }
    } while (usrContinue == 'Y' || usrContinue == 'y');
    return 0;
}
