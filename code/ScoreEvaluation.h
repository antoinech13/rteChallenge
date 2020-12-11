#pragma once
#include <vector>
#include <time.h>
#include "dataCollector.h" 
#include "Intervention.h"


class ScoreEvaluation
{

public:
	ScoreEvaluation(dataCollector data, vector<int> interTime);
	double getEvalScenario();
	double newEvalScenario();


private:
	dataCollector data;
	vector<int> scenarios;
	vector<int> interTime;
	vector<Intervention> interventions;
	double evalScenario;
	double extractScenario();
	vector<vector<vector<pair<int, vector<int>>>>> extractAllRisk();




};

