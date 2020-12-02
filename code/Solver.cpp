#include "Solver.h"
#include "Intervention.h"
#include <time.h>
#include <map>
#include <string>



Solver::Solver(dataCollector data){
	this->data = data;
	map<string, int> nik = randInitialisation();
}

vector<int> Solver::randInitialisation() {
	vector<vector<int>> value;
	vector<Intervention> interventions = this->data.getInterventions();
	srand(time(0));

	for (int i = 0; i < interventions.size(); i++) {
		value[interventions[i]] = rand() % it->second.getTmax() + 1;
		cout << it -> first << " " << it -> second.getTmax() << " " << value[it -> first] << '\n';
	}
	return value;
}


map<string, vector<string>> Solver::violatExclusion(map<string, int> interventionPosition) {

	vector<pair<string, vector<string>>> exclusions = this->data.getExclusions();
	vector<pair<string, vector<int>>> saisons = this->data.getSeasons();
	vector<Intervention> interventions = this->data.getInterventions();
	
	vector<string> exclusion;
	string season;
	int t;
	int dt;

    // chack every exclusions rules
	for (int i = 0; i < exclusions.size(); i++) { 

		exclusion = exclusions[i].second;
		season = exclusion[exclusion.size() - 1];

		//check one exclusion rules
		for (int j = 0; j < exclusion.size() - 1; j++) {
			t = interventionPosition[exclusion[i]];
			dt = interventions[exclusion[j]].getDelta()[;

		}

	}
	

}