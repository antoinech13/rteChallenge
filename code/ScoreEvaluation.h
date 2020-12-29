#pragma once
#include <vector>
#include <time.h>
#include "dataCollector.h" 
#include "Intervention.h"


class ScoreEvaluation
{

public:
	ScoreEvaluation(dataCollector data);
	ScoreEvaluation();
	double extractScenario(vector<int> interTime);


private:
	dataCollector data;
	vector<int> scenarios, means;
	vector<vector<int>> risks;
	vector<Intervention> interventions;
	float alpha;
	float quantile;
	double extractScenario2();
	double extractScenarioFinal();
	vector<vector<vector<pair<int, vector<int>>>>> extractAllRisk();




};

