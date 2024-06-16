#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <vector>

#include "Rect.h"
#include "Bin2.h"
#include "Tools.h"
#include <random>
#include <iostream>

using namespace std;

class SimulatedAnnealing {
public:

    SimulatedAnnealing(double t_0, double mu, int n1, int n2);
    ~SimulatedAnnealing();
    vector<vector<int>> transformConfigToInt(vector<Bin2*> binList);
    vector<Bin2*> runAlgorithm(vector<Bin2*> binList, vector<vector<FreeRect>> freeRects);
    pair<bool, vector<FreeRect>> FusionRectFreeRect(vector<FreeRect> tempFreeRects1, Rect* rec1);
    pair<bool, vector<FreeRect>> FusionFreeRect(vector<FreeRect> tempFreeRects1);

private:
    double t_0;
    double f_min;
    vector<double> f_actual;
    double mu;
    int n1;
    int n2;
    std::mt19937 gen;
    pair<vector<Bin2*>, vector<vector<FreeRect>>> x_min;
    pair<vector<Bin2*>, vector<vector<FreeRect>>> x_actual;

};

#endif