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
	vector<Intervention> getInterventions();
	vector<pair<int, map<string, vector<int>>>> getResources();
	vector<pair<string, vector<int>>> getExclusions();
	map<string, vector<int>> getSeasons();

	dataCollector();
	dataCollector(FILE * I);


private:
	int T;
	vector<int> scenariosNumber;
	float quantile;
	float alpha;
	vector<Intervention> interventions;
	vector<Intervention>  buildInterventions(string vFile);
	vector<pair<int, map<string, vector<int>>>> resources;
	vector<pair<string, vector<int>>> exclusions;
	map<string, vector<int>> seasons;

};
