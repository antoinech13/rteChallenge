#include "Solver.h"
#include "Intervention.h"
#include "ExclusionCheck.h"
#include "ScoreEvaluation.h"
#include <time.h>
#include <map>
#include <string>



Solver::Solver(dataCollector data){
	this->data = data;
	ExclusionCheck checker(data);
	this->nik = randInitialisation();
	this->a = checker.violatExclusions(nik);
	ScoreEvaluation s(data, nik);
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
//"yolo"


