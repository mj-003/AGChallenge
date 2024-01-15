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
		std::cout << bestFitness << std::endl;
	}
}



/* ---------- Initiation ---------- */

void GeneticAlgorithm::initializePopulation() 
{
	size_t genotypeSize = evaluator.iGetNumberOfBits();

	for (int i = 0; i < populationSize; i++) 
	{
		auto genotype = std::make_unique<std::vector<int>>();

		for (int j = 0; j < genotypeSize; j++) 
		{
			genotype->push_back(lRand(evaluator.iGetNumberOfValues(j)));
		}

		population.emplace_back(std::move(genotype));
	}
}




/* ---------- Helper Functions ---------- */

void GeneticAlgorithm::singleIteration()
{

	vector<Individual> newPopulation;
	
	for (int i = 0; i < population.size(); i++)
	{
		population.at(i).evaluate(evaluator);
	}

	while (newPopulation.size() < population.size() - 1)
	{
		std::vector<Individual> parents;
		std::vector<Individual> children;

		if (!stagnation) 
		{
			int fstParentIndex = selectParentIndex(tournamentSize, -1);
			int sndParentIndex = selectParentIndex(tournamentSize, fstParentIndex);

			parents.push_back(population.at(fstParentIndex));
			parents.push_back(population.at(sndParentIndex));
		}

		else 
		{
			auto genotype1 = std::make_unique<std::vector<int>>(evaluator.iGetNumberOfBits(), 0);
			auto genotype2 = std::make_unique<std::vector<int>>(evaluator.iGetNumberOfBits(), 0);

			parents.emplace_back(std::move(genotype1));
			parents.emplace_back(std::move(genotype2));

			stagnation = false;
		}

		children = parents.at(0).cross(parents.at(1), crossoverRatio, evaluator);

		newPopulation.push_back(std::move(children.at(0)));
		newPopulation.push_back(std::move(children.at(1)));
		
	}

	for (int i = 0; i < newPopulation.size(); i++)
	{
		 // if (dRand() < mutationRatio) 
			newPopulation.at(i).mutate(mutationRatio, evaluator);
	}

	population = std::move(newPopulation);
}


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
		if (population.at(i).getFitness() > bestFitness)
		{
			bestFitness = population.at(i).getFitness();
			improved = true;
		}
	}

	checkIfStagnation(improved);
}


void GeneticAlgorithm::checkIfStagnation(bool improved)
{
	iterationsWithoutImprovement = improved ? 0 : iterationsWithoutImprovement ++;
	stagnation = iterationsWithoutImprovement >= stagnationThreshold;
}



