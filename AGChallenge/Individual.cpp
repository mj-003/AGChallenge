#include "Individual.h"

/* ---------- Constructors ----------- */

Individual::Individual(std::vector<int> genotype) 
	: genotype(std::move(genotype)), fitness(-1) 
{}


Individual::Individual() 
	: fitness(-1) 
{}

Individual::Individual(const Individual& other) 
	: genotype(other.genotype), fitness(other.fitness) 
{}

Individual::Individual(Individual&& other) noexcept
	: genotype(std::move(other.genotype)), fitness(other.fitness) 
{}

Individual& Individual::operator=(const Individual& other) 
{
	if (this != &other) 
	{
		genotype = other.genotype;
		fitness = other.fitness;
	}

	return *this;
}

Individual& Individual::operator=(Individual&& other) noexcept
{
	if (this != &other) 
	{
		genotype = std::move(other.genotype);
		fitness = other.fitness;
	}

	return *this;
}



/* ---------- Public Methods ---------- */

void Individual::evaluate(CLFLnetEvaluator &evaluator) 
{
	if (fitness == -1) 
	{
		fitness = evaluator.dEvaluate(&genotype);
	}
}


double Individual::getFitness() const 
{
	return fitness;
}


void::Individual::mutate(double mutationRatio, CLFLnetEvaluator& evaluator) 
{
	for (int i = 0; i < genotype.size(); i++) {
		if (dRand() < mutationRatio) {
			genotype.at(i) = lRand(evaluator.iGetNumberOfValues(i));
		}
	}
}


std::vector<Individual> Individual::cross(Individual& other, double crossoverRatio, CLFLnetEvaluator& evaluator)
{
	if (dRand() < crossoverRatio) 
	{
		int crossoverPoint = lRand(genotype.size());

		std::vector<int> child1Genotype;
		std::vector<int> child2Genotype;
    

		for (int i = 0; i < crossoverPoint; i++)    
		{
			child1Genotype.push_back(this->genotype[i]);
			child2Genotype.push_back(other.genotype[i]);
		}

		for (int i = crossoverPoint; i < this->genotype.size(); i++) 
		{
			child1Genotype.push_back(other.genotype[i]);
			child2Genotype.push_back(this->genotype[i]);
		}


		return std::vector<Individual> { Individual(std::move(child1Genotype)), Individual(std::move(child2Genotype)) };
	}

	else return std::vector<Individual> { *this, other };
}

