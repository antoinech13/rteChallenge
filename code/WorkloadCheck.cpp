#include "WorkloadCheck.h"
#include "dataCollector.h"
#include "Resources.h"


WorkloadCheck::WorkloadCheck(dataCollector data) {
	this->interventions = data.getInterventions();
	this->ressouces = data.getResources();
	vector<int> tab(data.getT(), 0.0);
	this->arrayWorkload = vector<vector<int>>(ressouces.size(), vector<int>(data.getT()));
	//vector<pair<string, map<string, vector<int>>>>
};


int WorkloadCheck::workloadCheckMax(vector<int> soluce) {
	int score = 0;
	for (int indice = 0; indice < soluce.size(); indice++) {
		int jour = soluce[indice];
		int delta = interventions[indice].getDelta()[jour - 1];
		vector<pair<int, vector<vector<pair<int, int>>>>> workload = interventions[indice].getWorkload();
		for (int nbjour = 0; nbjour < delta; nbjour++)
			for (int c = 0; c < workload.size(); c++) {
				int nomC = workload[c].first;
				arrayWorkload[nomC][jour - 1] += workload[c].second[jour - 1 + nbjour][jour - 1].second;

				if (arrayWorkload[nomC][jour - 1] > ressouces[nomC].second["max"][jour - 1]) {
					score++;
					interventionBad.push_back(indice);
				}
			}
	}
	return score;
}


int WorkloadCheck::workloadCheckMin(int score) {
	for (int ligne = 0; ligne < arrayWorkload.size(); ligne++)
		for (int colonne = 0; colonne < arrayWorkload[ligne].size(); colonne++)
			if (arrayWorkload[ligne][colonne] < ressouces[ligne].second["max"][colonne]) {
				score++;
				timeBad[ligne].push_back(colonne + 1);
			}
	return score;
}



int WorkloadCheck::workloadCheck(vector<int> soluce) {
	int score = workloadCheckMax(soluce);
	score += workloadCheckMin(score);

	return score;
}