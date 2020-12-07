#include "ScoreEvaluation.h"
#include <algorithm> 

using namespace std;


vector<vector<int>> ScoreEvaluation::getEvalScenario() {
	return this->evalScenario;
}


ScoreEvaluation::ScoreEvaluation(dataCollector data, vector<int> interTime) {
	this->data = data;
	this->interTime = interTime;
	this->interventions = data.getInterventions();
	this->scenarios = data.getScenarioNumber();
	this->evalScenario = extractScenario();
}

int ScoreEvaluation::Obj1() {
	vector<int> avgByTime;
	for(int temps = 0; temps < this->evalScenario.size(); temps++)

}

vector<int> ScoreEvaluation::avgOnSc(int i) {
	for (int scenario = 0; scenario < this->evalScenario[i].size(); scenario++)
}

vector<vector<int>> ScoreEvaluation::extractScenario() {
	vector<vector<int>> value; // line: scenario column: time
	vector<vector<vector<pair<int, vector<int>>>>> riskByInterventions = extractAllRisk();
	vector<int> valueForOneScenario, scNb = this->scenarios, idxStartTime = this->interTime;
	int risk = 0;

	for (int j = 0; j < this->data.getT(); j++) {
		for (int k = 0; k < scNb[j]; k++) {
			for (int i = 0; i < riskByInterventions.size(); i++) {
				risk += riskByInterventions[i][j][(int)interTime[i]-1].second[k];
			}
			valueForOneScenario.push_back(risk);
			risk = 0;
		}
		value.push_back(valueForOneScenario);
		valueForOneScenario.clear();
	}

	return value;
}



vector<vector<vector<pair<int, vector<int>>>>> ScoreEvaluation::extractAllRisk() {
	vector<vector<vector<pair<int, vector<int>>>>> value;

	for (int i = 0; i < this->interventions.size(); i++)
		value.push_back(this->interventions[i].getRisk());
	return value;
}