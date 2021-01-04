#include "ExclusionCheck.h"
#include "dataCollector.h"
#include "Intervention.h"
#include <map>
#include <string>



ExclusionCheck::ExclusionCheck(dataCollector data) {
	this->data = data;
}

ExclusionCheck::ExclusionCheck(){}

map<int, vector<int>> ExclusionCheck::violatExclusions(vector<int> interventionPosition) {

	vector<pair<string, vector<double>>> exclusions = this->data.getExclusions();
	map<string, vector<double>> seasons = this->data.getSeasons();
	vector<Intervention> interventions = this->data.getInterventions();
	vector<int> val;
	vector<double> exclusion, tInSeasons;
	string season;
	vector<pair<int, double>> tDt;
	vector<bool> interIsInSeason;

	map<int, vector<int>> result;


	// check every exclusions rules
	for (int i = 0; i < exclusions.size(); i++) {

		exclusion = exclusions[i].second;
		season = exclusions[i].first;
		tDt = getTDt(interventionPosition, exclusion, interventions);
		tInSeasons = seasons[season];
		/*cout << "season: " << season << '\n';
		for (int w = 0; w < exclusion.size(); w++)
			cout << exclusion[w] << " ";
		cout << '\n';*/

		interIsInSeason = testIfInSeason(tInSeasons, tDt);

		/*cout << "interIsInSeason: " << '\n';
		for (int w = 0; w < interIsInSeason.size(); w++)
			cout << interIsInSeason[w] << " ";
		cout << '\n';
		cout << "exclusion size \n" << exclusion.size() << '\n';*/

		for (int j = 0; j < exclusion.size(); j++) {
			if (interIsInSeason[j]) {
				val = getConflic(exclusion, interIsInSeason, tDt, tDt[j], j);

			}
			if (val.size() != 0) {
				if (result.find(j) == result.end())
					result[exclusion[j]] = val;
				else
					result[exclusion[j]].insert(result[exclusion[j]].end(), val.begin(), val.end());

			}

		}
	}

	return result;
}

vector<int> ExclusionCheck::getConflic(vector<double> exclusion, vector<bool> interIsInSeason, vector<pair<int, double>>  tDts, pair<int, double> tDt, int j) {
	vector<int> result;
	for (int i = 0; i < interIsInSeason.size(); i++) {
		if (interIsInSeason[i] && i != j && ((tDt.first < tDts[i].first && tDt.first + tDt.second - 1 >= tDts[i].first) || (tDt.first > tDts[i].first && tDts[i].second + tDts[i].first - 1 >= tDt.first) || tDt.first == tDts[i].first)) {
			result.push_back(exclusion[i]);
		}
	}
	return result;
}

vector<bool> ExclusionCheck::testIfInSeason(vector<double> tInSeasons, vector<pair<int, double>> tDt) {
	vector<bool> in;

	for (int i = 0; i < tDt.size(); i++) {
		if (tInSeasons.size() == 0)
			in.push_back(false);

		else if (tDt[i].first >= tInSeasons[0] && tDt[i].first <= tInSeasons[tInSeasons.size() - 1]) {
			in.push_back(true);
		}
		else {
			in.push_back(false);
		}
	}
	return in;
}


vector<pair<int, double>> ExclusionCheck::getTDt(vector<int> interTime, vector<double> exclusion, vector<Intervention> interventions) {
	vector<pair<int, double>> result;
	int t;
	int idx;
	for (int j = 0; j < exclusion.size(); j++) {
		idx = this->data.IdToIdx(exclusion[j]);
		t = interTime[idx];
		result.push_back(make_pair(t, interventions[idx].getDelta()[t - 1]));
	}
	return result;
}