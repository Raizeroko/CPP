#define _CRT_SECURE_NO_WARNINGS 1

//594. 最长和谐子序列
//
class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int maxSize = 0;
        for (int i = 0, j = i + 1; i < nums.size() - 1; i++)
        {

            for (; j < nums.size(); j++)
            {
                if (abs(nums[i] - nums[j]) > 1)
                {
                    //cout<< abs(nums[i] - nums[j]);
                    break;
                    //cout << maxSize << ' ';
                }
            }
            if (nums[i] != nums[j - 1])
                maxSize = max(maxSize, j - i);

        }
        return maxSize;
    }
};