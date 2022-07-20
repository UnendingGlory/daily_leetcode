#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans;
        for(int i = 0, j = n; i < n; i++, j++)
        {   
            ans.push_back(nums[i]);
            ans.push_back(nums[j]);
        }
        return ans;
    }
};

// T2, m是数组的中位数
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());
        int m = arr[(n - 1) / 2];
        vector<pair<int, int>> temp; // 绝对值差和数值大小
        for(int i = 0; i < n; ++i)
            temp.push_back({arr[i], abs(arr[i] - m)});
        sort(temp.begin(), temp.end(), [&](const pair<int, int> a, const pair<int, int> b)
        {
            return a.second == b.second ? a.first > b.first : a.second > b.second;
        });
        vector<int> ans;
        for(int i = 0; i < k; ++i)
            ans.push_back(temp[i].first);
        return ans;
    }
};

// T3
class BrowserHistory {
public:
    vector<string> web, his; // his : 在下一次vis前存起来
    int vis; // 访问位
    BrowserHistory(string homepage) {
        web.push_back(homepage);
        vis = 0;
    }
    
    void visit(string url) {
        if(vis != web.size() - 1)
        {
            while (web.size() - 1 != vis)
            {
                web.pop_back();
            }
        }
        web.push_back(url);
        vis = web.size() - 1;
    }
    
    string back(int steps) {
        if(vis >= steps) // 可以回退
            vis = vis - steps;
        else // 回退至底部
            vis = 0;
        his.push_back(web[vis]);
        return web[vis];
    }
    
    string forward(int steps) {
        if(vis + steps < web.size())
            vis = vis + steps;
        else vis = web.size() - 1;
        his.push_back(web[vis]);
        return web[vis];
    }
};

// T4

int main()
{
    return 0;
}