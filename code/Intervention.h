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
	double getInterId();
	string getName();
	vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> getWorkload();
	vector<vector<pair<int, vector<double>>>> getRisk();
	void setId(double id);
	void setName(string name);
	Intervention(string vFile);

private:
	int tmax;
	vector<double> Delta;
	double interId;
	string name;

	vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> workload;
	vector<pair<int, vector<pair<int, vector<pair<int, double>>>>>> extractWorkLoad(string vFile);
	vector<pair<int, vector<pair<int, double>>>> extractC(string vFile);
	vector<pair<int, double>> extractTstep(string vFile);
	
	vector<vector<pair<int, vector<double>>>> risk;
	vector<vector<pair<int, vector<double>>>> extractRisk(string vFile);
	vector<pair<int, vector<double>>> extractTr(string vFile);
};

