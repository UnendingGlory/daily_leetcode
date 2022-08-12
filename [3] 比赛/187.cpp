#include <bits/stdc++.h>
using namespace std;

// T1
// 不会通往其他城市
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        set<string> start, end;
        for(auto i : paths)
        {
            start.insert(i[0]);
            end.insert(i[1]);
        }
        for(auto i : end)
        {
            if(start.find(i) == start.end())
                return i;
        }
        return "";
    }
};

// T2
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        int last = 0, flag = 0; // 上一个1的位置
        for(int i = 0; i < nums.size(); ++i)
        {
            if(nums[i] == 1)
            {
                if(flag == 0) flag = 1;
                else
                {
                    if(i - last - 1 < k) return false;
                    last = i;
                }
            }
        }
        return true;
    }
};

// T3
// 滑动窗口，双指针
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int n = nums.size();
        int left = 0, right = 0, ans = 1;
        int _min = nums[0], _max = nums[0];
        while(left < n && right < n)
        {
            //printf("%d %d\n", left, right);
            if(abs(_min - _max) <= limit)
            {
                ans = max(ans, right - left + 1);
                ++right;
                if(right < n)
                {
                    _min = min(nums[right], _min);
                    _max = max(nums[right], _max);
                }
            }
            else
            {
                ++left;
                if(left < n)
                {
                    _max = _min = nums[left];
                    for(int i = left; i <= right; ++i)
                    {
                        _min = min(nums[i], _min);
                        _max = max(nums[i], _max);
                    }
                }
            }
        }
        return ans;
    }
};

// T4，由于k最大为200，所以直接暴力
class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k){
        vector<int> res, temp;
        res.push_back(0);
        int row = mat.size(), col = mat[0].size();
        for (int i = 0; i < row; ++i) 
        {
            for (int j = 0; j < col; ++j) 
            {
                for (int m = 0, n = res.size(); m < n; ++m) 
                {
                    int ss = mat[i][j] + res[m];
                    temp.push_back(ss);
                }
            }
            sort(temp.begin(), temp.end());
            temp.erase(temp.begin() + min((int)temp.size(), k), temp.end());
            temp.swap(res);
            temp.clear();
        }
        return res.back();
    }
};