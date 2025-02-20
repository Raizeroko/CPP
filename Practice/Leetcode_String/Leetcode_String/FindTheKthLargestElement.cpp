#include "String.h"

// nowcoder
// MySolution
#include <iostream>
#include <vector>
#include <queue> 
#include <functional>
using namespace std;

int main() {
    string input;
    priority_queue<int> pq;
    cin >> input;
    int cur = 0;
    for (int subPosition = 1; subPosition < input.size(); subPosition++) {
        if (input[subPosition] == ',' || input[subPosition] == ']') {
            string subString = input.substr(cur + 1, subPosition - cur - 1);
            pq.push(stoi(subString));
            cur = subPosition;
        }
    }
    pq.pop();
    pq.pop();
    cout << pq.top();
}
