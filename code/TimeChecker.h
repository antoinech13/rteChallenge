#include "dataCollector.h"
#include "Intervention.h"


class TimeChecker {



	public:
	TimeChecker(dataCollector data, vector<int> time);

  




	private:
		vector<int> getViolations();
		vector<Intervention> interventions;
		vector<int> times;
		int T;
};