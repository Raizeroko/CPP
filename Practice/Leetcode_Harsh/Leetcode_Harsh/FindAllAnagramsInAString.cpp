#include "Harsh.h"

// MySolution(29/65)
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> harsh;
        for (auto c : p) {
            harsh[c]++;
        }
        vector<int> ret;
        int r = 0;
        int l = 0;
        while (l < s.size() - p.size() + 1 && r < s.size()) {
            int tmp = 0;
            // 初始化already
            unordered_map<char, int> already = unordered_map<char, int>();
            // 找不到控制左边界增加
            while (l < s.size() && harsh.find(s[l]) == harsh.end()) {
                l++;
                already[s[l]]--;
            }
            // 越界直接离开
            if (l == s.size() || s.size() - l < p.size()) {
                return ret;
            }
            r = l;
            // 没有就存放
            while (r < s.size() && harsh.find(s[r]) != harsh.end() && already[s[r]] != harsh[s[r]]) {
                already[s[r]]++;
                r++;
            }
            for (auto e : already) {
                cout << e.first << ' ' << e.second;
            }
            cout << endl;
            // 存放的数量和p的数量一致
            if (r - l == p.size()) {
                ret.push_back(l);
            }
            l++;
            already[s[l]]--;

        }
        return ret;
    }
};

// OptmSolution
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> ret;
        // s 比 p 短，无解
        if (s.size() < p.size()) return ret;

        // 统计 p 中字符的频次
        unordered_map<char, int> harsh;
        for (char c : p) {
            harsh[c]++;
        }

        // 滑动窗口中字符的频次
        unordered_map<char, int> window;
        int valid = 0; // 当前匹配的字符数量

        int l = 0, r = 0; // 定义左右指针
        while (r < s.size()) {
            char c = s[r]; // 当前右边界字符
            r++;

            // 如果 c 在 p 中，更新窗口中的计数
            if (harsh.count(c)) {
                window[c]++;
                if (window[c] == harsh[c]) {
                    valid++;
                }
            }

            // 当窗口大小超过 p 的长度时，需要收缩左边界
            while (r - l >= p.size()) {
                // 如果匹配字符数等于 p 的字符种类数，说明找到异位词
                if (valid == harsh.size()) {
                    ret.push_back(l);
                }

                char d = s[l]; // 左边界字符
                l++;

                // 如果 d 在 p 中，更新窗口中的计数
                if (harsh.count(d)) {
                    if (window[d] == harsh[d]) {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }

        return ret;

    }
};