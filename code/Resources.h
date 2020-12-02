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
	vector<pair<int, map<string, vector<int>>>> getData();

private:
	
	vector<pair<int, map<string, vector<int>>>> data;
	vector<pair<int, map<string, vector<int>>>> extractData(string vFile);
	map<string, vector<int>> extractMap(string vFile);
};

