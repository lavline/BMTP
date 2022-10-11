#include <iostream>
#include "hr_tree.h"
using namespace std;
int main(int argc, char **argv)
{
    int totalSub;
    int subs;           // Number of subscriptions.
    int pubs;           // Number of publications.
    int atts;           // Total number of attributes, i.e. dimensions.
    int cons;           // Number of constraints(predicates) in one sub.
    int m;              // Number of constraints in one pub.
    int valDom;         // Cardinality of values.
    int attDis;         // The distribution of attributes in subs and pubs. 0:uniform distribution | 1:Zipf distribution
    int valDis;         // The distribution of values in subs and pubs. 0:uniform
    double alpha;       // Parameter for Zipf distribution.
    double width;       // Width of a predicate.
    int level;
    int cells;
    int max_buckets;
    int genRand;

    ifstream infile("paras.txt", ios::in);
    
    infile >> totalSub >> subs >> pubs >> atts >> cons >> m >> attDis >> valDis >> valDom;
    infile >> alpha >> width;
    infile >> level >> cells;
    infile >> max_buckets >> genRand;

    vector<double> insertTimeList;
    vector<double> deleteTimeList;
    vector<double> matchTimeList;
    vector<double> matchSubList;

    // Initiate generator
    intervalGenerator gen(subs, pubs);
    
    string dir;
    //infile >> dir;
    getline(infile, dir);
    getline(infile, dir);
    //cout << dir << endl;
    infile.close();

    string sname = dir + "sub-" + to_string(totalSub / 1000) + "K-" + to_string(atts) + "D-" + to_string(cons) + "A-" + to_string(attDis) + "Ad-"
        + to_string(valDis) + "Vd-" + to_string((int)(alpha * 10)) + "al-" + to_string((int)(width * 10)) + "W-" + to_string(genRand) + "R.txt";
    string pname = dir + "pub-" + to_string(atts) + "D-" + to_string(m) + "A-" + to_string(attDis) + "Ad-"
        + to_string(valDis) + "Vd-" + to_string((int)(alpha * 10)) + "al.txt";

    cout << sname << "\n" << pname << "\n";

    gen.InsertSubs(sname);
    gen.InsertPubs(pname);


    HRtree a(atts, level, cells, valDis, valDom, max_buckets);


    // insert
    cout << "insert start...\n";
    for (int i = 0; i < subs; i++)
    {
        Timer subStart;

        a.insert(gen.subList[i]);                       // Insert sub[i] into data structure.

        int64_t insertTime = subStart.elapsed_nano();   // Record inserting time in nanosecond.
        insertTimeList.push_back((double) insertTime / 1000000);
    }

    //a.cout_buck_size();
    double memCost = a.mem_size();
    cout << memCost << endl;
    cout << memCost / (double)(1 << 20) << "MB\n";

    // match
    cout << "match start...\n";
    for (int i = 0; i < pubs; i++)
    {
        int matchSubs = 0;                              // Record the number of matched subscriptions.
        Timer matchStart;

        a.match(gen.pubList[i], matchSubs, gen.subList);

        int64_t eventTime = matchStart.elapsed_nano();  // Record matching time in nanosecond.
        matchTimeList.push_back((double) eventTime / 1000000);
        matchSubList.push_back(matchSubs);
        //cout << "------\n" << matchSubs << endl;
    }

    //delete
    cout << "delete start...\n";
    for (int i = 0; i < 1; i++)
    {
        Timer delStart;

        a.delete_sub(gen.subList[i]);

        int64_t deleteTime = delStart.elapsed_nano();
        deleteTimeList.push_back((double)deleteTime / 1000000);
    }

    // output
    cout << "output start...\n";
    string outputFileName = "hr_tree.txt";
    string content = Util::Int2String(subs) + "\t" + Util::Double2String(Util::Average(insertTimeList)) + "\t" +
                     Util::Double2String(Util::Average(deleteTimeList)) + "\t" +
                     Util::Double2String(Util::Average(matchTimeList)) + "\t" +
                     Util::Double2String(Util::Average(matchSubList)) + "\t" +
                     Util::Double2String(Util::ComputeDoubleStatistics(matchTimeList)[1]) + "\t" +
                     Util::Double2String(Util::ComputeDoubleStatistics(matchTimeList)[2]) + "\t" +
                     Util::Double2String(Util::ComputeDoubleStatistics(matchTimeList)[3]);
    Util::WriteData(outputFileName.c_str(), content);


    // check
    //cout << "**********************************\n";
    //Util::Check(gen, "hr_tree");
    cout << "program complete\n";
    return 0;
}
