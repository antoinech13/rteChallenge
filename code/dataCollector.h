#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>
#include <iostream>
#include "Intervention.h"
#include "Resources.h"
#include "Seasons.h"
#include "Exclusions.h"

using namespace std;

class dataCollector
{

public:
	int getT();
	vector<int> getScenarioNumber();
	float getQuantile();
	float getAlpha();
	vector<pair<string, Intervention>> getInterventions();
	vector<pair<string, map<string, vector<int>>>> getResources();
	vector<pair<string, vector<string>>> getExclusions();
	vector<pair<string, vector<int>>> getSeasons();

	dataCollector();
	dataCollector(FILE * I);


private:
	int T;
	vector<int> scenariosNumber;
	float quantile;
	float alpha;
	vector<pair<string,Intervention>> interventions;
	vector<pair<string, Intervention>>  buildInterventions(string vFile);
	vector<pair<string, map<string, vector<int>>>> resources;
	vector<pair<string, vector<string>>> exclusions;
	vector<pair<string, vector<int>>> seasons;

};
