#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

class Seasons
{
public:
	map<string, vector<double>>  getData();
	Seasons(string vFile);

private:
	map<string, vector<double>>  data;
	map<string, vector<double>>  extractData(string vFile);
};

