#pragma once
#include <vector>
#include <map>
#include <utility>

using namespace std;
class Intervention
{

public:
	int getTmax();
	vector<int> getDelta();
	vector<vector<vector<pair<int, int>>>> getWorkload();
	vector<vector<pair<int, vector<int>>>> getRisk();
	Intervention(string vFile);

private:
	int tmax;
	vector<int> Delta;

	vector<vector<vector<pair<int, int>>>> workload;
	vector<pair<int, vector<vector<pair<int, int>>>>> extractWorkLoad(string vFile);
	vector<vector<pair<int, int>>> extractC(string vFile);
	vector<pair<int, int>> extractTstep(string vFile);
	
	vector<vector<pair<int, vector<int>>>> risk;
	vector<vector<pair<int, vector<int>>>> extractRisk(string vFile);
	vector<pair<int, vector<int>>> extractTr(string vFile);
};

