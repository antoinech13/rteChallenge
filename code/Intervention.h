#pragma once
#include <vector>
#include <map>
#include <utility>

using namespace std;
class Intervention
{

public:
	int getTmax();
	vector<double> getDelta();
	vector<pair<int, vector<vector<pair<int, double>>>>> getWorkload();
	vector<vector<pair<int, vector<double>>>> getRisk();
	Intervention(string vFile);

private:
	int tmax;
	vector<double> Delta;

	vector<pair<int, vector<vector<pair<int, double>>>>> workload;
	vector<pair<int, vector<vector<pair<int, double>>>>> extractWorkLoad(string vFile);
	vector<vector<pair<int, double>>> extractC(string vFile);
	vector<pair<int, double>> extractTstep(string vFile);
	
	vector<vector<pair<int, vector<double>>>> risk;
	vector<vector<pair<int, vector<double>>>> extractRisk(string vFile);
	vector<pair<int, vector<double>>> extractTr(string vFile);
};

