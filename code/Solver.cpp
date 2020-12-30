#include "Solver.h"
#include "Intervention.h"
#include "ExclusionCheck.h"
#include "ScoreEvaluation.h"
#include <time.h>
#include <map>
#include <string>
#include <iterator>
#include <float.h>
#include <algorithm>

using namespace std;


map<int, vector<int >> Solver::getExclusionViolation() {
	return this->exclusionViolation;
}

vector<int> Solver::getTime() {
	return this->Time;
}

double Solver::getScore() {
	return this->score;
}



Solver::Solver(dataCollector data){
	this->data = data;
	this->Time = randInitialisation();
	vector<int> test = { 1,1,2 };
	this->checker = ExclusionCheck(data);
	this->s = ScoreEvaluation(data);
	this->t = TimeChecker(data, this->Time);
	this->w = WorkloadCheck(data);
	this->exclusionViolation = checker.violatExclusions(this->Time);
	this->score = DBL_MAX;
	cout << "nnnnnnnnnnnnnniiiiiiiiikkkkkk: " << this->score << '\n';
	cout << "Time \n";
	for (int i = 0; i < this->Time.size(); i++)
		cout << this->Time[i] << " ";
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
	/*
	cout << "exclusion \n";
	for (int i = 0; i < exclusion.size(); i++)
		cout << exclusion[i] << " ";
	cout << '\n';
	cout << "wrokload \n";
	for (int i = 0; i < workload.size(); i++)
		cout << workload[i] << " ";
	cout << '\n';
	cout << "time \n";
	for (int i = 0; i < tme.size(); i++)
		cout << tme[i] << " ";
	cout << '\n';

	cout << "violation \n";
	for (int i = 0; i < violation.size(); i++)
		cout << violation[i] << " ";
	cout << '\n';*/



	return violation;
}

void Solver::move(double timeStart) {
	
	vector<Intervention> interventions = this->data.getInterventions();
	vector<int> Time, newTime;
	float cpTime = this->data.getComputationalTime() * 60;
	
	for (int i = 0; i < this->Time.size(); i++) {
		newTime.push_back(this->Time[i]);
		Time.push_back(this->Time[i]);
	}

	vector<int> violation = estimateViolation(this->Time);
	vector<int> newViolation;
	int idx, cpt=0;
	double score;
	
	while((clock() - timeStart) / CLOCKS_PER_SEC < cpTime) {

		srand(time(0));
		if (violation.size() > 0)
			idx = rand() % violation.size();
		else
			idx = rand() % Time.size();

		srand(time(0));

		//cout << "idx: " << idx << '\n';
		if (violation.size() > 0)
			newTime[violation[idx]] = rand() % interventions[violation[idx]].getTmax() + 1;
		else
			newTime[idx] = rand() % interventions[idx].getTmax() + 1;

		
		/*cout << "Time \n";
		for (int i = 0; i < Time.size(); i++) 
			cout << Time[i] << " ";
	
		cout << '\n';
		cout << "new Time \n";
		for (int i = 0; i < newTime.size(); i++)
			cout << newTime[i] << " ";
		cout << '\n';*/
		


		newViolation = estimateViolation(newTime);
		
		/*cout << "violation\n";
		for (int i = 0; i < violation.size(); i++)
			cout << violation[i] << " ";
		cout << '\n';
		cout << "newviolation\n";
		for (int i = 0; i < newViolation.size(); i++)
			cout << newViolation[i] << " ";
		cout << '\n';
		*/


		Time = newTime;
		violation = newViolation;
		


		if (violation.size() == 0) {
			score = this->s.extractScenarioFinal(Time);
			cpt++;
			//cout << "cpt: " << cpt << '\n';
			//cout << "score: " << this->score << " newScore" << score << '\n';
			if (score < this->score) {
				this->Time = Time;
				this->score = score;
				
			}
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





