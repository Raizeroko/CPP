#define _CRT_SECURE_NO_WARNINGS 1

//771. 宝石与石头
//
class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        int ret = 0;
        for (size_t i = 0; i < jewels.size(); i++)
        {
            for (size_t j = 0; j < stones.size(); j++)
            {
                if (jewels[i] == stones[j])
                {
                    ret++;
                }
            }
        }
        return ret;
    }
};

//796. 旋转字符串
//
class Solution {
public:
    bool rotateString(string s, string goal) {
        for (size_t i = 0; i < s.size(); i++)
        {
            if (s == goal)
            {
                return true;
            }
            char tmp = s[s.size() - 1];
            s.insert(0, 1, tmp);
            s.pop_back();
        }
        return false;
    }
};
