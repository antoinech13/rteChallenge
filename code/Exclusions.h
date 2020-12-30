#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

class Exclusions
{
public:
	vector<pair<string, vector<double>>> getData();
	Exclusions(string vFile);

private:
	vector<pair<string, vector<double>>> data; 
	vector<pair<string, vector<double>>> extractData(string vFile);

};

