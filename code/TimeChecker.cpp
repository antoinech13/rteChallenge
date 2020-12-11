#include "TimeChecker.h"
#include "dataCollector.h"
#include "Interventions.h"


TimeChecker::TimeChecker(dataCollector data) {
	this->interventions = data.getInterventions();
	this->deltas = data.getDelta();
	  

}

TimeChecker::TimeChecker() {}