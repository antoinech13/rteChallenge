#pragma once
#include <vector>
#include <time.h>
#include "dataCollector.h" 


class ScoreEvaluation
{

public:
	ScoreEvaluation(dataCollector data, vector<int> interTime);
	
	/*
	*return the scenario randomly selected btw 1 and the minimum of scenario number.
	*/
	int scenarioRandInit();

private:
	dataCollector data;
	vector<int> scenarios;
	vector<int> interTime;
	int minScenarioNbIdx;
	int ScenarioNb;

	/*
	*return the idex of the minimum of the vector scenrarios
	*/
	int minChoiceScenarioIdx();

};

