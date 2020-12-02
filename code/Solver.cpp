#include "Solver.h"
#include "Intervention.h"
#include <time.h>
#include <map>
#include <string>



Solver::Solver(dataCollector data){
	this->data = data;
	vector<int> nik = randInitialisation();
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


map<int, vector<int>> Solver::violatExclusions(vector<int> interventionPosition) {

	vector<pair<string, vector<int>>> exclusions = this->data.getExclusions();
	map<string, vector<int>> seasons = this->data.getSeasons();
	vector<Intervention> interventions = this->data.getInterventions();
	
	vector<int> exclusion;
	string season;
	vector<pair<int, int>> tDt;
	vector<int> tInSeasons;
	vector<bool> interIsInSeason;
	

    // chack every exclusions rules
	for (int i = 0; i < exclusions.size(); i++) { 

		exclusion = exclusions[i].second;
		season = exclusions[i].first;
		tDt = getTDt(interventionPosition, exclusion, interventions);
		tInSeasons = seasons[season];
		interIsInSeason = testIfInSeason(tInSeasons, tDt);



	}

}

vector<int> Solver::getConflic(vector<bool> interIsInSeason, vector<int> exclusion, vector<pair<int, int>>  tDts, pair<int, int> tDt) {
	for (int i = 0; i < exclusion.size(); i++) {
		if(interIsInSeason[i] && tDt.first < tDts.first)

	}
}
	
vector<bool> Solver::testIfInSeason(vector<int> tInSeasons, vector<pair<int, int>> tDt) {
	vector<bool> in;

	for (int i = 0; i < tDt.size(); i++) {
		if (tDt[i].first >= tInSeasons[0] && tDt[i].first <= tInSeasons[tInSeasons.size() - 1]) {
			in.push_back(true);
		}
		else {
			in.push_back(false);
		}
	}
	return in;
}

vector<pair<int, int>> Solver::getTDt(vector<int> interTime, vector<int> tabInter, vector<Intervention> interventions) {
	vector<pair<int, int>> result;
	int t;
	for (int j = 0; j < tabInter.size() - 1; j++) {
		t = interTime[tabInter[j]];
		result.push_back(make_pair(t, interventions[tabInter[j]].getDelta()[t - 1]));
	}
	return result;
}

//méthode getTps from randInitialisation
  
int Solver::getTps(Intervention intervention, int i) {
	vector<vector<int>> value = this->data.randInitialisation();
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


}



