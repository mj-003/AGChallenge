#include "GeneticAlgorithm.h"


/* ---------- Constructor ---------- */

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossRatio, double mutationRatio, CLFLnetEvaluator& evaluator) 
	:
	crossoverRatio(crossRatio),
	mutationRatio(mutationRatio),
	evaluator(evaluator),
	populationSize(populationSize),
	iterationsWithoutImprovement(0),
	bestFitness(0)
{
	initializePopulation();
}



/* ---------- Run Algorithm ---------- */

void GeneticAlgorithm::run(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		singleIteration();
		findBestIndividual();
		std::cout << i << " " << bestFitness << std::endl;
	}
}



/* ---------- Initialization ---------- */

void GeneticAlgorithm::initializePopulation() 
{
	size_t genotypeSize = evaluator.iGetNumberOfBits();

	for (int i = 0; i < populationSize; i++) 
	{
		std::vector<int> genotype;
		genotype.reserve(genotypeSize);

		for (int j = 0; j < genotypeSize; j++) 
		{
			genotype.push_back(lRand(evaluator.iGetNumberOfValues(j)));
		}

		population.emplace_back(std::move(genotype));
	}
}



/* ---------- Single Iteration ---------- */

void GeneticAlgorithm::singleIteration()
{
	vector<Individual> newPopulation;
	
	for (int i = 0; i < population.size(); i++)
	{
		population[i].evaluate(evaluator);
	}

	while (newPopulation.size() < population.size() - 1)
	{
		std::vector<Individual> parents;
		std::vector<Individual> children;

		if (stagnation) performGlobalMutation();

		int fstParentIndex = selectParentIndex(tournamentSize, -1);
		int sndParentIndex = selectParentIndex(tournamentSize, fstParentIndex);

		parents.push_back(population[fstParentIndex]);
		parents.push_back(population[sndParentIndex]);


		children = parents[0].cross(parents[1], crossoverRatio);

		newPopulation.push_back(std::move(children[0]));
		newPopulation.push_back(std::move(children[1]));
	}

	for (int i = 0; i < newPopulation.size(); i++)
	{
		newPopulation[i].mutate(mutationRatio, evaluator);
	}

	population = std::move(newPopulation);
}



/* ---------- Helpers ---------- */

int GeneticAlgorithm::selectParentIndex(int tournamentSize, int occupiedIndex)
{
	int winnerIndex = iRand() % populationSize;
	while (winnerIndex == occupiedIndex) winnerIndex = iRand() % populationSize;

	double winnerFitness = population[winnerIndex].getFitness();

	for (int i = 0; i < tournamentSize; i++)
	{
		int competitorIndex = iRand() % populationSize;
		while (competitorIndex == occupiedIndex) competitorIndex = iRand() % populationSize;

		double competitorFitness = population[competitorIndex].getFitness();

		if (competitorFitness > winnerFitness)
		{
			winnerIndex = competitorIndex;
			winnerFitness = competitorFitness;
		}
	}

	return winnerIndex;
}


void GeneticAlgorithm::findBestIndividual()
{
	bool improved = false;

	for (int i = 0; i < population.size(); i++)
	{
		if (population[i].getFitness() > bestFitness)
		{
			bestFitness = population[i].getFitness();
			improved = true;
		}
	}

	checkIfStagnation(improved);
}


void GeneticAlgorithm::checkIfStagnation(bool improved)
{
	improved ? iterationsWithoutImprovement = 0 : iterationsWithoutImprovement++;
	stagnation = iterationsWithoutImprovement >= stagnationThreshold;
}


void GeneticAlgorithm::performGlobalMutation()
{
	if (stagnation)
	{
		for (int i = 0; i < population.size(); i++)
		{
			if (dRand() < 0.5)
			{
				population[i].mutate(globalMutationRatio, evaluator);
			}
		}
		stagnation = false;
	}
}



