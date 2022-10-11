/*
 *	MIT License
 *
 *	Copyright(c) 2022 ShangHai Jiao Tong Univiersity CIT Laboratory.
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this softwareand associated documentation files(the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions :
 *
 *	The above copyright noticeand this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

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