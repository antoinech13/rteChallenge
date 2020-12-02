#pragma once
#include "dataCollector.h"
#include "Intervention.h"
#include <map>
#include <string>

class Solver
{

public:
	Solver(dataCollector data);

private:
	dataCollector data;
	map<string, int> randInitialisation();
	map<string, vector<string>> violatExclusion(map<string, int> interventions);
};

nik