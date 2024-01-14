#pragma once
#include <vector>
#include "Evaluator.h"
#include "MyMath.h"

class Individual
{
public:

	Individual();
	Individual(std::unique_ptr<std::vector<int>> genotype);

	Individual(const Individual& other);
	Individual(Individual&& other) noexcept;

	Individual& operator=(const Individual& other);
	Individual& operator=(Individual&& other) noexcept;

	~Individual();

	double getFitness() const;
	void evaluate(CLFLnetEvaluator& evaluator);

	void mutate(double mutationRate, CLFLnetEvaluator& evaluator);
	std::vector<Individual> cross(Individual& other, double crossoverRate, CLFLnetEvaluator& evaluator);


private:

	std::unique_ptr<std::vector<int>> genotype;
	double fitness;
};