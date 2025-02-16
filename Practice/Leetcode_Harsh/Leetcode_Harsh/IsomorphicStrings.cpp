#include "Harsh.h"

// MySolution
class Solution {
public:
    string transformString(string input) {
        string transform;
        unordered_map<char, int> harsh;
        int index = 1;
        for (auto c : input) {
            if (harsh.find(c) == harsh.end()) {
                harsh[c] = index++;
                cout << harsh[c];
            }

            transform += to_string(harsh[c]);

        }
        return transform;
    }

    bool isIsomorphic(string s, string t) {
        string transformS = transformString(s);
        string transformT = transformString(t);
        cout << transformS << endl;
        cout << transformT << endl;
        return transformS == transformT;

    }
};


// MySolution-v2
class Solution {
public:
    string transformString(const string& input) {
        string transform;
        unordered_map<char, int> harsh;
        int index = 1;

        for (auto c : input) {
            if (harsh.count(c) == 0) {
                harsh[c] = index++;
            }

            transform += harsh[c] + '0';
        }

        return transform;
    }

    bool isIsomorphic(string s, string t) {
        string transformS = transformString(s);
        string transformT = transformString(t);
        return transformS == transformT;
    }
};


// OptimSolution
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> t2s, s2t;
        for (int i = 0; i < s.size(); i++) {
            char a = s[i], b = t[i];
            // ��������ӳ�� a -> s2t[a]�����͵�ǰ�ַ�ӳ�� a -> b ��ƥ�䣬
            // ˵����һ�Զ��ӳ���ϵ���򷵻� false ��
            // ����ӳ�� b -> a Ҳͬ��
            if (s2t.find(a) != s2t.end() && s2t[a] != b ||
                t2s.find(b) != t2s.end() && t2s[b] != a)
                return false;
            s2t[a] = b;
            t2s[b] = a;
        }
        return true;
    }
};
