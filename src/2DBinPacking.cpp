// 2DBinPacking.cpp : définit le point d'entrée de l'application.
//

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <chrono>

#include "2DBinPacking.h"
#include "Rect.h"
#include "IOUtils.h"
#include "FileData.h"
#include "GeneticAlgorithm.h"
#include "NFDHAlgorithm.h"
#include "Bin2.h"
#include "SimulatedAnnealing.h"

using namespace std;

int main()
{
    // choix du jeu de données
    int choice;
    do {
        std::cout << "Veuillez choisir un jeu de données (entrez un nombre entre 1 et 13): ";
        std::cin >> choice;
    } while (choice < 1 || choice > 13);

    FileData::init(choice);

    // choix de l'algorithme
    int algoChoice;
    do {
        std::cout << "Veuillez choisir un algorithme :\n    1 - Simulated Annealing\n    2 - Genetic Algorithm\nVotre choix (1 ou 2): ";
        std::cin >> algoChoice;
    } while (algoChoice != 1 && algoChoice != 2);

    // Affiche le choix de l'utilisateur
    if (algoChoice == 1) {
        NFDHAlgorithm nfdhAlgorithm = NFDHAlgorithm();
        pair<vector<Bin2*>, vector<vector<FreeRect>>> res = nfdhAlgorithm.runAlgorithm();
        vector<Bin2*> binList = res.first;
        vector<vector<FreeRect>> freeRects_final = res.second;

        SimulatedAnnealing recuitSimule = SimulatedAnnealing(5, 0.999, 100, 100);
        binList = recuitSimule.runAlgorithm(binList, freeRects_final);
        FileData::binPackingToJSON(binList);
    }
    else {
        vector<Bin*> binList;

        GeneticAlgorithm gen = GeneticAlgorithm();

        auto debut = std::chrono::high_resolution_clock::now();

        gen.GenAlgo(binList);

        auto fin = std::chrono::high_resolution_clock::now();
        auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
        std::cout << "Temps d'exécution: " << duree << " microsecondes" << std::endl;


        FileData::binPackingToJSON(binList);

        for (Bin* bin : binList) {
            delete bin;
        }
    }

	return 0;
}
