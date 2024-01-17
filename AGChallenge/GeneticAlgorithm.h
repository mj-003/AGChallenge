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

	const size_t populationSize;
	double mutationRatio;
	double crossoverRatio;
	double bestFitness;

	CLFLnetEvaluator& evaluator;
	std::vector<Individual> population;

	void initializePopulation();
	void singleIteration();
	void findBestIndividual();
	int selectParentIndex(int tournamentSize, int occupiedIndex);
	

	/* ------ handling stagnation ------ */

	int iterationsWithoutImprovement;
	const int stagnationThreshold = 50;
	const int tournamentSize = 2;
	bool stagnation = false;
	const double globalMutationRatio = 0.0005;

	void checkIfStagnation(bool improved);
	void performGlobalMutation();

};
