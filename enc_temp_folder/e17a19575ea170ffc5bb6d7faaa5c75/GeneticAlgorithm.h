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

	size_t populationSize;
	double mutationRatio;
	double crossoverRatio;
	double bestFitness;

	CLFLnetEvaluator& evaluator;
	std::vector<Individual> population;

	void initializePopulation();
	void singleIteration();
	void findBestIndividual();
	int selectParentIndex(int tournamentSize);


	/* ------ helping with stagnation ------ */

	int iterationsWithoutImprovement;
	const int stagnationThreshold = 10;
	int tournamentSize = 10;
	bool stagnation = false;


};
