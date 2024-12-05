#include<vector>
#include<stack>

using namespace std;

// MySolution
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> ret(temperatures.size(), 0);
        stack<int> s;
        for (int i = 0; i < temperatures.size(); i++)
        {
            while (!s.empty() && temperatures[s.top()] < temperatures[i])
            {
                int k = s.top();
                s.pop();
                ret[k] = i - k;
            }
            s.push(i);
        }
        return ret;
    }
};
