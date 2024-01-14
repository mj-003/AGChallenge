#pragma once

#include "Evaluator.h"
#include "Individual.h"
#include "MyMath.h"

#include <vector>

class IMutation
{
public:
	virtual void mutate(Individual& individual, double mutationRate, CLFLnetEvaluator& evaluator) = 0;
};