#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

class Exclusions
{
public:
	vector<pair<string, vector<int>>> getData();
	Exclusions(string vFile);

private:
	vector<pair<string, vector<int>>> data; 
	vector<pair<string, vector<int>>> extractData(string vFile);

};

