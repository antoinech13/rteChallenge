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
	vector<int> randInitialisation();
	map<int, vector<int>> violatExclusions(vector<int> interventions);
	vector<pair<int, int>> getTDt(vector<int> interTime, vector<int> tabInter, vector<Intervention> interventions);
	vector<bool> testIfInSeason(vector<int> tInSeasons, vector<pair<int, int>> tDt)
};
