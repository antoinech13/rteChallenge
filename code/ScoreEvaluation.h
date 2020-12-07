#pragma once
#include <vector>
#include <time.h>
#include "dataCollector.h" 
#include "Intervention.h"


class ScoreEvaluation
{

public:
	ScoreEvaluation(dataCollector data, vector<int> interTime);
	vector<vector<int>> getEvalScenario();


private:
	dataCollector data;
	vector<int> scenarios;
	vector<int> interTime;
	vector<Intervention> interventions;
	vector<vector<int>> evalScenario;
	vector<vector<int>> extractScenario();
	vector<vector<vector<pair<int, vector<int>>>>> extractAllRisk();
	vector<int> avgOnSc();
	int Obj1();



};

