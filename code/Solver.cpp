#include "Solver.h"
#include "Intervention.h"
#include "ExclusionCheck.h"
#include "ScoreEvaluation.h"
#include "TimeChecker.h"
#include <time.h>
#include <map>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;


map<int, vector<int >> Solver::getExclusionViolation() {
	return this->exclusionViolation;
}

vector<int> Solver::getTime() {
	return this->Time;
}

double Solver::getObj1() {
	return this->obj1;
}



Solver::Solver(dataCollector data){
	this->data = data;
	this->Time = randInitialisation();
	vector<int> test = { 1,1,2 };
	this->checker = ExclusionCheck(data);
	this->s = ScoreEvaluation(data, this->Time);
	this->t = TimeChecker(data, this->Time);
	this->w = WorkloadCheck(data);
	this->exclusionViolation = checker.violatExclusions(Time);
	this->obj1 = s.getEvalScenario();
}



vector<int> Solver::randInitialisation() {
	vector<int> value;
	vector<Intervention> interventions = this->data.getInterventions();
	srand(time(0));

	for (int i = 0; i < interventions.size(); i++) {
		value.push_back(rand() % interventions[i].getTmax() + 1);
	}
	return value;
}

int Solver::scoreCheckWorload(vector<int> soluce) {
	int score = this->w.getWorkloadCheck(this->Time);
	return score;
}

map<int, vector<int>> Solver::scoreExclusion() {
	return this->exclusionViolation;

 }

vector<int> Solver::estimateViolation(vector<int> time) {

	w.getWorkloadCheck(time);
	this->t = TimeChecker(this->data, time);

	vector<int> exclusion = exclusionTab(time);
	vector<int> workload = this->w.getInterventionBad();
	vector<int> tme = this->t.getViolations();

	vector<int> violation;

	violation.insert(violation.end(), exclusion.begin(), exclusion.end());
	violation.insert(violation.end(), workload.begin(), workload.end());
	violation.insert(violation.end(), tme.begin(), tme.end());

	sort(violation.begin(), violation.end());
	violation.erase(unique(violation.begin(), violation.end()), violation.end());

	return violation;
}

void Solver::move() {
	
	vector<Intervention> interventions = this->data.getInterventions();
	vector<int> newTime = this->Time;
	vector<int> violation = estimateViolation(this->Time);
	vector<int> newViolation;

	while(violation.size() > 0) {
		
		int idx = rand() % violation.size();
		newTime[violation[idx]] = rand() % interventions[violation[idx]].getTmax() + 1;

		newViolation = estimateViolation(newTime);

		if (newViolation.size() < violation.size()) {
			this->Time = newTime;
			violation = newViolation;
		}

	}
}


vector<int> Solver::exclusionTab(vector<int> time) {
	map<int, vector<int>> exclusion = this->checker.violatExclusions(time);
	vector<int> exclusionVec;

	for (map<int, vector<int>>::iterator it = exclusion.begin(); it != exclusion.end(); it++)
		exclusionVec.push_back(it->first);
	
	return exclusionVec;
}


//méthode getTps from randInitialisation
/*
int Solver::getTps(Intervention intervention, int i) {
	vector<int> value = randInitialisation();
	return
}

// checker pour t (t + Delta(i,t) =< T + 1 )

bool Solver::checkt() {
	int tps = this->data.getTps();
	int T = this->data.getT();
	int Delta = this->data.getDelta();

	if (tps + Delta > T + 1)
		return false;
	return true;


}*/



