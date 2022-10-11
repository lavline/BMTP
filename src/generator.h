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


#ifndef _GENERATOR_H
#define _GENERATOR_H
#include "data_structure.h"

class intervalGenerator
{
public:
    vector<IntervalSub> subList;
    vector<Pub> pubList;
    int subs, pubs, atts, cons, m, attDis, valDis, valDom;
    double alpha, width;

    intervalGenerator(int subs, int pubs, int atts, int cons, int m, int attDis, int valDis, int valDom, double alpha,
        double width) : subs(subs), pubs(pubs), atts(atts), cons(cons), m(m), attDis(attDis), valDis(valDis), valDom(valDom),
        alpha(alpha), width(width)
    {
    }
    intervalGenerator(int subs, int pubs):subs(subs), pubs(pubs) {};

    void InsertSubs(string file);
    void InsertPubs(string file);
};

#endif
