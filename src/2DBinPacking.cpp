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
    FileData::init();

    //vector<Bin*> binList;

    //GeneticAlgorithm gen = GeneticAlgorithm();

    //auto debut = std::chrono::high_resolution_clock::now();

    //gen.GenAlgo(binList);

    //auto fin = std::chrono::high_resolution_clock::now();
    //auto duree = std::chrono::duration_cast<std::chrono::microseconds>(fin - debut).count();
    //std::cout << "Temps d'exécution: " << duree << " microsecondes" << std::endl;


    //FileData::binPackingToJSON(binList);

    //for (Bin* bin : binList) {
    //    delete bin;
    //}



    NFDHAlgorithm nfdhAlgorithm = NFDHAlgorithm();
    pair<vector<Bin2*>, vector<vector<FreeRect>>> res = nfdhAlgorithm.runAlgorithm();
    vector<Bin2*> binList = res.first;
    vector<vector<FreeRect>> freeRects_final = res.second;

    SimulatedAnnealing recuitSimule = SimulatedAnnealing(5, 0.999, 100, 100);
    binList = recuitSimule.runAlgorithm(binList, freeRects_final);
    FileData::binPackingToJSON(binList);

	return 0;
}
