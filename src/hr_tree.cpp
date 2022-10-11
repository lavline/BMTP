#include "hr_tree.h"


void HRtree::insert(IntervalSub &sub)
{
    vector<vector<int> > mark;
    mark.resize(unsigned(mLevel));
    for (int i = 0; i < sub.size; i++)
    {
        int att = sub.constraints[i].att;
        if (att < mLevel)        // Choose the first mLevel attributes as Indexed attributes
        {
            double low = sub.constraints[i].lowValue / (double) valDom, 
                   high = sub.constraints[i].highValue / (double) valDom;
            
            for (int j = 0; j < cellStep.size(); j++) {
                if ((high - low) < cellStep[j]) {
                    double center = (low + high) / 2.0;
                    double slice = cellStep[j] / 2.0;
                    if (center < slice)
                        mark[att].push_back(cells[j].first);  //isert to first cell in this level
                    else if (center > 1 - slice)
                        mark[att].push_back(cells[j].second); //insert to the last cell in this level
                    else
                        mark[att].push_back((int)((center - slice) / cellStep[j]) + cells[j].first);
                    break;
                }
                else if ((int)(low / cellStep[j]) == (int)((high - cellStep[j]) / cellStep[j])) { //if be covered
                    mark[att].push_back((int)(low / cellStep[j]) + cells[j].first);
                    break;
                }
            }
        }

    }
    for (int i = 0; i < mLevel; i++)
        if (mark[i].size() == 0)
            mark[i].push_back(total_cells - 1);
    insertToBucket(mark, 0, 0, sub);
}

void HRtree::delete_sub(IntervalSub sub)
{
    vector<vector<int> > mark;
    mark.resize(unsigned(mLevel));
    for (int i = 0; i < sub.size; i++)
    {
        int att = sub.constraints[i].att;
        if (att < mLevel)        // Choose the first mLevel attributes as Indexed attributes
        {
            double low = sub.constraints[i].lowValue / (double)valDom,
                high = sub.constraints[i].highValue / (double)valDom;

            for (int j = 0; j < cellStep.size(); j++) {
                if ((high - low) < cellStep[j]) {
                    double center = (low + high) / 2.0;
                    double slice = cellStep[j] / 2.0;
                    if (center < slice)
                        mark[att].push_back(cells[j].first);
                    else if (center > 1 - slice)
                        mark[att].push_back(cells[j].second);
                    else
                        mark[att].push_back((int)((center - slice) / cellStep[j]) + cells[j].first);
                    break;
                }
                else if ((int)(low / cellStep[j]) == (int)((high - cellStep[j]) / cellStep[j])) {
                    mark[att].push_back((int)(low / cellStep[j]) + cells[j].first);
                    break;
                }
            }
        }

    }
    for (int i = 0; i < mLevel; i++)
        if (mark[i].size() == 0)
            mark[i].push_back(total_cells - 1);
    deleteInBucket(mark, 0, 0, sub);
}

size_t HRtree::mem_size()
{
    size_t sum = 0;
    sum += buckets.size() * atts * 2 * MAX_BUCKS * sizeof(vector<Combo>);
    for (auto cell : buckets) {
        for (int i = 0; i < atts; i++) {
            for (int j = 0; j < MAX_BUCKS; j++) {
                sum += cell[i][0][j].size() * sizeof(Combo);
                sum += cell[i][1][j].size() * sizeof(Combo);
            }
        }
    }
    return sum;
}


void HRtree::insertToBucket(const vector<vector<int> > &mark, int bucketID, int level, IntervalSub& sub)
{
    if (level == mLevel - 1)
    {
        int cellId = bucketID + mark[level][0];
        int subId = counter[cellId].size();
        counter[cellId].push_back(sub.id);

        for (int i = 0; i < sub.size; i++) {
            int att = sub.constraints[i].att, lval = sub.constraints[i].lowValue, hval = sub.constraints[i].highValue;
            Combo tmp = { lval, subId };
            buckets[cellId][att][0][lval / buckStep].push_back(tmp);
            tmp.val = hval;
            buckets[cellId][att][1][hval / buckStep].push_back(tmp);
        }
        return;
    }
    insertToBucket(mark, (bucketID + mark[level][0]) * total_cells, level + 1, sub);
}

void HRtree::deleteInBucket(const vector<vector<int> >& mark, int bucketID, int level, IntervalSub& sub)
{
    if (level == mLevel - 1)
    {
        int cellId = bucketID + mark[level][0];
        int subId = sub.id;
        int Id = -1;
        for (int i = 0; i < counter[cellId].size(); i++) {
            if (counter[cellId][i] == subId) {
                Id = i;
                counter[cellId][i] = -1;
            }
        }
        if (Id == -1)return;

        for (int i = 0; i < sub.size; i++) {
            int att = sub.constraints[i].att, lval_id = sub.constraints[i].lowValue / buckStep, hval_id = sub.constraints[i].highValue / buckStep;
            for (int j = 0; j < buckets[cellId][att][0][lval_id].size(); j++)
                if (buckets[cellId][att][0][lval_id][j].subID == Id) {
                    buckets[cellId][att][0][lval_id][j].subID = -1;
                    buckets[cellId][att][0][lval_id][j].val = -1;
                }
            for (int j = 0; j < buckets[cellId][att][1][hval_id].size(); j++)
                if (buckets[cellId][att][1][hval_id][j].subID == Id) {
                    buckets[cellId][att][1][hval_id][j].subID = -1;
                    buckets[cellId][att][1][hval_id][j].val = valDom + 1;
                }
        }
        return;
    }
    deleteInBucket(mark, (bucketID + mark[level][0]) * total_cells, level + 1, sub);
}

void HRtree::match(const Pub &pub, int &matchSubs, const vector<IntervalSub> &subList)
{
    //memset(matched, 0, sizeof(matched));
    vector<vector<int> > mark;
    mark.resize(mLevel);
    for (int i = 0; i < pub.size; i++)
    {
        int att = pub.pairs[i].att;
        if (att < mLevel)
        {
            double value = pub.pairs[i].value / (double) valDom;
            for (int j = 0; j < cellStep.size(); j++) {
                if (value < cellStep[j])
                    mark[att].push_back(cells[j].first);
                else if (value > 1 - cellStep[j])
                    mark[att].push_back(cells[j].second);
                else
                {
                    mark[att].push_back(int(value / cellStep[j]) - 1 + cells[j].first);
                    mark[att].push_back(int(value / cellStep[j]) + cells[j].first);
                }
            }
        }
    }
    for (int i = 0; i < mLevel; i++)
        mark[i].push_back(total_cells - 1);

    int _mark = 0;
    int _subs = 0;

    matchInBucket(mark, 0, 0, matchSubs, subList, pub, _mark, _subs);

    int _cells = 1;
    for (int i = 0; i < mark.size(); i++)_cells *= mark[i].size();
    match_log("\nprocess_cell:" + to_string(_cells) + " process_subs:" + to_string(_subs) + "/" + to_string((int)(_subs * 100/ subList.size()))
        + " total_marked:" + to_string(_mark) + "/" + to_string((int)(_mark * 100 / (subList.size() * subList[0].size)))
        + " total_matched:" + to_string(matchSubs) + "/" + to_string((int)(matchSubs * 100 / subList.size())));
    match_log("\n\n****************************************************************************************************\n\n");
}


void HRtree::matchInBucket(const vector<vector<int> > &mark, int bucketID, int level, int &matchSubs,
                          const vector<IntervalSub> &subList, const Pub &pub, int &_mark, int &_subs)
{
    if (level == mLevel - 1)
    {
        string buff = "";

        int* tmp = new int[atts];
        for (int i = 0; i < atts; i++)
            tmp[i] = -1;
        for (int i = 0; i < pub.size; i++)
            tmp[pub.pairs[i].att] = i;

        for (int i = 0; i < mark[level].size(); i++)
        {
            int cellId = bucketID + mark[level][i];
            int subSize = counter[cellId].size();
            int mark_num = 0;
            int match_num = 0;

            if (subSize == 0) {
                buff += "cellId:" + to_string(cellId) + " size:" + to_string(subSize) + " marked:" + to_string(mark_num)
                    + " matched:" + to_string(match_num) + "\n";
                continue;
            }
            else if (subSize < 5000) {
                for (int k = 0; k < counter[cellId].size(); k++)
                {
                    IntervalSub sub = subList[counter[cellId][k]];

                    bool flag = true;
                    for (int j = 0; j < sub.size; j++)
                    {
                        int att = sub.constraints[j].att;
                        if (tmp[att] == -1 || pub.pairs[tmp[att]].value < sub.constraints[j].lowValue ||
                            pub.pairs[tmp[att]].value > sub.constraints[j].highValue)
                        {
                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        ++matchSubs;
                        match_num++;
                        //cout << counter[cellId][k] << endl;
                    }
                }
            }
            else {

                vector<bool> bits(subSize, false);

                for (int i = 0; i < pub.size; i++)
                {
                    int value = pub.pairs[i].value, att = pub.pairs[i].att, buck = value / buckStep;
                    for (int k = 0; k < buckets[cellId][att][0][buck].size(); k++)
                        if (buckets[cellId][att][0][buck][k].val > value) {
                            bits[buckets[cellId][att][0][buck][k].subID] = true;
                            mark_num++;
                        }
                    for (int j = buck + 1; j < MAX_BUCKS; j++)
                        for (int k = 0; k < buckets[cellId][att][0][j].size(); k++) {
                            bits[buckets[cellId][att][0][j][k].subID] = true;
                            mark_num++;
                        }

                    for (int k = 0; k < buckets[cellId][att][1][buck].size(); k++)
                        if (buckets[cellId][att][1][buck][k].val < value) {
                            bits[buckets[cellId][att][1][buck][k].subID] = true;
                            mark_num++;
                        }
                    for (int j = buck - 1; j >= 0; j--)
                        for (int k = 0; k < buckets[cellId][att][1][j].size(); k++) {
                            bits[buckets[cellId][att][1][j][k].subID] = true;
                            mark_num++;
                        }
                }
                for (int i = 0; i < subSize; i++) {
                    if (!bits[i]) {
                        ++matchSubs;
                        match_num++;
                        //cout << counter[cellId][i];
                        //cout << endl;
                    }
                }
            }

            _mark += mark_num;
            _subs += subSize;
            buff += "cellId:" + to_string(cellId) + " size:" + to_string(subSize) + " marked:" + to_string(mark_num) + "/"
                + to_string((int)(mark_num * 100 / (subSize * subList[0].size))) + " matched:" + to_string(match_num) + "/"
                + to_string((int)(match_num * 100 / subSize)) + "\n";
        }
        match_log(buff);
        delete[] tmp;
        return;
    }
    for (int i = 0; i < mark[level].size(); i++)
        matchInBucket(mark, (bucketID + mark[level][i]) * total_cells, level + 1, matchSubs, subList, pub, _mark, _subs);
}
