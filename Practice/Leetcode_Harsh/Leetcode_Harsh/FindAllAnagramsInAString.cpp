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
            // ��ʼ��already
            unordered_map<char, int> already = unordered_map<char, int>();
            // �Ҳ���������߽�����
            while (l < s.size() && harsh.find(s[l]) == harsh.end()) {
                l++;
                already[s[l]]--;
            }
            // Խ��ֱ���뿪
            if (l == s.size() || s.size() - l < p.size()) {
                return ret;
            }
            r = l;
            // û�оʹ��
            while (r < s.size() && harsh.find(s[r]) != harsh.end() && already[s[r]] != harsh[s[r]]) {
                already[s[r]]++;
                r++;
            }
            for (auto e : already) {
                cout << e.first << ' ' << e.second;
            }
            cout << endl;
            // ��ŵ�������p������һ��
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
        // s �� p �̣��޽�
        if (s.size() < p.size()) return ret;

        // ͳ�� p ���ַ���Ƶ��
        unordered_map<char, int> harsh;
        for (char c : p) {
            harsh[c]++;
        }

        // �����������ַ���Ƶ��
        unordered_map<char, int> window;
        int valid = 0; // ��ǰƥ����ַ�����

        int l = 0, r = 0; // ��������ָ��
        while (r < s.size()) {
            char c = s[r]; // ��ǰ�ұ߽��ַ�
            r++;

            // ��� c �� p �У����´����еļ���
            if (harsh.count(c)) {
                window[c]++;
                if (window[c] == harsh[c]) {
                    valid++;
                }
            }

            // �����ڴ�С���� p �ĳ���ʱ����Ҫ������߽�
            while (r - l >= p.size()) {
                // ���ƥ���ַ������� p ���ַ���������˵���ҵ���λ��
                if (valid == harsh.size()) {
                    ret.push_back(l);
                }

                char d = s[l]; // ��߽��ַ�
                l++;

                // ��� d �� p �У����´����еļ���
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