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


using namespace std;

int main() {

    const char* path = "example1.json";
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


    cout << D.getAlpha()<< '\n';

    vector<int> nik = s.nik;
    map<int, vector<int>> a = s.a;

    for (int i = 0; i < nik.size(); i++)
        cout << nik[i]<< '\n';

    cout  <<'\n' << "map" << '\n';

    for (map<int, vector<int>>::iterator it = a.begin(); it != a.end(); ++it) {
        cout << it->first << " ";
        for (int i = 0; i < it->second.size(); i++)
            cout << it->second[i] << " ";
        cout << '\n';
    }


}



