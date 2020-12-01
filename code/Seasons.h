#pragma once
#include <vector>
#include <map>
#include <string>

using namespace std;

class Seasons
{
public:
	vector<pair<string, vector<int>>>  getData();
	Seasons(string vFile);

private:
	vector<pair<string, vector<int>>>  data;
	vector<pair<string, vector<int>>>  extractData(string vFile);
};

