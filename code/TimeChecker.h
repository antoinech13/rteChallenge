#include "dataCollector.h"
#include "Intervention.h"


class TimeChecker{



	public:

		TimeChecker(dataCollector data, vector<int> time);
		TimeChecker();

		vector<int> getViolations();
  

	private:
	
		vector<Intervention> interventions;
		vector<int> times;
		int T;
};