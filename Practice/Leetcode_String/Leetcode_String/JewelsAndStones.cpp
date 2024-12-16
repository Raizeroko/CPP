#include <string>
#include <unordered_set>

using namespace std;

// MySolution
class Solution {
public:
    int numJewelsInStones(string jewels, string stones) {
        unordered_set<char> set;
        for (auto& jewel : jewels) {
            set.insert(jewel);
        }
        int ret = 0;
        for (auto& stone : stones) {
            auto it = set.find(stone);
            if (it != set.end()) {
                ret++;
            }
        }
        return ret;
    }
};