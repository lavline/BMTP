#ifndef _HRTREE_H_
#define _HRTREE_H_
#include "util.h"

using namespace std;

class HRtree {
    int total_cells, atts, mLevel, valDis, valDom, buckStep;
    const int MAX_BUCKS;
    //record the first and the last cell id in each level 
    vector<pair<int, int>> cells;
    //record the half of the width of cell in each level
    vector<double> cellStep;
    ofstream log;

    vector<vector<vector<vector<vector<Combo>>>>> buckets;
    vector<vector<int>>counter;
    //bool matched[MAX_SUBS];

    void insertToBucket(const vector<vector<int> > &mark, int bucketID, int level, IntervalSub& sub);
    void deleteInBucket(const vector<vector<int> >& mark, int bucketID, int level, IntervalSub& sub);

    void matchInBucket(const vector<vector<int> > &mark, int bucketID, int level, int &matchSubs,
                       const vector<IntervalSub> &subList, const Pub &pub, int &_mark, int &_subs);
    //bool match(const IntervalSub &sub, const Pub &pub);
public:
    HRtree(int atts, int level, int _cells, int valDis, int valDom, const int MAX_BUCKS) : atts(atts), mLevel(level), total_cells(_cells - 1),
                                                                    valDis(valDis), valDom(valDom), MAX_BUCKS(MAX_BUCKS)
    {
        log.open("match_log.txt", ios::app);
        if (!log) {
            cout << "error opening log file." << endl;
        }

        //initialize cell step
        cellStep.push_back(1.0 / (double)_cells);
        pair<int, int> x(0, total_cells - 1);
        cells.push_back(x);

        for (int i = 0;; i++) {
            //next level cell step
            double tmp = cellStep[i] * 2;
            //next level first cell id
            x.first = total_cells;

            //if cell step large than 0.5 set this level to highest-level
            if (tmp >= 0.5) {
                total_cells++;
                x.second = total_cells - 1;
                cells.push_back(x);
                break;
            }

            cellStep.push_back(tmp);
            total_cells += (int)(1 / tmp) - 1;
            x.second = total_cells - 1;
            cells.push_back(x);
        }

        buckStep = (valDom - 1) / MAX_BUCKS + 1;
        buckets.resize(int(pow(total_cells, level) + 0.5));
        counter.resize(int(pow(total_cells, level) + 0.5));

        for (auto& cell : buckets) {
            cell.resize(atts);
            for (auto& bucket : cell) {
                bucket.resize(2);
                for (auto& buck : bucket)buck.resize(MAX_BUCKS);
            }
        }
    }

    ~HRtree() { 
        match_log("****************************************************************************************************\n");
        match_log("****************************************************************************************************\n\n");
        log.close(); 
    }

    void insert(IntervalSub &sub);
    void delete_sub(IntervalSub sub);
    size_t mem_size();

    void match(const Pub &pub, int &matchSubs, const vector<IntervalSub> &subList);

    void cout_buck_size() {
        string FileName = "count.txt";
        ofstream outputfile(FileName, ios::out);
        if (!outputfile) {
            cout << "error opening destination file." << endl;
        }
        for (int i = 0; i < counter.size(); i++) {
            outputfile << counter[i].size() << "\n";
        }
        outputfile.close();
    }

    void match_log(string buff) {
        log << buff;
    }

    int get_cells() { return this->total_cells; }
};

#endif //_HRTREE_H_
