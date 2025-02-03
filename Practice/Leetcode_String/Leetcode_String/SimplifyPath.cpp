#include "String.h"

// MySolution
class Solution {
public:
    string simplifyPath(string path) {
        deque<string> dq;
        for (int l = 0, r = 0; r < path.size();) {
            if (path[l] == '/') {
                r = l + 1;
            }
            while (r < path.size() && path[r] != '/') {
                r++;
            }
            string subpath = string(path, l, r - l);
            if (subpath == "/..") {
                if (!dq.empty())
                    dq.pop_back();
            }
            else if (subpath != "/" && subpath != "/.") {
                dq.push_back(subpath);
            }
            l = r;
        }
        string ret;
        if (dq.empty()) {
            return "/";
        }
        for (auto e : dq) {
            ret += e;
        }
        return ret;
    }
};
