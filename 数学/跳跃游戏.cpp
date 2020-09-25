#include <bits/stdc++.h>
using namespace std;

// 暴力解法
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return false;
        // n = 1的情况
        bool vis[n];
        memset(vis, 0, sizeof(vis));
        vis[n - 1] = true;
        // 从后往前更新
        for(int i = n - 2; i >= 0; --i)
        {
            int temp = nums[i];
            for(int j = 1; j <= temp; j++)
            {
                if(vis[i + j] == true)
                {
                    vis[i] = true;
                    break;
                }
            }
        }
        return vis[0];
    }
};

// 贪心解法，维护能到达的最远位置
// 从起始位置开始遍历，如果当前位置+当前值比维护值大，就更新之
// 如果能维护到的最远位置能到达数组的最后一个位置，则return true即可

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int mostright = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            //mostright = max(mostright, nums[i] + i);
            if(i <= mostright && nums[i] + i >= mostright) 
            {
                mostright = nums[i] + i;
                if(mostright >= nums.size() - 1) return true;
            }
        }
        return false;
    }
};
