#include "Vector.h"

//OptimSolution
class Solution {
    vector<int> visited;
    vector<vector<int>> edges;
    bool valid = true;
public:
    void dfs(int u) {
        visited[u] = 1;
        for (int v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) {
                    return;
                }
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }


    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // �ÿγ��Ƿ������
        visited.resize(numCourses);
        // �γ̽ṹת��
        edges.resize(numCourses);
        for (auto info : prerequisites) {
            // ��ɸÿγ�(info[1])����ѧϰ�ĸ��γ�
            edges[info[1]].push_back(info[0]);
        }
        for (int i = 0; i < numCourses; i++) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;

    }
};