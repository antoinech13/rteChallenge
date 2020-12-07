#pragma once
#include "dataCollector.h"
#include "Intervention.h"
#include "WorkloadCheck.h"
#include <map>
#include <string>



class Solver
{

public:
	Solver(dataCollector data);
	map<int, vector<int >> getExclusionViolation();
	vector<int> getInitTime();
	vector<vector<int>> getScore();
	int checkWorload(vector<int>);


private:
	dataCollector data;
	vector<int> randInitialisation();
	map<int, vector<int>> exclusionViolation;
	vector<int> initTime;
	vector<vector<int>> Score;
	WorkloadCheck w;
};
