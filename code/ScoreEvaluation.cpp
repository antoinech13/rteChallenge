#include "ScoreEvaluation.h"
#include <algorithm> 

using namespace std;

ScoreEvaluation::ScoreEvaluation(dataCollector data, vector<int> interTime) {
	this->data = data;
	this->interTime = interTime;
	this->interventions = data.getInterventions();
	this->scenarios = data.getScenarioNumber();

}


vector<vector<int>> ScoreEvaluation::extractScenario() {
	vector<vector<int>> value; // line: scenarion column: time
	vector<vector<vector<pair<int, vector<int>>>>> riskByInterventions = extractAllRisk();
	vector<int> idxStartTime = this->interTime;

	for (int i = 0; i < riskByInterventions.size(); i++) {

	}

}

vector<vector<vector<pair<int, vector<int>>>>> ScoreEvaluation::extractAllRisk() {
	vector<vector<vector<pair<int, vector<int>>>>> value;

	for (int i = 0; i < this->interventions.size(); i++)
		value.push_back(this->interventions[i].getRisk());
	return value;
}