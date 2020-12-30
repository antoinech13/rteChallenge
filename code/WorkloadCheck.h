#include "dataCollector.h"
#include "Resources.h"


class WorkloadCheck
{
	
public:
	WorkloadCheck(dataCollector data);
	WorkloadCheck();
	int getWorkloadCheck(vector<int> soluce);
	int workloadCheckMax(vector<int> soluce);
	int workloadCheckMin(int score);
	vector<int> getInterventionBad();
	vector<vector<int>> getTimeBad();
	vector<vector<int>> getArrayWorkload();


private:
	int T;
	vector<vector<int>>arrayWorkload;
	vector<pair<int, map<string, vector<int>>>> ressouces;
	vector<Intervention> interventions;
	vector<int> interventionBad;
	vector<vector<int>>timeBad;

};