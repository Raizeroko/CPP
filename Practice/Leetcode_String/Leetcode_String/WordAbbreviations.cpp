#include "String.h"

// Nowcoder
// MySolution
int main() {
    int wordNum;
    string words;
    cin >> wordNum;
    while (cin >> words) { // 注意 while 处理多个 case
        if (words.size() < 10) {
            cout << words << endl;
            continue;
        }
        string abbreviation;
        abbreviation += words.front();
        abbreviation += to_string(words.size() - 2);
        abbreviation += words.back();
        cout << abbreviation << endl;
    }
}
