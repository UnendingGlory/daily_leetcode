#include <../header.h>

// T1
class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int ans = 0;
        unordered_map<char, set<int>> wm;
        for(int i = 0; i < s.size(); ++i) wm[s[i]].insert(i);
        bool flag = false;
        for(auto i : wm)
        {
            char a = i.first;
            auto m = i.second;
            if(m.size() > 1) flag = true;
            ans = max(ans,  *(--m.end()) -*m.begin() - 1);
        }
        if(!flag) return -1;
        return ans;
    }
};


// T2

// T3
// Union find set

class Solution {
    int n;
    vector<int> father;
public:
    int find(int x)
    {
        int z = x;
        while(x != father[x]) x = father[x];
        return x;
    }

    void Union(int a, int b)
    {
        int fa = find(a), fb = find(b);
        if(fa != fb)
            father[fa] = fb;
    }

    // 最大流分割
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = ages.size();
        father.resize(n);
        for(int i = 0; i < n; ++i) father[i] = i;
        for(int i = 0; i < n; ++i)
        {
            for(int j = i + 1; j < n; ++j)
            {
                if(ages[i] < ages[j] && scores[i] > scores[j]) continue;
                if(ages[j] < ages[i] && scores[j] > scores[i]) continue;
                // 否则则Union
                /// cout << father[i] << father[j] << endl;
                Union(i, j);
            }
        }
        // 贪心，如果年龄相同优先选择score高的
        // 找寻root
        unordered_map<int, int> root;
        for(int i = 0; i < n; ++i)
        {
            // cout << father[i] << endl;
            root[find(i)] += scores[i];
        }
        int ans = 0;
        for(auto i : root)
        {
            ans = max(ans, i.second);
        }
        return ans;
    }
};

// T4
