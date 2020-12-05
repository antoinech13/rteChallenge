#pragma once
#include "dataCollector.h"
#include "Intervention.h"
#include <map>
#include <string>

class ExclusionCheck
{
public:
	map<int, vector<int>> violatExclusions(vector<int> interventions);
	ExclusionCheck(dataCollector data);
	ExclusionCheck();

private:
	vector<pair<int, int>> getTDt(vector<int> interTime, vector<int> tabInter, vector<Intervention> interventions);
	vector<bool> testIfInSeason(vector<int> tInSeasons, vector<pair<int, int>> tDt);
	vector<int> getConflic(vector<int> exclusion, vector<bool> interIsInSeason, vector<pair<int, int>>  tDts, pair<int, int> tDt, int j);
	dataCollector data;

};

