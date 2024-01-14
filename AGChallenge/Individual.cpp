#include "Individual.h"


/* ---------- Constructors and Operators ----------- */

Individual::Individual() 
	: genotype(std::make_unique<std::vector<int>>()), fitness(-1) 
{}


Individual::Individual(std::unique_ptr<std::vector<int>> genotype)
	: genotype(std::move(genotype)), fitness(-1) 
{}


Individual::Individual(const Individual& other)
	: genotype(std::make_unique<std::vector<int>>(*other.genotype)), 
	  fitness(other.fitness) 
{}


Individual::Individual(Individual&& other) noexcept = default;


Individual& Individual::operator=(const Individual& other) 
{
	if (this != &other) 
	{
		genotype = std::make_unique<std::vector<int>>(*other.genotype);
		fitness = other.fitness;
	}
	return *this;
}


Individual& Individual::operator=(Individual&& other) noexcept = default;


Individual::~Individual() = default;



/* ---------- Calculate Fitness Value ---------- */

void Individual::evaluate(CLFLnetEvaluator& evaluator)
{
	if (fitness == -1)
	{
		fitness = evaluator.dEvaluate(genotype.get());
	}
}


double Individual::getFitness() const
{
	return fitness;
}



/* ---------- Mutate Individual ---------- */

void::Individual::mutate(double mutationRatio, CLFLnetEvaluator& evaluator)
{
	for (int i = 0; i < genotype->size(); i++)
	{
		if (dRand() < mutationRatio)
		{
			if (dRand() < 0.5)
				genotype->at(i) = 0;
			else
				genotype->at(i) = lRand(evaluator.iGetNumberOfValues(i));
		}
	}
}



/* ---------- Cross two Individuals ---------- */

std::vector<Individual> Individual::cross(Individual& other, double crossoverRatio, CLFLnetEvaluator& evaluator)
{
	if (dRand() < crossoverRatio)
	{
		int crossoverPoint = lRand(genotype->size());

		auto genotype1 = std::make_unique<std::vector<int>>(*genotype); 
		auto genotype2 = std::make_unique<std::vector<int>>(*other.genotype); 

		for (int i = crossoverPoint; i < genotype->size(); i++)
		{
			std::swap(genotype1->at(i), genotype2->at(i)); 
		}

		Individual child1(std::move(genotype1));
		Individual child2(std::move(genotype2));

		return std::vector<Individual> { child1, child2 };
	}

	else
	{
		return std::vector<Individual> { *this, other };
	}
}
