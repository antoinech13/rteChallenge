#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <list>
#include <vector>
#include <utility>
#include "Parser.h"
#include "Intervention.h"
#include "dataCollector.h"
#include "Solver.h"
#include "WorkloadCheck.h"


using namespace std;

int main() {

    const char* path = "example2.json";
    FILE* exemple1;
    errno_t err;
    vector<int> c;
    err = fopen_s(&exemple1, path, "r");

    if (err != 0) {
        printf("cannot open file\n");
        return 0;
    }
    else {
        printf("open file\n");
    }

    

    dataCollector D(exemple1);
    Solver s(D);

    vector<int> nik = s.getInitTime();
    
    vector<vector<int>> score = s.getScore();

    for (int i = 0; i < score.size(); i++) {
        for (int j = 0; j < score[i].size(); j++)
            cout << score[i][j] << " ";
        cout << '\n';
    }

}



