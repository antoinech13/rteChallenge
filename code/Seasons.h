#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

class Seasons
{
public:
	map<string, vector<int>>  getData();
	Seasons(string vFile);

private:
	map<string, vector<int>>  data;
	map<string, vector<int>>  extractData(string vFile);
};

