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

int WorkloadCheck::workloadCheck(vector<int> soluce) {

	for (int indice = 0; indice < soluce.size(); indice++) {
		int jour = soluce[indice];
		int delta = interventions[indice].getDelta()[jour - 1];
		vector<pair<int, vector<vector<pair<int, int>>>>> workload = interventions[indice].getWorkload();
		for (int nbjour = 0; nbjour < delta; nbjour++) {
			jour - 1 + nbjour;

		}



	}


}
