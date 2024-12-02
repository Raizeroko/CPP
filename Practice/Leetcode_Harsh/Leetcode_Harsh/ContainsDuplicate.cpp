    #include<unordered_set>

    using namespace std;

    // MySolution
    class Solution {
    public:
        bool containsDuplicate(vector<int>& nums) {
            unordered_set<int> set;
            for (auto e : nums) {
                if (set.find(e) != set.end()) {
                    return true;
                }
                set.insert(e);
            }
            return false;
        }
    };