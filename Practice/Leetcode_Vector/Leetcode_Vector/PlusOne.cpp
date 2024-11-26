#include <vector>
using namespace std;


// MySolution
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (auto it = digits.rbegin(); it != digits.rend(); it++) {
            *it += carry;
            if (*it == 10) {
                carry = 1;
                *it = 0;
            }
            else {
                carry = 0;
                break;
            }
        }
        if (carry == 1) {
            digits.insert(digits.begin(), carry);
        }
        return digits;
    }
};
