#define _CRT_SECURE_NO_DEPRECATE
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
#include <fstream>

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
	const char* path = "SoluceTime.txt";
	FILE* exemple;


	vector<int> sq;
	string d = "";
	exemple = fopen(path, "r");
	char c;
	
	do {
		c = fgetc(exemple);
		if (c != ' ' && c != '\n' && c != '\t')
			d.push_back(c);
		if(c == '\n')
		{
			sq.push_back(stoi(d));
			d = "";
		}
		
	} while (c != EOF);


	this->data = data;
	this->Time = randInitialisation();
	vector<int> test = { 1,1,2 };
	this->checker = ExclusionCheck(data);
	this->s = ScoreEvaluation(data);
	this->t = TimeChecker(data, this->Time);
	this->w = WorkloadCheck(data);
	this->exclusionViolation = checker.violatExclusions(this->Time);
	this->score = DBL_MAX;
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
	*/


	return violation;
}

vector<int> Solver::findWorkload(int idx)
{
	vector<int> loadMultiple;
	vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> workMultiple = this->data.getInterventions()[idx].getWorkload();
	for (int indice = 0; indice < workMultiple.size(); indice++)
	{
		loadMultiple.push_back(workMultiple[indice].first);
	}
	return loadMultiple;
}

vector<int> Solver::chekFindWork(int idx, vector<vector<int>> timeBad)
{
	vector<int> timeBadWorkMin;
	vector<int>loadMultiple = findWorkload(idx);
	for (int work : loadMultiple)
	{
		if (timeBad[work].size() != 0)
		{
			timeBadWorkMin.push_back(work);
		}
	}
	return timeBadWorkMin;
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
	vector<vector<int>> timeBad = this->w.getTimeBad();

	int idx, inter, cpt=0, cpt2 = 0, cpt3=0;
	double score;
	
	while((clock() - timeStart) / CLOCKS_PER_SEC < cpTime) {

		srand(time(0));
		if (violation.size() > 1)
		{
			
			idx = rand() % violation.size();
			inter = this->data.IdToIdx(violation[idx]);
		}
		
		else if(violation.size() == 1)
		{
			if (cpt2 == 3) {
				cout << "cpt reinit\n";
				cpt2 = 0;
				cpt3 = 1;
				idx = rand() % Time.size();
				inter = idx;
			}
			else {

				cout << "cpt increment\n";
				cpt2++;
				cpt3 = 0;
				idx = rand() % violation.size();
				inter = this->data.IdToIdx(violation[idx]);
			}
		}

		else
		{
			idx = rand() % Time.size();
			inter = idx;
		}

		srand(time(0));

		vector<int> timeBadWorkMin = chekFindWork(inter, timeBad);
		
		//cout << "idx: " << idx << '\n';
		if (violation.size() > 0) {
			if (timeBadWorkMin.size() > 0)
			{
				cout << "jen est marre: " << this->data.IdToIdx(violation[idx]) << " intervention id:  " << this->data.getInterventions()[this->data.IdToIdx(violation[idx])].getInterId() << '\n';
				newTime[this->data.IdToIdx(violation[idx])] = timeBadWorkMin[rand() % timeBadWorkMin.size()];
			}
			else if (cpt3 == 1)
			{
				cout << "jen est marre: " << idx << " intervention id:  " << this->data.getInterventions()[idx].getInterId() << '\n';
				newTime[idx] = rand() % interventions[idx].getTmax() + 1;
			}
			else
			{
				cout << "jen est marre: " <<this->data.IdToIdx(violation[idx]) << " intervention id:  "<< this->data.getInterventions()[this->data.IdToIdx(violation[idx])].getInterId()<<'\n';
				newTime[this->data.IdToIdx(violation[idx])] = rand() % interventions[this->data.IdToIdx(violation[idx])].getTmax() + 1;
			}
			
		}
		else if (timeBadWorkMin.size() > 0)
		{
			newTime[idx] = timeBadWorkMin[rand() % timeBadWorkMin.size()];
		}
		else
			newTime[idx] = rand() % interventions[idx].getTmax() + 1;

		
		cout << "Time \n";
		for (int i = 0; i < Time.size(); i++) 
			cout << Time[i] << " ";
	
		cout << '\n';
		cout << "new Time \n";
		for (int i = 0; i < newTime.size(); i++)
			cout << newTime[i] << " ";
		cout << '\n';
		


		newViolation = estimateViolation(newTime);
		

		/*
		if (newViolation.size() == 0)
		{
			cout << "�criture solution\n";
			ofstream monFlux("SoluceTime.txt");

			if (monFlux)
			{
				for (int intere = 0; intere < newTime.size(); intere++)
				{
					monFlux << newTime[intere] << " " << endl;
				}
			}
			else
			{
				cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
			}

			monFlux.close();
		}*/
		
		cout << "violation\n";
		for (int i = 0; i < violation.size(); i++)
			cout << violation[i] << " ";
		cout << '\n';
		cout << "newviolation\n";
		for (int i = 0; i < newViolation.size(); i++)
			cout << newViolation[i] << " ";
		cout << '\n';
		
		

		Time = newTime;
		violation = newViolation;
		timeBad = this->w.getTimeBad();
		

		
		if (violation.size() == 0 && timeBad.size() == 1 && timeBad[0].size() == 0) 
		{
			cout << "score coputation: \n";
			score = this->s.extractScenarioFinal(Time);
			cpt++;
			cout << "cpt: " << cpt << '\n';
			cout << "score: " << this->score << " newScore" << score << '\n';
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





