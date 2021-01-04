#include "TimeChecker.h"
#include "dataCollector.h"
#include <vector>



TimeChecker::TimeChecker(dataCollector data, vector<int> time) {
	this->T = data.getT();
	this->interventions = data.getInterventions();
	this->times = time;

}

TimeChecker::TimeChecker(){}

vector<int> TimeChecker::getViolations() {
	vector<int> values;
	for(int i = 0; i < this->interventions.size(); i++) {
		if (this->times[i] + this->interventions[i].getDelta()[this->times[i]-1] - 1 > this->T) 
			values.push_back(this->interventions[i].getInterId());
	}
	return values;

}


 


