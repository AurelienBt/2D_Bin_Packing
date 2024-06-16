#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>

#include "Tools.h"
#include "Bin.h"

struct Solution {
	std::vector<Rect*> rects;
	double fitness;
};

class GeneticAlgorithm
{
public:
	GeneticAlgorithm();
	~GeneticAlgorithm();

	void LGFi(std::vector<Bin*>& binList);
	void LGFi(std::vector<Bin*>& binList, std::vector<Rect*> orderedRectangles);

	void GenAlgo(std::vector<Bin*>& binList, int popSize = 10, float crossoverRate = 0.7, float kappa = 10, float delta = 20);



private:

	bool canFit(const Rect& rect, const FreeRect& freeRect);
	int insertionScore(const Rect& rect, const FreeRect& freeRect);
	std::pair<Rect*, int> getShortestRectangle(const std::vector<Rect*>& rectangles);
	std::vector<FreeRect> cutRectangle(const Rect& item, const FreeRect& freeRect);
	std::vector<FreeRect> cutRectangle(const Rect& item, const FreeRect& freeRect, const int shortestRectangle);
	FreeRect getNextFreeRect(const std::vector<FreeRect>& freeRects);

	std::vector<Solution> generateInitialPopulation(int popSize, float kappa);
	std::vector<Solution> crossover(const std::vector<Solution>& population, double crossoverRate, double delta);

	void addNewSolutions(std::vector<Solution>& newPopulation, int popSize, float kappa);
	void deterministicSequence(std::vector<Rect*>* rects);
	double calculateValue(int nbItems, int position, float kappa);
	int rouletteWheelSelection(const std::vector<double>& values);
	double crossoverProbability(int popSize, int pos_s, int pos_sc, double delta);
	void calculateFitness(Solution& s);
	double calculateFitness(const std::vector<Bin*>& binList);
	static bool compareFitness(const Solution& a, const Solution& b);
};

#endif
