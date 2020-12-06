#pragma once
#include "dataCollector.h"
#include "Intervention.h"
#include <map>
#include <string>

class Solver
{

public:
	Solver(dataCollector data);
	map<int, vector<int>> exclusionViolation;
	vector<int> initTime;

private:
	dataCollector data;
	vector<int> randInitialisation();
	
};
