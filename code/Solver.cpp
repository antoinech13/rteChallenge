#include "Solver.h"
#include "Intervention.h"
#include "ExclusionCheck.h"
#include "ScoreEvaluation.h"
#include <time.h>
#include <map>
#include <string>


map<int, vector<int >> Solver::getExclusionViolation() {
	return this->exclusionViolation;
}

vector<int> Solver::getInitTime() {
	return this->initTime;
}

double Solver::getObj1() {
	return this->obj1;
}

Solver::Solver(dataCollector data){
	this->data = data;
	ExclusionCheck checker(data);
	this->initTime = randInitialisation();
	this->exclusionViolation = checker.violatExclusions(initTime);
	vector<int> test= { 1,1,2 };
	ScoreEvaluation s(data, test);
	this->obj1 = s.getEvalScenario();
	this->w = WorkloadCheck (data);
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
	int score = this->w.getWorkloadCheck(this->initTime);
	return score;
}

map<int, vector<int>> Solver::scoreExclusion() {
	return this->exclusionViolation;

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



