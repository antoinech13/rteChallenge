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
//#include <time.h>

using namespace std;

class dataCollector
{

public:
	int getT();
	vector<double> getScenarioNumber();
	float getQuantile();
	float getAlpha();
	float getComputationalTime();
	vector<Intervention> getInterventions();
	vector<pair<int, map<string, vector<double>>>> getResources();
	vector<pair<string, vector<double>>> getExclusions();
	map<string, vector<double>> getSeasons();
	int IdToIdx(int id);

	dataCollector();
	dataCollector(FILE * I);
	dataCollector(FILE* vFile, int timeC);


private:
	int T;
	vector<double> scenariosNumber;
	float quantile;
	float alpha;
	//clock_t cpTime;
	float cpTime;
	vector<Intervention> interventions;
	vector<Intervention>  buildInterventions(string vFile);
	vector<pair<int, map<string, vector<double>>>> resources;
	vector<pair<string, vector<double>>> exclusions;
	map<string, vector<double>> seasons;

};
