#include "Harsh.h"

// MySolution
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_set<int> harsh;
        int left = 0, right = 0;
        int ans = -1;
        while (right < cards.size()) {
            if (harsh.count(cards[right]) == 0) {
                harsh.insert(cards[right]);
            }
            else {
                int tmp = left;
                while (cards[left] != cards[right]) {
                    left++;
                }
                if (left == right) {
                    left = tmp;
                }
                if ((ans == -1 || ans >= right - left + 1)) {
                    ans = right - left + 1;
                    left++;
                }
            }
            right++;
        }
        return ans;
    }
};


// OptimSolution
class Solution {
public:
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int, int> lastSeen;
        int ans = INT_MAX;

        for (int right = 0; right < cards.size(); right++) {
            if (lastSeen.find(cards[right]) != lastSeen.end()) {
                int windowLength = right - lastSeen[cards[right]] + 1;
                ans = min(ans, windowLength);
            }
            lastSeen[cards[right]] = right;
        }
        return ans == INT_MAX ? -1 : ans;
    }
};