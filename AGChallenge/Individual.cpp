#include "Individual.h"


/* ---------- Constructors ----------- */

Individual::Individual() 
	: genotype(std::vector<int>()), fitness(-1)
{}


Individual::Individual(std::vector<int> genotype)
	: genotype(std::move(genotype)), fitness(-1) 
{}



/* ---------- Evaluation ---------- */

void Individual::evaluate(CLFLnetEvaluator& evaluator)
{
	if (fitness == -1)
	{
		fitness = evaluator.dEvaluate(&genotype);
	}
}



/* ---------- Mutation ---------- */

void::Individual::mutate(double mutationRatio, CLFLnetEvaluator& evaluator)
{
	for (int i = 0; i < genotype.size(); i++)
	{
		if (dRand() < mutationRatio)
		{
			if (dRand() < 0.24) genotype[i] = 0;
			else genotype[i] = lRand(evaluator.iGetNumberOfValues(i));
		}
	}
}



/* ---------- Crossover ---------- */

std::vector<Individual> Individual::cross(const Individual& other, double crossoverRatio, CLFLnetEvaluator& evaluator) const
{
    if (dRand() < crossoverRatio)
    {
        int crossoverPoint = lRand(genotype.size());
        while (crossoverPoint == 0) crossoverPoint = lRand(genotype.size());

        std::vector<int> genotype1 = genotype;
        std::vector<int> genotype2 = other.genotype;

        for (int i = crossoverPoint; i < genotype.size(); i++)
        {
            std::swap(genotype1[i], genotype2[i]);
        }

        Individual child1(std::move(genotype1));
        Individual child2(std::move(genotype2));

        return std::vector<Individual> { std::move(child1), std::move(child2) };
    }
    else
    {
        return std::vector<Individual> { *this, other };
    }
}



/* ---------- Getters ---------- */

double Individual::getFitness() const
{
    return fitness;
}