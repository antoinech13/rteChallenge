#include "ScoreEvaluation.h"
#include <algorithm> 

using namespace std;


double ScoreEvaluation::getEvalScenario() {
	return this->evalScenario;
}
double ScoreEvaluation::newEvalScenario() {
	this->evalScenario = extractScenario();
	return this->evalScenario;
}


ScoreEvaluation::ScoreEvaluation(dataCollector data, vector<int> interTime) {
	this->data = data;
	this->interTime = interTime;
	this->interventions = data.getInterventions();
	this->scenarios = data.getScenarioNumber();
	this->evalScenario = extractScenario();
}


double ScoreEvaluation::extractScenario() {
	vector<vector<int>> value; // line: scenario column: time
	vector<vector<vector<pair<int, vector<int>>>>> riskByInterventions = extractAllRisk();
	vector<int> valueForOneScenario, scNb = this->scenarios, idxStartTime = this->interTime;
	int risk = 0;
	double avgBySc = 0, avgByTime = 0;

	for (int j = 0; j < this->data.getT(); j++) {
		for (int k = 0; k < scNb[j]; k++) {
			for (int i = 0; i < riskByInterventions.size(); i++) {
				risk += riskByInterventions[i][j][(int)interTime[i]-1].second[k];
			}
			valueForOneScenario.push_back(risk);
			avgBySc += risk;
			risk = 0;
		}
		value.push_back(valueForOneScenario);
		avgBySc /= valueForOneScenario.size();
		avgByTime += avgBySc;
		avgBySc = 0;
		valueForOneScenario.clear();

	}
	avgByTime /= value.size();
	return avgByTime;
}



vector<vector<vector<pair<int, vector<int>>>>> ScoreEvaluation::extractAllRisk() {
	vector<vector<vector<pair<int, vector<int>>>>> value;

	for (int i = 0; i < this->interventions.size(); i++)
		value.push_back(this->interventions[i].getRisk());
	return value;
}