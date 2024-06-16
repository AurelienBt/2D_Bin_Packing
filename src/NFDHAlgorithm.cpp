#include <vector>

#include "NFDHAlgorithm.h"
#include "FileData.h"
#include "Tools.h"

using namespace std;

NFDHAlgorithm::NFDHAlgorithm() {
}

NFDHAlgorithm::~NFDHAlgorithm() {
}

pair<vector<Bin2*>, vector<vector<FreeRect>>> NFDHAlgorithm::runAlgorithm() {
    vector<Bin2*> binList;
    Tools tools;
    //Version naïve où l'on créé autant de bin qu'il y a de rectangle => 1 rectangle / bin 
    /*for (int i=0 ; i<FileData::RECT_LIST.size() ; i++){
        Bin* bin=new Bin(i);
        bin->addRectangle(&FileData::RECT_LIST.at(i), 0, 0) ;
        binList.push_back(bin) ;
    }*/

    vector<vector<FreeRect>> freeRects_final;

    // Définition d'un rectangle libre initial correspondant à toute la bin
    FreeRect initialRect = { 0, 0, FileData::BIN_WIDTH, FileData::BIN_HEIGHT };
    std::vector<FreeRect> freeRects = { initialRect };
    std::vector<Rect> items;
    for (Rect* r : FileData::RECT_LIST) {
        items.push_back(*r);
    }

    Bin2* firstBin = new Bin2(0);
    binList.push_back(firstBin);
    Bin2* currentBin = firstBin;
    vector<pair<Bin2, vector<FreeRect>>> binFreeRects;

    for (int i = 0; i < items.size(); i++) {
        Rect itemToInsert = items.at(i);
        bool inserted = false;
        // Essai d'insertion du rectangle courant dans l'espace libre
        for (int j = 0; j < freeRects.size(); j++) {
            if (tools.canFit(itemToInsert, freeRects.at(j)) == 1 || tools.canFit(itemToInsert, freeRects.at(j)) == 2) {
                Rect* newItem = new Rect(itemToInsert); // Créer une nouvelle instance du rectangle
                if (tools.canFit(itemToInsert, freeRects.at(j)) == 2) {
                    newItem->setRotation(true);
                }
                currentBin->addRectangle(newItem, freeRects.at(j).x, freeRects.at(j).y);
                inserted = true;
                std::vector<FreeRect> newFreeRects = tools.cutRectangle(*newItem, freeRects.at(j));
                freeRects.erase(freeRects.begin() + j);
                freeRects.insert(freeRects.end(), newFreeRects.begin(), newFreeRects.end());
                break;
            }
        }

        if (!inserted) {
            Bin2* newBin = new Bin2(binList.size());
            binList.push_back(newBin);
            currentBin = newBin;
            freeRects_final.push_back(freeRects);
            freeRects.clear();
            freeRects.push_back(initialRect);
            i--; // Réessayer d'insérer le même rectangle dans la nouvelle bin
        }
    }
    freeRects_final.push_back(freeRects);
    return pair<vector<Bin2*>, vector<vector<FreeRect>>>(binList, freeRects_final);
}
