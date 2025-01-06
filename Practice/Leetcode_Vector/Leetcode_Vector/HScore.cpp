#include "Vector.h"

// MySolution
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int h = citations.size();
        while (h)
        {
            int tmp;
            auto it = citations.begin();
            for (tmp = 0; it != citations.end(); it++)
            {
                if (*it >= h)
                {
                    tmp++;
                }
            }
            if (tmp >= h) {
                break;
            }
            h--;
        }
        return h;
    }
};

// OptimSolution
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h = 0;
        for (int i = citations.size() - 1; i >= 0; i--) {
            if (citations[i] > h) {
                h++;
            }
            else {
                break;
            }
        }
        return h;
    }
};
