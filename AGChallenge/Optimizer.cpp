#include "Optimizer.h"

#include <cfloat>
#include <iostream>
#include <windows.h>

using namespace std;

COptimizer::COptimizer(CLFLnetEvaluator &cEvaluator)
	: c_evaluator(cEvaluator), geneticAlgorithm(100, 0.9, 0.0001, cEvaluator)
{
	random_device c_seed_generator;
	c_rand_engine.seed(c_seed_generator());
	d_current_best_fitness = 0;
}


void COptimizer::vInitialize()
{
	d_current_best_fitness = -DBL_MAX;
	v_current_best.clear();
}


void COptimizer::vRunIteration()
{
	geneticAlgorithm.singleIteration();
	geneticAlgorithm.findBestIndividual();

	d_current_best_fitness = geneticAlgorithm.bestFitness;
	v_current_best = *geneticAlgorithm.bestIndividual->getGenotype();
	std::cout << geneticAlgorithm.bestFitness << std::endl;
}



void COptimizer::v_fill_randomly(vector<int> &vSolution)
{
	vSolution.resize((size_t)c_evaluator.iGetNumberOfBits());

	for (int ii = 0; ii < vSolution.size(); ii++)
	{
		vSolution.at(ii) = lRand(c_evaluator.iGetNumberOfValues(ii));
	}
}
