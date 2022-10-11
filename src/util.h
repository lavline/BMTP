#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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

#include <fstream>
#include <sstream>
#include "data_structure.h"
#include "generator.h"
#include "chrono_time.h"
#include "printer.h"
#include <cmath>
#include <vector>
#include <cstring>
using namespace std;
									 

class Util {
public:
	//static void Check(generator gen, string filename);

	static void Check(intervalGenerator gen, string filename);

	static double Average(const vector<double> &a);

	static std::string RemoveBlank(std::string str);

	static std::string RemoveLastZero(std::string str);

	static void WriteData(string fileName, string text);

	static string Double2String(double value);

	static double String2Double(string str);

	static string Int2String(int value);

	static int String2Int(string str);

	static bool CheckExist(int value, vector<int> array);

	static bool IsPrime(int number);

	static int Fac(int n);

	static double N2U(double value, double mean, double var);     //normal distribution to uniform distribution
	static double E2U(double value, double mean);     //exponential distribution to uniform distribution
	static double P2U(double value, double mean, double scale);     //pareto distribution to uniform distribution

	static void
	OutputResult(string filename, int ope, int att, int ite, int subDis, int pubDis, double wid, int sub, int pub,
				 double zip, double total, double avg, double max, double min, double std, int matchNo,
				 string matchList);

	static void
	OutputStatistics(string filename, int pubs, int subs, int atts, int comAtts, int cons, double wid, int subDis,
					 int pubDis, double zipf, int testId, vector<int> matSubList, vector<double> matTimeList,
					 vector<vector<int> > priList, vector<vector<double> > detTimeList, int freq[]);

	static vector<double> ComputeDoubleStatistics(vector<double> data);

	static vector<double> ComputeIntStatistics(vector<int> data);

};

#endif
