#include "SimulatedAnnealing.h"
#include "FileData.h"
#include "Tools.h"
#include <vector>
#include <cmath>
using namespace std;

SimulatedAnnealing::SimulatedAnnealing(double t_0, double mu, int n1, int n2) {
    this->t_0 = t_0;
    this->mu = mu;
    this->n1 = n1;
    this->n2 = n2;
    srand(time(0));
    this->gen = mt19937(std::random_device{}()); // Initialisation de rand()
}

SimulatedAnnealing::~SimulatedAnnealing() {
}

vector<Bin2*> SimulatedAnnealing::runAlgorithm(vector<Bin2*> binList, vector<vector<FreeRect>> freeRects) {
    Tools tools;
    double fitness = tools.calculateFitness(binList);
    this->f_min = fitness;
    this->f_actual.push_back(fitness);

    vector<Bin2*> binListCopy;
    for (Bin2* bin : binList) {
        Bin2* newBin = new Bin2(bin->getId());
        for (Rect* rect : bin->getRectInBinList()) {
            Rect* newRect = new Rect(rect->getId(), rect->getHeight(), rect->getWidth());
            newRect->setRotation(rect->getRotation());
            newBin->addRectangle(newRect, rect->getX(), rect->getY());
        }
        binListCopy.push_back(newBin);
    }

    vector<vector<FreeRect>> freeRectsCopy = freeRects; // Pour les objets simples comme FreeRect, une copie superficielle peut suffire

    this->x_min = make_pair(binListCopy, freeRectsCopy);
    this->x_actual = make_pair(binListCopy, freeRectsCopy);

    std::uniform_int_distribution<> dis(1, 125);
    for (int k = 0; k < this->n1; k++) {
        if (k != 0) {
            vector<Bin2*> binListCopy;
            for (Bin2* bin : x_actual.first) {
                Bin2* newBin = new Bin2(bin->getId());
                for (Rect* rect : bin->getRectInBinList()) {
                    Rect* newRect = new Rect(rect->getId(), rect->getHeight(), rect->getWidth());
                    newRect->setRotation(rect->getRotation());
                    newBin->addRectangle(newRect, rect->getX(), rect->getY());
                }
                binListCopy.push_back(newBin);
            }

            binList = binListCopy;
            freeRects = x_actual.second;
        }
        bool achieved = false;
        while (!achieved) {
            int random = 70;//dis(gen);

            // Échange entre deux rectangles
            if (random <= 25) {

                // Choix aléatoire des bins
                int bin1 = 0;
                int bin2 = 0;
                while (bin1 == bin2) {
                    bin1 = rand() % binList.size();
                    bin2 = rand() % binList.size();
                }
                if (binList[bin1]->getRectInBinList().size() > 0 && binList[bin2]->getRectInBinList().size() > 0) {
                    //calcul random des rectangles
                    int rect1Index = rand() % binList[bin1]->getRectInBinList().size();
                    int rect2Index = rand() % binList[bin2]->getRectInBinList().size();

                    // Faire des copies temporaires des bins
                    vector<Bin2*> binListCopy;
                    for (Bin2* bin : binList) {
                        Bin2* newBin = new Bin2(bin->getId());
                        for (Rect* rect : bin->getRectInBinList()) {
                            Rect* newRect = new Rect(rect->getId(), rect->getHeight(), rect->getWidth());
                            newRect->setRotation(rect->getRotation());
                            newBin->addRectangle(newRect, rect->getX(), rect->getY());
                        }
                        binListCopy.push_back(newBin);
                    }

                    Bin2* tempBin1 = binListCopy[bin1];
                    Bin2* tempBin2 = binListCopy[bin2];

                    // Faire des copies temporaires des listes de rectangles
                    vector<FreeRect> tempFreeRects1 = freeRects.at(bin1);
                    vector<FreeRect> tempFreeRects2 = freeRects.at(bin2);
                    Rect* rec1 = tempBin1->getRectInBinList().at(rect1Index);
                    Rect* rec2 = tempBin2->getRectInBinList().at(rect2Index);

                    // Retirer les rectangles des bins temporaires
                    tempBin1->removeRectangle(rec1);
                    tempBin2->removeRectangle(rec2);
                    if (rec1->getWidth() == rec2->getWidth() && rec1->getHeight() == rec2->getHeight()) {
                        int x = rec1->getX();
                        int y = rec1->getY();
                        tempBin1->addRectangle(rec2, x, y);
                        x = rec2->getX();
                        y = rec2->getY();
                        tempBin2->addRectangle(rec1, x, y);
                        binList[bin1] = tempBin1;
                        binList[bin2] = tempBin2;
                        freeRects[bin1] = tempFreeRects1;
                        freeRects[bin2] = tempFreeRects2;
                        achieved = true;
                    }
                    else {
                        // Vérifier si le rectangle 1 peut être inséré dans le bin 2
                        pair <bool, vector<FreeRect>> res = FusionRectFreeRect(tempFreeRects1, rec1);
                        bool fusionable = res.first;
                        tempFreeRects1 = res.second;

                        if (fusionable) { //on a effectué des changements donc on va essayer de fusionner deux freeRects  
                            pair <bool, vector<FreeRect>> res2 = FusionFreeRect(tempFreeRects1);
                            fusionable = res2.first;
                            tempFreeRects1 = res2.second;
                        }
                        pair <bool, vector<FreeRect>> res3 = FusionRectFreeRect(tempFreeRects2, rec2);
                        fusionable = res3.first;
                        tempFreeRects2 = res3.second;
                        if (fusionable) { //on a effectué des changements donc on va essayer de fusionner deux freeRects 
                            pair <bool, vector<FreeRect>> res4 = FusionFreeRect(tempFreeRects2);
                            fusionable = res4.first;
                            tempFreeRects2 = res4.second;
                        }
                        bool inserted = false;
                        for (size_t j = 0; j < tempFreeRects2.size(); ++j) {
                            if (tools.canFit(*rec1, tempFreeRects2[j]) == 1 || tools.canFit(*rec1, tempFreeRects2[j]) == 2) {
                                if (tools.canFit(*rec1, tempFreeRects2[j]) == 2) {
                                    rec1->setRotation(rec1->getRotation() ? false : true);
                                }
                                tempBin2->addRectangle(rec1, tempFreeRects2[j].x, tempFreeRects2[j].y);
                                std::vector<FreeRect> newFreeRects = tools.cutRectangle(*rec1, tempFreeRects2[j]);
                                tempFreeRects2.erase(tempFreeRects2.begin() + j);
                                tempFreeRects2.insert(tempFreeRects2.end(), newFreeRects.begin(), newFreeRects.end());
                                inserted = true;
                                break;
                            }
                        }
                        if (inserted) {
                            inserted = false;
                            for (size_t j = 0; j < tempFreeRects1.size(); ++j) {
                                if (tools.canFit(*rec2, tempFreeRects1[j]) == 1 || tools.canFit(*rec2, tempFreeRects1[j]) == 2) {
                                    if (tools.canFit(*rec2, tempFreeRects1[j]) == 2) {
                                        rec2->setRotation(rec2->getRotation() ? false : true);
                                    }
                                    tempBin1->addRectangle(rec2, tempFreeRects1[j].x, tempFreeRects1[j].y);
                                    std::vector<FreeRect> newFreeRects = tools.cutRectangle(*rec2, tempFreeRects1[j]);
                                    tempFreeRects1.erase(tempFreeRects1.begin() + j);
                                    tempFreeRects1.insert(tempFreeRects1.end(), newFreeRects.begin(), newFreeRects.end());
                                    inserted = true;
                                    break;
                                }
                            }
                            if (inserted) {
                                // Mise à jour des bins et des listes de freeRects
                                binList[bin1] = tempBin1;
                                achieved = true;
                                binList[bin2] = tempBin2;
                                freeRects[bin1] = tempFreeRects1;
                                freeRects[bin2] = tempFreeRects2;
                            }
                        }
                    }
                }
            }
            // Autres cas de random
            else if (random <= 50) {
                // Choix aléatoire d'un bin
                int binIndex = rand() % binList.size();
                while (binList[binIndex]->getRectInBinList().size() == 0) {
                    binIndex = rand() % binList.size();
                }
                // Choix aléatoire d'un rectangle dans le bin
                int rectIndex = rand() % binList[binIndex]->getRectInBinList().size();

                // Faire une copie temporaire du bin et de la liste des FreeRect
                vector <Bin2*> binListCopy;
                for (Bin2* bin : binList) {
                    Bin2* newBin = new Bin2(bin->getId());
                    for (Rect* rect : bin->getRectInBinList()) {
                        Rect* newRect = new Rect(rect->getId(), rect->getHeight(), rect->getWidth());
                        newRect->setRotation(rect->getRotation());
                        newBin->addRectangle(newRect, rect->getX(), rect->getY());
                    }
                    binListCopy.push_back(newBin);
                }
                Bin2* tempBin = binListCopy[binIndex];
                vector<FreeRect> tempFreeRects = freeRects.at(binIndex);

                Rect* rec = tempBin->getRectInBinList().at(rectIndex);

                // Retirer le rectangle du bin temporaire
                tempBin->removeRectangle(rec);
                int width = rec->getHeight();
                int height = rec->getWidth();
                if (rec->getHeight() == rec->getWidth()) {
                    achieved = true;
                    break;
                }
                else {
                    pair <bool, vector<FreeRect>> res = FusionRectFreeRect(tempFreeRects, rec);
                    bool fusionable = res.first;
                    tempFreeRects = res.second;
                    if (fusionable) { //on a effectué des changements donc on va essayer de fusionner deux freeRects  
                        pair <bool, vector<FreeRect>> res2 = FusionFreeRect(tempFreeRects);
                        fusionable = res2.first;
                        tempFreeRects = res2.second;
                    }
                    bool moved = false;
                    for (size_t j = 0; j < tempFreeRects.size(); ++j) {
                        if (rec->getHeight() <= tempFreeRects.at(j).width && rec->getWidth() <= tempFreeRects.at(j).height) {
                            rec->setRotation(rec->getRotation() ? false : true);
                            tempBin->addRectangle(rec, tempFreeRects.at(j).x, tempFreeRects.at(j).y);
                            std::vector<FreeRect> newFreeRects = tools.cutRectangle(*rec, tempFreeRects[j]);
                            tempFreeRects.erase(tempFreeRects.begin() + j);
                            tempFreeRects.insert(tempFreeRects.end(), newFreeRects.begin(), newFreeRects.end());
                            moved = true;
                            break;
                        }
                    }
                    if (moved) {
                        // Mise à jour des bins et des listes de freeRects
                        binList[binIndex] = tempBin;
                        achieved = true;
                        freeRects[binIndex] = tempFreeRects;
                    }
                }
            }
            else {
                if (random <= 75) {
                    //on choisit une bin aléatoire, on choisit un rectangle aléatoire et on le déplace dans une autre bin
                    // Choix aléatoire des bins
                    int bin1 = 0;
                    int bin2 = 0;
                    while (bin1 == bin2) {
                        bin1 = rand() % binList.size();
                        bin2 = rand() % binList.size();
                    }
                    if (binList[bin1]->getRectInBinList().size() > 0) {
                        //calcul random des rectangles
                        int rect1Index = rand() % binList[bin1]->getRectInBinList().size();

                        // Faire des copies temporaires des bins
                        vector<Bin2*> binListCopy;
                        for (Bin2* bin : binList) {
                            Bin2* newBin = new Bin2(bin->getId());
                            for (Rect* rect : bin->getRectInBinList()) {
                                Rect* newRect = new Rect(rect->getId(), rect->getHeight(), rect->getWidth());
                                newRect->setRotation(rect->getRotation());
                                newBin->addRectangle(newRect, rect->getX(), rect->getY());
                            }
                            binListCopy.push_back(newBin);
                        }

                        Bin2* tempBin1 = binListCopy[bin1];
                        Bin2* tempBin2 = binListCopy[bin2];

                        // Faire des copies temporaires des listes de rectangles
                        vector<FreeRect> tempFreeRects1 = freeRects.at(bin1);
                        vector<FreeRect> tempFreeRects2 = freeRects.at(bin2);
                        Rect* rec1 = tempBin1->getRectInBinList().at(rect1Index);

                        // Retirer les rectangles des bins temporaires
                        tempBin1->removeRectangle(rec1);

                        // On va mettre à jour les freeRect de la bin1
                        pair <bool, vector<FreeRect>> res = FusionRectFreeRect(tempFreeRects1, rec1);
                        bool fusionable = res.first;
                        tempFreeRects1 = res.second;

                        if (fusionable) { //on a effectué des changements donc on va essayer de fusionner deux freeRects  
                            pair <bool, vector<FreeRect>> res2 = FusionFreeRect(tempFreeRects1);
                            fusionable = res2.first;
                            tempFreeRects1 = res2.second;
                        }
                        bool inserted = false;
                        for (size_t j = 0; j < tempFreeRects2.size(); ++j) {
                            if (tools.canFit(*rec1, tempFreeRects2[j]) == 1 || tools.canFit(*rec1, tempFreeRects2[j]) == 2) {
                                if (tools.canFit(*rec1, tempFreeRects2[j]) == 2) {
                                    rec1->setRotation(rec1->getRotation() ? false : true);
                                }
                                tempBin2->addRectangle(rec1, tempFreeRects2[j].x, tempFreeRects2[j].y);
                                std::vector<FreeRect> newFreeRects = tools.cutRectangle(*rec1, tempFreeRects2[j]);
                                tempFreeRects2.erase(tempFreeRects2.begin() + j);
                                tempFreeRects2.insert(tempFreeRects2.end(), newFreeRects.begin(), newFreeRects.end());
                                inserted = true;
                                break;
                            }
                        }
                        if (inserted) {
                            // Mise à jour des bins et des listes de freeRects
                            binList[bin1] = tempBin1;
                            achieved = true;
                            binList[bin2] = tempBin2;
                            freeRects[bin1] = tempFreeRects1;
                            freeRects[bin2] = tempFreeRects2;
                        }
                    }
                }
                else {
                    if (random <= 100) {
                        Bin2* bin = new Bin2(binList.size());
                        binList.push_back(bin);
                        freeRects.push_back({ {0, 0, FileData::BIN_WIDTH, FileData::BIN_HEIGHT} });
                        achieved = true;
                    }
                    else {
                        for (Bin2* b : binList) {
                            if (b->getRectInBinList().size() == 0) {
                                freeRects.erase(freeRects.begin() + binList.size());
                                binList.erase(std::remove(binList.begin(), binList.end(), b), binList.end());
                                achieved = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        double delta = tools.calculateFitness(binList) - f_actual.at(f_actual.size() - 1);
        //meilleure solution
        if (delta <= 0) {
            cout << "meilleure solution, fitness : " << endl; /// ajouter l'affichage de la fitness ?
            f_actual.push_back(tools.calculateFitness(binList));
            x_actual = pair<vector<Bin2*>, vector<vector<FreeRect>>>(binList, freeRects);
            if (f_actual.at(f_actual.size() - 1) < f_min) {
                f_min = f_actual.at(f_actual.size() - 1);
                x_min = x_actual;
            }
        }
        else {
            //je tire un nombre aléatoire p entre 0 et 1
            std::srand(static_cast<unsigned int>(std::time(0)));
            // Générer un nombre aléatoire entre 0 et 1
            double p = static_cast<double>(std::rand());
            double result = exp(-delta / t_0);
            if (p < result) {
                f_actual.push_back(tools.calculateFitness(binList));
                x_actual = pair<vector<Bin2*>, vector<vector<FreeRect>>>(binList, freeRects);
            }
        }
    }
    t_0 = t_0 * mu;
    for (Bin2* b : x_min.first) {
        if (b->getRectInBinList().size() == 0) {
            x_min.first.erase(std::remove(x_min.first.begin(), x_min.first.end(), b), x_min.first.end());
        }
    }

    return x_min.first;
}

//modifier la condition du fusion, en plus d'avoir x==x et width==width il faut que y du premier+ height = y du deuxième genre les blocs sont collés 
// si y==y et height===height il faut que x du premier + width = x du deuxième 
pair<bool, vector<FreeRect>> SimulatedAnnealing::FusionRectFreeRect(vector<FreeRect> tempFreeRects1, Rect* rec1) {
    int width = rec1->getWidth();
    int height = rec1->getHeight();
    int x = rec1->getX();
    int y = rec1->getY();
    bool fusionable = false;
    for (size_t i = 0; i < tempFreeRects1.size(); ++i) {
        FreeRect& f = tempFreeRects1[i];
        if (f.width == width && f.x == x && (f.y + f.height == y || y + height == f.y)) {
            fusionable = true;
            int width2 = f.width;
            int height2 = f.height;
            int x2 = f.x;
            int y2 = f.y;
            // Supprimer f de tempFreeRects2
            tempFreeRects1.erase(tempFreeRects1.begin() + i);
            // Créer un nouveau freeRect fusionné
            FreeRect newFreeRect;
            newFreeRect.x = x;
            newFreeRect.y = std::min(y, y2);
            newFreeRect.width = width;
            newFreeRect.height = height + height2;
            tempFreeRects1.push_back(newFreeRect);
            break;
        }
        if (f.height == height && f.y == y && ((f.x + f.width == x || x + width == f.x))) {
            fusionable = true;
            int width2 = f.width;
            int height2 = f.height;
            int x2 = f.x;
            int y2 = f.y;
            // Supprimer f de tempFreeRects1
            tempFreeRects1.erase(tempFreeRects1.begin() + i);

            // Créer un nouveau freeRect fusionné
            FreeRect newFreeRect;
            newFreeRect.y = y;
            newFreeRect.x = std::min(x, x2);
            newFreeRect.width = width + width2;
            newFreeRect.height = height;
            tempFreeRects1.push_back(newFreeRect);
            break;
        }
    }
    return pair<bool, vector<FreeRect>>(fusionable, tempFreeRects1);
}

pair<bool, vector<FreeRect>> SimulatedAnnealing::FusionFreeRect(vector<FreeRect> tempFreeRects1) {
    bool fusionable = true;
    while (fusionable) {
        fusionable = false;
        for (int i = 0; i < tempFreeRects1.size(); i++) {
            for (int j = 0; j < tempFreeRects1.size(); j++) {
                if (i != j) {
                    FreeRect f1 = tempFreeRects1[i];
                    FreeRect f2 = tempFreeRects1[j];
                    if (f1.width == f2.width && f1.x == f2.x && (f1.height + f1.y == f2.y || f2.y + f2.height == f1.y)) {
                        fusionable = true;
                        FreeRect newFreeRect;
                        newFreeRect.x = f1.x;
                        newFreeRect.y = min(f1.y, f2.y);
                        newFreeRect.width = f1.width;
                        newFreeRect.height = f1.height + f2.height;
                        // Supprimer f de tempFreeRects2
                        tempFreeRects1.erase(tempFreeRects1.begin() + i);
                        if (i < j) {
                            tempFreeRects1.erase(tempFreeRects1.begin() + j - 1);
                        }
                        else {
                            tempFreeRects1.erase(tempFreeRects1.begin() + j);
                        }
                        // Créer un nouveau freeRect fusionné
                        tempFreeRects1.push_back(newFreeRect);
                        break;
                    }
                    if (f1.height == f2.height && f1.y == f2.y && (f1.width + f1.x == f2.x || f2.x + f2.width == f1.x)) {
                        fusionable = true;
                        FreeRect newFreeRect;
                        newFreeRect.x = min(f1.x, f2.x);
                        newFreeRect.y = f1.y;
                        newFreeRect.width = f1.width + f2.width;
                        newFreeRect.height = f1.height;

                        // Supprimer f de tempFreeRects2
                        tempFreeRects1.erase(tempFreeRects1.begin() + i);
                        if (i < j) {
                            tempFreeRects1.erase(tempFreeRects1.begin() + j - 1);
                        }
                        else {
                            tempFreeRects1.erase(tempFreeRects1.begin() + j);
                        }
                        // Créer un nouveau freeRect fusionné
                        tempFreeRects1.push_back(newFreeRect);
                        break;
                    }
                }
            }
        }
    }
    return pair<bool, vector<FreeRect>>(fusionable, tempFreeRects1);
}
