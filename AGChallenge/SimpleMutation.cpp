#include "SimpleMutation.h"


void SimpleMutation::mutate(Individual& individual, double mutationRate, CLFLnetEvaluator& evaluator)
{
	for (int i = 0; i < individual.genotype.size(); i++)
	{
		if (dRand() < mutationRate)
		{
			individual.genotype.at(i) = evaluator.iGetNumberOfValues(i);
		}
	}
}