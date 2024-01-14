#pragma once
#include "IMutation.h"

class SimpleMutation : public IMutation
{
public:
	void mutate(Individual& individual, double mutationRate, CLFLnetEvaluator& evaluator) override;
};
