#include "GeneticAlgorithm.h"
#include "FileData.h"
#include "Tools.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <numeric>
#include <random>
#include <cmath>

GeneticAlgorithm::GeneticAlgorithm()
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

void GeneticAlgorithm::LGFi(std::vector<Bin*>& binList) {
    std::vector<Rect*> rectangles = FileData::RECT_LIST;
    deterministicSequence(&rectangles);
    LGFi(binList, rectangles);
}

void GeneticAlgorithm::LGFi(std::vector<Bin*>& binList, std::vector<Rect*> orderedRectangles) {
    // Initialisation
    FreeRect initialRect = { 0, 0, FileData::BIN_WIDTH, FileData::BIN_HEIGHT };
    std::vector<FreeRect> freeRects = { initialRect };
    std::vector<Rect*> rectangles = orderedRectangles;

    Bin* firstBin = new Bin(0);
    binList.push_back(firstBin);
    Bin* currentBin = firstBin;

    // Etape de remplissage
    while (!rectangles.empty()) {
        bool createNewBin = false;
        Rect* bestFit = nullptr;
        bool foundFit = false;
        FreeRect freeRectToUse = getNextFreeRect(freeRects);

        for (Rect* rect : rectangles) {
            if (canFit(*rect, freeRectToUse)) {
                bestFit = rect;
                foundFit = true;
                break;
            }
            rect->setRotation(!rect->getRotation());
            if (canFit(*rect, freeRectToUse)) {
                bestFit = rect;
                foundFit = true;
                break;
            }
            rect->setRotation(!rect->getRotation());
        }

        if (foundFit) {
            currentBin->addRectangle(bestFit, freeRectToUse.x, freeRectToUse.y);

            rectangles.erase(std::remove(rectangles.begin(), rectangles.end(), bestFit), rectangles.end());
            freeRects.erase(std::remove(freeRects.begin(), freeRects.end(), freeRectToUse), freeRects.end());

            std::vector<FreeRect> newFreeRects = cutRectangle(*bestFit, freeRectToUse);
            freeRects.insert(freeRects.begin(), newFreeRects.begin(), newFreeRects.end());
            if (freeRects.size() == 0) createNewBin = true;
        }
        else {
            freeRects.erase(std::remove(freeRects.begin(), freeRects.end(), freeRectToUse), freeRects.end());
            if (freeRects.size() == 0) createNewBin = true;
        }

        if (createNewBin) {
            Bin* bin = new Bin(static_cast<int>(binList.size()));
            binList.push_back(bin);
            currentBin = bin;
            freeRects.push_back(initialRect);
        }
    }
}

bool GeneticAlgorithm::canFit(const Rect& rect, const FreeRect& freeRect)
{
    int rectWidth = rect.getRotation() ? rect.getHeight() : rect.getWidth();
    int rectHeight = rect.getRotation() ? rect.getWidth() : rect.getHeight();
    return rectWidth <= freeRect.width && rectHeight <= freeRect.height;
}

int GeneticAlgorithm::insertionScore(const Rect& rect, const FreeRect& freeRect)
{
    return freeRect.width * freeRect.height - rect.getWidth() * rect.getHeight();
}

std::pair<Rect*, int> GeneticAlgorithm::getShortestRectangle(const std::vector<Rect*>& rectangles) {
    int shortestEdge = rectangles.at(0)->getHeight();
    Rect* shortestRect = rectangles.at(0);
    for (Rect* rect : rectangles) {
        if (rect->getHeight() < shortestEdge) {
            shortestEdge = rect->getHeight();
            shortestRect = rect;
        }
        if (rect->getWidth() < shortestEdge) {
            shortestEdge = rect->getWidth();
            shortestRect = rect;
        }
    }
    return std::pair<Rect*, int>(shortestRect, shortestEdge);
}

std::vector<FreeRect> GeneticAlgorithm::cutRectangle(const Rect& item, const FreeRect& freeRect) {
    std::vector<FreeRect> newFreeRects;
    int width = 0;
    int height = 0;
    if (item.getRotation()) {
        width = item.getHeight();
        height = item.getWidth();
    }
    else {
        width = item.getWidth();
        height = item.getHeight();
    }

    if (freeRect.height - height > freeRect.width - width) {
        // coupe horizontale
        if (width < freeRect.width) {
            newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, height });
        }

        if (height < freeRect.height) {
            newFreeRects.push_back({ freeRect.x, freeRect.y + height, freeRect.width, freeRect.height - height });
        }
    }
    else {
        // coupe verticale
        if (width < freeRect.width) {
            newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, freeRect.height });
        }

        if (height < freeRect.height) {
            newFreeRects.push_back({ freeRect.x, freeRect.y + height, width, freeRect.height - height });
        }
    }

    return newFreeRects;
}

std::vector<FreeRect> GeneticAlgorithm::cutRectangle(const Rect& item, const FreeRect& freeRect, const int shortestEdge) {
    std::vector<FreeRect> newFreeRects;
    int width = 0;
    int height = 0;
    if (item.getRotation()) {
        width = item.getHeight();
        height = item.getWidth();
    }
    else {
        width = item.getWidth();
        height = item.getHeight();
    }

    if (freeRect.height - height > freeRect.width - width) {
        // coupe horizontale
        if (width < freeRect.width) {
            if ((freeRect.width - width) >= shortestEdge && height >= shortestEdge) {
                newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, height });
            }
        }

        if (height < freeRect.height) {
            if (freeRect.width >= shortestEdge && (freeRect.height - height) >= shortestEdge) {
                newFreeRects.push_back({ freeRect.x, freeRect.y + height, freeRect.width, freeRect.height - height });
            }
        }
    }
    else {
        // coupe verticale
        if (width < freeRect.width) {
            if ((freeRect.width - width) >= shortestEdge && freeRect.height >= shortestEdge) {
                newFreeRects.push_back({ freeRect.x + width, freeRect.y, freeRect.width - width, freeRect.height });
            }
            
        }

        if (height < freeRect.height) {
            if (width >= shortestEdge && (freeRect.height - height) >= shortestEdge) {
                newFreeRects.push_back({ freeRect.x, freeRect.y + height, width, freeRect.height - height });
            }
        }
    }

    return newFreeRects;
}

FreeRect GeneticAlgorithm::getNextFreeRect(const std::vector<FreeRect>& freeRects) {
    FreeRect nextFreeRect = freeRects.at(0);
    std::pair<int, int> bottomLeftCoords(nextFreeRect.x, nextFreeRect.y);
    for (FreeRect freeRect : freeRects) {
        if (freeRect.y < bottomLeftCoords.second ||
            (freeRect.y == bottomLeftCoords.second && freeRect.x < bottomLeftCoords.first)) {
            bottomLeftCoords = std::make_pair(freeRect.x, freeRect.y);
            nextFreeRect = freeRect;
        }
    }

    return nextFreeRect;
}

void GeneticAlgorithm::GenAlgo(std::vector<Bin*>& binList, int popSize, float crossoverRate, float kappa, float delta) {
    std::vector<Solution> population = generateInitialPopulation(popSize, kappa);

    double bestFitness = population[0].fitness;
    std::vector<Rect*> bestSolution(population[0].rects);
    std::cout << "best sol" << bestFitness << std::endl;
    for (int i = 0; i < 100; i++) {
        auto newPopulation = crossover(population, crossoverRate, delta);
        //std::cout << "coucou2" << std::endl;
        addNewSolutions(newPopulation, popSize, kappa);
        //std::cout << "coucou3" << std::endl;

        //for (Solution s : population) {
        //    for (Rect* r : s.rects) {
        //        delete r;
        //    }
        //}

        population = newPopulation;
        if (population[0].fitness < bestFitness) {
            bestSolution = population[0].rects; /// ?
            bestFitness = population[0].fitness;
            std::cout << "Best solution : Fitness : "<< bestFitness << ", Iteration : "<< i << std::endl;
        }
        //std::cout << "coucou4" << std::endl;
    }

    LGFi(binList, bestSolution);
}

std::vector<Solution> GeneticAlgorithm::generateInitialPopulation(int popSize, float kappa) {
    std::vector<Solution> initialPopulation;
    addNewSolutions(initialPopulation, popSize, kappa);
    return initialPopulation;
}

void GeneticAlgorithm::addNewSolutions(std::vector<Solution>& newPopulation, int popSize, float kappa) {
    for(int i = newPopulation.size(); i < popSize; i++) {
        newPopulation.push_back({ std::vector<Rect*>(FileData::NB_ITEMS), -1 });
        std::vector<Rect*>* remainingRects = new std::vector<Rect*>(FileData::RECT_LIST);
        deterministicSequence(remainingRects);
        int nbItems = FileData::NB_ITEMS;
        std::vector<int> positions(nbItems);

        for (int j = 0; j < nbItems; j++) {
            positions[j] = j;
        }

        for (int pos = 0; pos < nbItems; ++pos) {
            std::vector<double> values(remainingRects->size());

            for (int k = 0; k < remainingRects->size(); k++) {
                values[k] = calculateValue(nbItems, positions[k], kappa);
            }

            int selectedIndex = rouletteWheelSelection(values);
            newPopulation[i].rects[pos] = remainingRects->at(selectedIndex);
            remainingRects->erase(remainingRects->begin() + selectedIndex);
            positions.erase(positions.begin() + selectedIndex);
        }

        // met à jour la fitness de la solution ajoutée
        calculateFitness(newPopulation[i]);
        //std::cout <<"fitness "<< newPopulation[i].fitness << std::endl;
    }

    // tri par ordre croissant de fitness
    std::sort(newPopulation.begin(), newPopulation.end(), compareFitness);
    //std::cout << "tri ou non" << std::endl;
    //for (Solution p : newPopulation) std::cout << p.fitness << std::endl;
    //std::cout << "tri ou non fin" << std::endl;

}

void GeneticAlgorithm::deterministicSequence(std::vector<Rect*>* rects) {
    // rotation pour que la largeur soit supérieure à la hauteur
    for (Rect* rect : *rects) {
        if (rect->getWidth() < rect->getHeight()) {
            rect->setRotation(true);
        }
    }
    // tri par aire décroissante
    std::sort(rects->begin(), rects->end(), Rect::compareRects);
}

double GeneticAlgorithm::calculateValue(int nbItems, int position, float kappa) {
    return nbItems - position;
    //return std::pow(nbItems - position+1, kappa);
}

int GeneticAlgorithm::rouletteWheelSelection(const std::vector<double>& values) {
    //std::cout << "roulette" << std::endl;
    //for (double v : values) std::cout << v << std::endl;
    double sum = std::accumulate(values.begin(), values.end(), 0.0);
    std::vector<double> probabilities(values.size());
    std::transform(values.begin(), values.end(), probabilities.begin(), [sum](double v) { return v / sum; });
    //std::cout<<"proba"<<std::endl;
    //for (double p : probabilities) std::cout << p << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dist(probabilities.begin(), probabilities.end());
    int res = dist(gen);
    //std::cout << "res" << res << std::endl;
    return res;
}

double GeneticAlgorithm::crossoverProbability(int popSize, int pos_s, int pos_sc, double delta) {
    double numerator = pow(popSize - 1 - pos_sc, delta);

    double denominator = 0.0;
    for (int i = 0; i < popSize; ++i) {
        if(i!=pos_s) denominator += pow(popSize - 1 - i, delta);
    }

    return numerator / denominator;
}

std::vector<Solution> GeneticAlgorithm::crossover(const std::vector<Solution>& population, double crossoverRate, double delta) {
    int popSize = population.size();
    int bestSolutionsSize = crossoverRate * popSize;
    std::vector<Solution> bestSolutions(population.begin(), population.begin() + bestSolutionsSize);
    //std::cout << "a" << std::endl;
    for (int i = 0; i < bestSolutionsSize; i++) {
        //std::cout << "b" << std::endl;

        // Roulette-wheel selection
        std::vector<double> probabilities(bestSolutionsSize);
        for (int j = 0; j < bestSolutionsSize; j++) {
            probabilities[j] = crossoverProbability(popSize, i, j, delta);
        }
        //std::cout << "c" << std::endl;
        
        int crossoverIndex = -1;
        do {
            crossoverIndex = rouletteWheelSelection(probabilities);
        } while (crossoverIndex == i); // tant que la solution de crossover est identique à la solution courante

        //std::cout << "d" << std::endl;
        Solution s = population[i]; // solution courante
        Solution sCrossover = population[crossoverIndex]; // solution avec laquelle on réalise le crossover

        Solution sChild = {std::vector<Rect*>(s.rects.size()), -1};

        int k = 0, l = 0, r = 0;
        std::vector<bool> usedRectangles(s.rects.size(), false);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        while (r < sChild.rects.size()) {
            if (s.rects[k]->getId() == sCrossover.rects[l]->getId()) {
                sChild.rects[r] = s.rects[k];
                //usedRectangles[k] = true;
            }
            else {
                double p = dis(gen);
                if (p <= 0.75) {
                    sChild.rects[r] = s.rects[k];
                }
                else {
                    sChild.rects[r] = sCrossover.rects[l];
                }
            }
            
            usedRectangles[sChild.rects[r]->getId()-1] = true;

            // on incrémente les pointeurs
            r++;

            while (k < s.rects.size() && usedRectangles[s.rects[k]->getId()-1]) {
                k++;
            }

            while (l < s.rects.size() && usedRectangles[sCrossover.rects[l]->getId()-1]) {
                l++;
            }
        }

        // évaluation de la nouvelle solution
        calculateFitness(sChild);
        if (sChild.fitness < s.fitness) bestSolutions[i] = sChild;
    }

    return bestSolutions;
}

void GeneticAlgorithm::calculateFitness(Solution& s) {
    std::vector<Bin*> binList;
    LGFi(binList, s.rects);
    s.fitness = calculateFitness(binList);
}

double GeneticAlgorithm::calculateFitness(const std::vector<Bin*>& binList) {
    int binsUsed = binList.size();

    if (binsUsed == 0) {
        return 0.0; // Aucune bin utilisée
    }

    const Bin* lastBin = binList[binsUsed - 1];
    int lastBinArea = FileData::BIN_WIDTH * FileData::BIN_HEIGHT - lastBin->getEmptySpace();

    double fillPercentage = (double)lastBinArea / (FileData::BIN_WIDTH * FileData::BIN_HEIGHT);

    double fitness = binsUsed-1 + fillPercentage;

    //std::cout << fitness << std::endl;
    return fitness;
}

bool GeneticAlgorithm::compareFitness(const Solution& a, const Solution& b) {
    return a.fitness < b.fitness;
}