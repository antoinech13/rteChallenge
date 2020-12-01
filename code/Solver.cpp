#include "Solver.h"
#include "Intervention.h"
#include<time.h>
#include <map>
#include <string>



Solver::Solver(dataCollector data){
	this->data = data;
	map<string, int> nik = randInitialisation();
}

map<string, int> Solver::randInitialisation() {
	map<string, int> value;
	vector<pair<string, Intervention>> interventions = this->data.getInterventions();
	srand(time(0));

	for (int i = 0; i < interventions.size(); i++) {
		value[interventions[i].first] = rand() % interventions[i].second.getTmax() + 1;
		cout << interventions[i].first << " " << interventions[i].second.getTmax() << " " << value[interventions[i].first] << '\n';
	}
	return value;
}


