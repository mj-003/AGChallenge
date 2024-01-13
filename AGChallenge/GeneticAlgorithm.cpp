#include "GeneticAlgorithm.h"


/* ---------- Constructor ---------- */

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double crossProbability, double mutationProbability, CLFLnetEvaluator& evaluator) :
	crossoverRatio(crossProbability),
	mutationRatio(mutationProbability),
	evaluator(evaluator),
	populationSize(populationSize),
	iterationsWithoutImprovement(0)
{
	initializePopulation();
	bestIndividual = population.at(0);
}



/* ---------- Main Function ---------- */

void GeneticAlgorithm::run(int iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		singleIteration();
		findBestIndividual();
		std::cout << bestIndividual.getFitness() << std::endl;
	}
}



/* ---------- Initiation ---------- */

void GeneticAlgorithm::initializePopulation()
{
	size_t genotypeSize = evaluator.iGetNumberOfBits();

	for (int i = 0; i < populationSize; i++)
	{
		std::vector<int> genotype;

		for (int j = 0; j < genotypeSize; j++)
		{
			//genotype.push_back(lRand(evaluator.iGetNumberOfValues(j)));
			genotype.push_back(0);
		}

		population.emplace_back(Individual(genotype));
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

		if (!needHelp) 
		{
			parents.push_back(population.at(selectParentIndex(tournamentSize)));
			parents.push_back(population.at(selectParentIndex(tournamentSize)));

			std::vector<Individual> children = parents.at(0).cross(parents.at(1), crossoverRatio, evaluator);

			newPopulation.push_back(children.at(0));
			newPopulation.push_back(children.at(1));
		}

		else 
		{
			std::vector<int> newIndividual1gen, newIndividual2gen;

			for (int i = 0; i < evaluator.iGetNumberOfBits(); i++)
			{
				newIndividual1gen.push_back(lRand(evaluator.iGetNumberOfValues(i)));
				newIndividual2gen.push_back(lRand(evaluator.iGetNumberOfValues(i)));
			}

			newPopulation.push_back(Individual(newIndividual1gen));
			newPopulation.push_back(Individual(newIndividual2gen));

			//needHelp = false;
		}

		
	}

	for (int i = 0; i < newPopulation.size(); i++)
	{
		newPopulation.at(i).mutate(mutationRatio, evaluator);
	}

	population = newPopulation;
}


int GeneticAlgorithm::selectParentIndex(int tournamentSize)
{
	int winnerIndex = iRand() % populationSize;
	double winnerFitness = population[winnerIndex].getFitness();

	for (int i = 0; i < tournamentSize; i++)
	{
		int competitorIndex = iRand() % populationSize;
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
		if (population.at(i).getFitness() > bestIndividual.getFitness())
		{
			bestIndividual = population.at(i);
			improved = true;
		}
	}

	if (improved) 
	{
		iterationsWithoutImprovement = 0;
	}

	else 
	{
		iterationsWithoutImprovement++;
	}

	if (iterationsWithoutImprovement >= stagnationThreshold) 
	{
		if (tournamentSize++ > populationSize) 
		{
			needHelp = true;
			//tournamentSize = populationSize;
		}
		//else tournamentSize++;
	}
}
