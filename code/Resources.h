#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

class Resources
{

public:
	Resources(string vFile);
	vector<pair<int, map<string, vector<double>>>> getData();

private:
	
	vector<pair<int, map<string, vector<double>>>> data;
	vector<pair<int, map<string, vector<double>>>> extractData(string vFile);
	map<string, vector<double>> extractMap(string vFile);
};

