#pragma once
#include <vector>
#include <map>
#include <utility>
#include <string>

using namespace std;

class Exclusions
{
public:
	vector<pair<string, vector<string>>> getData();
	Exclusions(string vFile);

private:
	vector<pair<string, vector<string>>> data; 
	vector<pair<string, vector<string>>> extractData(string vFile);

};

