#include "dataCollector.h"
#include "Resources.h"


class WorkloadCheck
{

public:
	WorkloadCheck(dataCollector data);
	int workloadCheck(vector<int> soluce);
	int workloadCheckMax(vector<int> soluce);
	int workloadCheckMin(int score);
	vector<int> getInterventionBad();
	vector<vector<int>> getTimeBad();


private:
	vector<vector<int>>arrayWorkload;
	vector<pair<int, map<string, vector<int>>>> ressouces;
	vector<Intervention> interventions;
	vector<int> interventionBad;
	vector<vector<int>>timeBad;
};