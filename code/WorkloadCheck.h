#include "dataCollector.h"
#include "Resources.h"


class WorkloadCheck
{

public:
	WorkloadCheck(dataCollector data);
	int workloadCheck(vector<int> soluce);

private:
	vector<vector<int>>arrayWorkload;
	vector<pair<string, map<string, vector<int>>>> ressouces;
	vector<Intervention> interventions;
};
