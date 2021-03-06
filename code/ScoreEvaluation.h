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
	double extractScenarioFinal(vector<int> interTime);
	double extractScenario(vector<int> interTime);
	void print(vector<vector<vector<pair<int, vector<double>>>>> riskByInterventions);

private:
	dataCollector data;
	vector<double> scenarios, means;
	vector<vector<double>> risks;
	vector<Intervention> interventions;
	float alpha;
	float quantile;
	//double extractScenario(vector<int> interTime);
	double extractScenario2();
	vector<vector<vector<pair<int, vector<double>>>>> extractAllRisk();
	int keyToIdx(int time, vector<pair<int, vector<double>>> rsk);



};

