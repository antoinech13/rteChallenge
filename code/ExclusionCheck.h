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
	vector<pair<int, double>> getTDt(vector<int> interTime, vector<double> tabInter, vector<Intervention> interventions);
	vector<bool> testIfInSeason(vector<double> tInSeasons, vector<pair<int, double>> tDt);
	vector<int> getConflic(vector<double> exclusion, vector<bool> interIsInSeason, vector<pair<int, double>>  tDts, pair<int, double> tDt, int j);
	dataCollector data;

};

