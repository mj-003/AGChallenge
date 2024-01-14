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
	int selectParentIndex(int tournamentSize, int occupiedIndex);


	/* ------ helping with stagnation ------ */

	int iterationsWithoutImprovement;
	const int stagnationThreshold = 10;
	int tournamentSize = max(populationSize % 10, 2);
	bool stagnation = false;

	void checkIfStagnation(bool improved);


};
