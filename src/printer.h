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

#ifndef _PRINTER_H
#define _PRINTER_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "data_structure.h"
#include "util.h"
#include <vector>

using namespace std;

class Printer {

public:

	static string PrintParameters(int argc, char *argv[]);

	//static void PrintProgress (string name, int num, int unit, int index);

	static string FormatStatistics(vector<double> valueList);

	static string PrintMatchSubStatistics(vector<int> matchSubList);

	static string PrintTimeStatistics(vector<double> matchTimeList);

	static string PrintFileName(string method);

	static void SaveResults(string fileName, vector<double> insertTimeList, vector<double> matchTimeList,
							vector<int> matchSubList, int subs, int atts, int cons, int m, int attDis, int valDis,
							double alpha);

	//static void PrintSubscription (Sub sub, bool showDetail=false);
	//static void PrintPublication (Pub pub);
};

#endif
