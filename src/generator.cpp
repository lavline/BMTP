#include "generator.h"
#include <cmath>
#include <iostream>
#include<fstream>

using namespace std;

void intervalGenerator::InsertSubs(string file)
{
    ifstream infile(file, ios::in);
    if (!infile) {
        cout << "error opening source file." << endl;
        return;
    }
    int tmp;
    infile >> tmp >> atts >> cons >> m >> valDom >> attDis >> valDis >> alpha >> width;
    subList.resize(subs);
    for (auto &sub:subList) {
        infile >> sub.id;
        infile >> sub.size;
        sub.constraints.resize(sub.size);
        for (auto &pred:sub.constraints) {
            infile >> pred.att;
            infile >> pred.lowValue;
            infile >> pred.highValue;
        }
    }
    infile.close();
}

void intervalGenerator::InsertPubs(string file)
{
    ifstream infile(file, ios::in);
    if (!infile) {
        cout << "error opening source file." << endl;
        return;
    }
    int tmp;
    infile >> tmp >> atts >> tmp >> m >> valDom >> attDis >> valDis >> alpha;
    pubList.resize(pubs);
    for (auto &pub : pubList) {
        infile >> pub.size;
        pub.pairs.resize(pub.size);
        for (auto &pred : pub.pairs) {
            infile >> pred.att;
            infile >> pred.value;
        }
    }
    infile.close();
}