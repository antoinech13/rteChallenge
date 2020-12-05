#include "ScoreEvaluation.h"
#include <algorithm> 

using namespace std;

ScoreEvaluation::ScoreEvaluation(dataCollector data, vector<int> interTime) {
	this->data = data;
	this->interTime = interTime;//////////////////////////////////////////////utile?
	this->scenarios = data.getScenarioNumber();
	this->minScenarioNbIdx = minChoiceScenarioIdx();
	this->ScenarioNb = scenarioRandInit();

}

int ScoreEvaluation::minChoiceScenarioIdx() {
	int minIdx = min_element(this->scenarios.begin(), this->scenarios.end()) - this->scenarios.begin();
	return minIdx;
}

int ScoreEvaluation::scenarioRandInit() {
	srand(time(0));
	int value = rand() % (this->scenarios[this->minScenarioNbIdx] - 1) + 1;
	
	return value;
}