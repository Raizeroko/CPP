#include "Vector.h"

// MySolution
class Solution {
public:
    vector<int> mergeInterval(vector<int> v1, vector<int> v2) {

        v1[1] = v2[1];
        return v1;
    }


    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        for (int cur = 0; cur < intervals.size() - 1;) {
            vector<int>& v1 = intervals[cur];
            int flag = 0;
            for (int next = cur + 1; next < intervals.size();) {
                vector<int>& v2 = intervals[next];
                if (v1[1] >= v2[0] && v1[0] <= v2[0] && v1[1] <= v2[1]) {
                    v1 = mergeInterval(v1, v2);
                    intervals.erase(intervals.begin() + next);
                    flag = 1;
                    continue;
                }
                else if (v1[0] <= v2[1] && v1[0] >= v2[0] && v1[1] > v2[1]) {
                    v1 = mergeInterval(v2, v1);
                    intervals.erase(intervals.begin() + next);
                    flag = 1;
                    continue;

                }
                else if (v1[0] <= v2[0] && v1[1] >= v2[1]) {
                    intervals.erase(intervals.begin() + next);
                    flag = 1;
                    continue;
                }
                else if (v2[0] < v1[0] && v2[1] >= v1[1]) {
                    v1 = v2;
                    intervals.erase(intervals.begin() + next);
                    flag = 1;
                    continue;
                }
                next++;
            }
            if (flag != 1) {
                cur++;
            }
        }
        return intervals;

    }
};


// OptimSolution
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> merged;
        int k = 0;
        int mleft = intervals[k][0];
        int mright = intervals[k][1];
        for (int i = 1; i < intervals.size(); i++)
        {
            int before = mright;
            int after = intervals[i][0];
            if (before < after)
            {
                mright = before;
                vector<int> interval = { mleft, mright };
                merged.push_back(interval);
                k = i;
                mleft = intervals[k][0];
                mright = intervals[k][1];
            }
            else
            {
                if (intervals[i][1] > mright)
                {
                    mright = intervals[i][1];
                }
            }
        }
        vector<int> interval = { mleft, mright };
        merged.push_back(interval);

        return merged;
    }
};

// Review(2025/2/10)
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // sort(intervals.begin(), intervals.end(), [&](vector<int> a, vector<int> b){return a[0] < b[0];});
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ret;
        ret.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            int& retRight = ret.back()[1];
            vector<int> interval = intervals[i];
            if (retRight < interval[0]) {
                ret.push_back(interval);
            }
            else {
                retRight = retRight > interval[1] ? retRight : interval[1];
            }
        }

        return ret;
    }
};


// Review 2025_03_06
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ret;
        int i = 0;
        while (i < intervals.size()) {
            vector<int> interval = intervals[i];
            int cur = i + 1;
            while (cur < intervals.size() && interval[1] >= intervals[cur][0]) {
                interval[1] = max(intervals[cur][1], interval[1]);
                cur++;
            }
            ret.push_back(interval);
            i = cur;
        }
        return ret;
    }
};