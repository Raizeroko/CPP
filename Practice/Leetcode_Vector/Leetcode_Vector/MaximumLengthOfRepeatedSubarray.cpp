#include <vector>

using namespace std;

// MySolution
class Solution {
public:
    int ret = 0;

    int compare(vector<int>::iterator it1, vector<int>::iterator it2,
        vector<int>::iterator end1, vector<int>::iterator end2) {
        int compare = 0;
        while (it1 != end1 && it2 != end2 && *it1 == *it2) {
            compare++;
            it1++;
            it2++;
        }
        return compare;
    }

    int findLength(vector<int>& nums1, vector<int>& nums2) {
        auto it1 = nums1.begin();
        while (it1 != nums1.end())
        {
            int tmp = 0;
            auto it2 = nums2.begin();
            while (it2 != nums2.end())
            {
                if (nums2.end() - it2 <= ret)
                    break;
                tmp = compare(it1, it2, nums1.end(), nums2.end());
                if (tmp > ret) {
                    ret = tmp;
                }
                it2++;
            }
            it1++;
        }

        return ret;
    }
};

// OptimSolution

