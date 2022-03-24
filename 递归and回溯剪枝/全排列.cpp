#include "header.h"
using namespace std;

// 经典解法
class Solution {
    int n;
    unordered_map<int, bool> vis;
    vector<int> p;
    vector<vector<int>> ans;
public:

    // 递归生成，分解成子问题
    void generate(int index, const vector<int>& nums)
    {
        if(index == n) // 递归边界
        {
            ans.push_back(p);
            return;
        }
        for(auto i : nums) // 遍历每个数，挑一个未访问过的
        {
            if(vis[i] == false)
            {
                p.push_back(i);
                vis[i] = true; // 已被访问
                generate(index + 1, nums);    
                vis[i] = false; // 向深层遍历，退出的时候还原
                p.pop_back();
            }
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        n = nums.size();
        for(int i : nums) vis[i] = false;
        generate(0, nums);
        return ans;
    }
};