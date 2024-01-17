#pragma once
#include <vector>
#include "Evaluator.h"
#include "MyMath.h"

class Individual
{
public:

	Individual();
	Individual(std::vector<int> genotype);

	double getFitness() const;
	void evaluate(CLFLnetEvaluator& evaluator);

	void mutate(double mutationRate, CLFLnetEvaluator& evaluator);
	std::vector<Individual> cross(const Individual& other, double crossoverRate, CLFLnetEvaluator& evaluator) const;


private:

	std::vector<int> genotype;  
	double fitness;
};