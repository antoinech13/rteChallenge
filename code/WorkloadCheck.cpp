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

void WorkloadCheck::workloadCheckMax(vector<int> soluce) {
	int jour, delta, delaisjour, nomC, timeIdx, startingTime;
	
	for (int indice = 0; indice < soluce.size(); indice++) {
		jour = soluce[indice] - 1;
		delta = this->interventions[indice].getDelta()[jour];
		vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> workload = this->interventions[indice].getWorkload();
		for (int nbjour = 0; nbjour < delta; nbjour++) {
			for (int c = 0; c < workload.size(); c++) {
				int nomC = workload[c].first;
				int delaisjour = jour + nbjour;
				arrayWorkload[nomC][delaisjour] += workload[c].second[delaisjour].second[jour].second;
	
				if (arrayWorkload[nomC][delaisjour] > this->ressouces[nomC].second["max"][delaisjour]) {
					
					this->interventionBad.push_back(this->interventions[indice].getInterId());
				}
			}
		}
	}
}

void WorkloadCheck::workloadCheckMin() {
	for (int ligne = 0; ligne < arrayWorkload.size(); ligne++) {
		vector<int> lim;
		for (int colonne = 0; colonne < arrayWorkload[ligne].size(); colonne++) {
			if (arrayWorkload[ligne][colonne] < ressouces[ligne].second["min"][colonne]) {

				lim.push_back(colonne + 1);

			}
		}
		this->timeBad.push_back(lim);
	}
}


void WorkloadCheck::getWorkloadCheck(vector<int> soluce) {
	this->interventionBad.clear();
	this->arrayWorkload = vector<vector<int>>(ressouces.size(), vector<int>(this->T));
	workloadCheckMax(soluce);
	this->timeBad.clear();
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
