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

	vector<pair<string, vector<int>>> exclusions = this->data.getExclusions();
	map<string, vector<int>> seasons = this->data.getSeasons();
	vector<Intervention> interventions = this->data.getInterventions();

	vector<int> exclusion, val, tInSeasons;
	string season;
	vector<pair<int, int>> tDt;
	vector<bool> interIsInSeason;

	map<int, vector<int>> result;


	// chack every exclusions rules
	for (int i = 0; i < exclusions.size(); i++) {

		exclusion = exclusions[i].second;
		season = exclusions[i].first;
		tDt = getTDt(interventionPosition, exclusion, interventions);
		tInSeasons = seasons[season];
		interIsInSeason = testIfInSeason(tInSeasons, tDt);

		for (int j = 0; j < exclusion.size(); j++) {
			if (interIsInSeason[i]) {
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

vector<int> ExclusionCheck::getConflic(vector<int> exclusion, vector<bool> interIsInSeason, vector<pair<int, int>>  tDts, pair<int, int> tDt, int j) {
	vector<int> result;
	for (int i = 0; i < interIsInSeason.size(); i++) {
		if (interIsInSeason[i] && i != j && ((tDt.first < tDts[i].first && tDt.first + tDt.second >= tDts[i].first) || (tDt.first > tDts[i].first && tDts[i].second + tDts[i].first >= tDt.first) || tDt.first == tDts[i].first)) {
			result.push_back(exclusion[i]);
		}
	}
	return result;
}

vector<bool> ExclusionCheck::testIfInSeason(vector<int> tInSeasons, vector<pair<int, int>> tDt) {
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

vector<pair<int, int>> ExclusionCheck::getTDt(vector<int> interTime, vector<int> exclusion, vector<Intervention> interventions) {
	vector<pair<int, int>> result;
	int t;
	for (int j = 0; j < exclusion.size(); j++) {
		t = interTime[exclusion[j]];
		result.push_back(make_pair(t, interventions[exclusion[j]].getDelta()[t - 1]));
	}
	return result;
}