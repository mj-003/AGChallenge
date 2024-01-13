#pragma once
#include "Evaluator.h"
#include "Individual.h"
#include <vector>

class GeneticAlgorithm
{
public:

	GeneticAlgorithm(int populationSize, double mutationRatio, double crossoverRatio, CLFLnetEvaluator& evaluator);
	
	void run(int rounds);


private:

	int populationSize;
	double mutationRatio;
	double crossoverRatio;

	CLFLnetEvaluator& evaluator;
	std::vector<Individual> population;
	Individual bestIndividual;

	void initializePopulation();
	void singleIteration();
	void findBestIndividual();
	int selectParentIndex(int tournamentSize);

	
	int iterationsWithoutImprovement;
	const int stagnationThreshold = 10;
	int tournamentSize = 10;

};
