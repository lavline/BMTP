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
