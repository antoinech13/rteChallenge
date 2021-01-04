#include "dataCollector.h"
#include "Resources.h"


class WorkloadCheck
{
	
public:
	WorkloadCheck(dataCollector data);
	WorkloadCheck();
	void getWorkloadCheck(vector<int> soluce);
	void workloadCheckMax(vector<int> soluce);
	void workloadCheckMin();
	vector<int> getInterventionBad();
	vector<vector<int>> getTimeBad();
	vector<vector<int>> getArrayWorkload();
	int timeToIdx(int time, vector<pair<int, vector<pair<int, double>>>> workloadTime);
	int startingTimeToIdx(int time, vector<pair<int, double>> workloadTime);


private:
	int T;
	vector<vector<int>>arrayWorkload;
	vector<pair<int, map<string, vector<double>>>> ressouces;
	vector<Intervention> interventions;
	vector<int> interventionBad;
	vector<vector<int>>timeBad;
	
};