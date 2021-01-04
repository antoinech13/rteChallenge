#include "WorkloadCheck.h"
#include "dataCollector.h"
#include "Resources.h"


WorkloadCheck::WorkloadCheck(dataCollector data) {
	this->T = data.getT();
	this->interventions = data.getInterventions();
	this->ressouces = data.getResources();
	vector<int> tab(data.getT(), 0);
	
};

WorkloadCheck::WorkloadCheck() {}

int WorkloadCheck::workloadCheckMax(vector<int> soluce) {
	
	for (int indice = 0; indice < soluce.size(); indice++) {
		jour = soluce[indice] - 1;
		delta = this->interventions[indice].getDelta()[jour];
		vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> workload = this->interventions[indice].getWorkload();
		for (int nbjour = 0; nbjour < delta; nbjour++) {
			for (int c = 0; c < workload.size(); c++) {
				nomC = workload[c].first;
				delaisjour = jour + nbjour;
				//cout << "soluce: " << soluce[indice] << '\n';
				//cout << "delta: " << delta << '\n';
				//cout << "nomC: " << nomC << '\n';
				//cout << "delai: " << delaisjour << '\n';
				//cout << "size1: " << arrayWorkload.size() << " size2: " << arrayWorkload[0].size() << '\n';
				//cout << "test?: " << '\n';
				//cout << "Intervention ID: " << this->interventions[indice].getInterId() << '\n';
				timeIdx = timeToIdx(delaisjour + 1, workload[c].second);
				startingTime = startingTimeToIdx(jour + 1, workload[c].second[timeIdx].second);
				
				if(timeIdx != -1 && startingTime != -1)
					arrayWorkload[nomC][delaisjour] += workload[c].second[timeIdx].second[startingTime].second;
	
				if (arrayWorkload[nomC][delaisjour] > this->ressouces[nomC].second["max"][delaisjour]) {
					
					this->interventionBad.push_back(indice);
				}
			}
		}
	}
}

void WorkloadCheck::workloadCheckMin() {
	for (int ligne = 0; ligne < arrayWorkload.size(); ligne++) {
		vector<int> lim;
		for (int colonne = 0; colonne < arrayWorkload[ligne].size(); colonne++){
			if (arrayWorkload[ligne][colonne] < ressouces[ligne].second["min"][colonne]) {
			
		    	lim.push_back(colonne + 1);
	
			}
		}
		this->timeBad.push_back(lim);
	}
	return score;


void WorkloadCheck::getWorkloadCheck(vector<int> soluce) {
	this->interventionBad.clear();
	this->arrayWorkload = vector<vector<int>>(ressouces.size(), vector<int>(this->T));
	workloadCheckMax(soluce);
	workloadCheckMin();

}

vector<int>  WorkloadCheck::getInterventionBad() {
	return interventionBad;
}

vector<vector<int>> WorkloadCheck::getTimeBad() {
	return timeBad;
}

vector<vector<int>> WorkloadCheck::getArrayWorkload() {
	return arrayWorkload;
}

int WorkloadCheck::timeToIdx(int time, vector<pair<int, vector<pair<int, double>>>> workloadTime) {
	for (int i = 0; i < workloadTime.size(); i++)
		if (time == workloadTime[i].first)
			return i;
	//cout << "problem with WorkloadCheck: Time step not found! time: " << time << '\n';
	return -1;
}

int WorkloadCheck::startingTimeToIdx(int time, vector<pair<int, double>> workloadSTime) {
	for (int i = 0; i < workloadSTime.size(); i++)
		if (time == workloadSTime[i].first)
			return i;
	//cout << "problem with WorkloadCheck: Starting time step not found! time: " << time << '\n';
	return -1;
}