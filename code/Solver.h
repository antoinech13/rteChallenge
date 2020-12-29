#pragma once
#include "dataCollector.h"
#include "Intervention.h"
#include "WorkloadCheck.h"
#include "ExclusionCheck.h"
#include "TimeChecker.h"
#include "ScoreEvaluation.h"
#include <map>
#include <string>



class Solver
{

public:
	Solver(dataCollector data);
	map<int, vector<int >> getExclusionViolation();
	vector<int> estimateViolation(vector<int> time);
	void move();
	vector<int> getTime();
	double getScore();



private:
	
	vector<int> randInitialisation();
	vector<int> exclusionTab(vector<int> time);
	map<int, vector<int>> exclusionViolation;
	vector<int> Time;
	vector<int> violation;
	double score;
	map<int, vector<int>> scoreExclusion();
	int scoreCheckWorload(vector<int>);
	
	
	WorkloadCheck w;
	ExclusionCheck checker;
	ScoreEvaluation s;
	TimeChecker t;
	dataCollector data;
};
