#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        int indegree[N + 1], outdegree[N + 1];
        memset(indegree, 0, sizeof(indegree));
        memset(outdegree, 0, sizeof(outdegree));
        for(auto i : trust)
            ++outdegree[i[0]], ++indegree[i[1]];
        for(int i = 1; i <= N; ++i)
            if(indegree[i] == N - 1 && !outdegree[i])
                return i;
        return -1;
    }
};

int main()
{
    return 0;
}