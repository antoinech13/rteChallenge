#pragma once
#include <vector>
#include <time.h>
#include "dataCollector.h" 
#include "Intervention.h"


class ScoreEvaluation
{

public:
	ScoreEvaluation(dataCollector data, vector<int> interTime);
	ScoreEvaluation();
	double getEvalScenario();
	double newEvalScenario();


private:
	dataCollector data;
	vector<int> scenarios;
	vector<int> interTime;
	vector<Intervention> interventions;
	float alpha;
	float quantile;
	double evalScenario;
	double extractScenario();
	double extractScenario2();
	double extractScenarioFinal();
	vector<vector<vector<pair<int, vector<int>>>>> extractAllRisk();




};

