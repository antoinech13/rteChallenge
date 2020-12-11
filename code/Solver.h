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
	double getObj1();



private:
	dataCollector data;
	vector<int> randInitialisation();
	map<int, vector<int>> exclusionViolation;
	vector<int> initTime;
	double obj1;
	map<int, vector<int>> scoreExclusion();
	int scoreCheckWorload(vector<int>);
	WorkloadCheck w;
};
