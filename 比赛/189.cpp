#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    int busyStudent(vector<int>& startTime, vector<int>& endTime, int queryTime) {
        int n = startTime.size(), ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(startTime[i] <= queryTime && endTime[i] >= queryTime)
                ++ans;
        }
        return ans;
    }
};

// 先string
class Solution {
public:
    string arrangeWords(string text) {
        vector<pair<int, string>> ans;
        string temp;
        text[0] = tolower(text[0]);
        for(int i = 0; i < text.size(); ++i)
        {
            if(text[i] == ' ')
            {
                ans.push_back({i, temp});
                temp.clear();
            }
            else temp.push_back(text[i]);
            if(i == text.size() - 1) ans.push_back({i, temp});
        }
        sort(ans.begin(), ans.end(), [&](const pair<int, string> a, const pair<int, string> b)
        {
            return a.second.size() == b.second.size() ? a.first < b.first : a.second.size() < b.second.size();
        });
        string aws = ans[0].second;
        aws[0] = toupper(aws[0]);
        for(int i = 1; i < ans.size(); ++i)
        {
            aws.push_back(' ');
            aws += ans[i].second;
        }
        return aws;
    }
};

// T3
class Solution {
public:
    // 不是其他任何人收藏子集的用户清单
    vector<int> peopleIndexes(vector<vector<string>>& f) {
        unordered_map<string, vector<bool>> m;
        for(auto i : f)
        {
            for(auto j : i)
            {
                m[j].resize(100);
                fill(m[j].begin(), m[j].end(), false);
            }
        }
       for(int i = 0; i < f.size(); ++i) 
       {
           for(int j = 0; j < f[i].size(); ++j)
           {
               m[f[i][j]][i] = true;
           }
       }
       vector<int> ans;
       for(int i = 0; i < f.size(); ++i) 
       {
           int k;
           bool flag = false;
           for(k = 0; k < 100; ++k)
           {
               int j;
               bool flag1 = false;
                for(j = 0; j < f[i].size(); ++j)
                {
                    if(m[f[i][j]][k] == false)
                    {
                        flag1 = true;
                        break;
                    }
                }
                if(flag1 == false) // 是其他子集
                {
                    flag = true;
                    break;
                }
           }
           if(flag == false) ans.push_back(i);
       }
       return ans;
    }
};