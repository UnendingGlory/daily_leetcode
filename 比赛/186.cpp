#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    int maxScore(string s) {
        int n = s.size();
        int left[n], right[n];
        memset(left, 0, sizeof(left));
        memset(right, 0, sizeof(right));
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == '0')
                for(int j = i ; j < n; ++j) ++left[j];
            else
                for(int j = i; j >= 0; --j) ++right[j];
        }
        int res = 0;
        for(int i = 0; i < n; ++i)
            res = max(res, left[i] + right[i + 1]);
        return res;
    }
};


// T2，dfs必定超时
// 转换思路：左边拿i张，右边拿k - i张，用前缀和和后缀和
class Solution {
    int res = 0, K;
public:

    void dfs(vector<int>& a, int step, int sum, int i, int j)
    {
        if(step == K)
        {
            res = max(res, sum);
            return;
        }
        dfs(a, step + 1, sum + a[i + 1], i + 1, j);
        dfs(a, step + 1, sum + a[j - 1], i, j - 1);
    }

    int maxScore(vector<int>& cardPoints, int k) {
        K = k;
        dfs(cardPoints, 0, 0, -1, cardPoints.size());
        return res;
    }
};

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int ret = 0;
        int tmpRes = 0;
        for (int i = 0; i < k; i++)
        {
            tmpRes = tmpRes + cardPoints[i];
        }
        int l = k - 1, r = cardPoints.size() - 1;
        ret = tmpRes;
        while (l >= 0)
        {
            tmpRes = tmpRes - cardPoints[l] + cardPoints[r];
            l--;
            r--;
            ret = ret < tmpRes ? tmpRes : ret;
        }
        return ret;
    }
};

// T3
class Solution {
    struct node
    {
        int i, j; // 下标
        int val;
        bool operator<(const node & a)const
        {
            return (i + j) == (a.i + a.j) ? i > a.i : (i + j) < (a.i + a.j);
        }
    };
    
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        set<node> ans;
        for(int i = 0; i < nums.size(); ++i)
        {
            for(int j = 0; j < nums[i].size(); ++j)
            {
                node temp{i, j, nums[i][j]};
                ans.insert(temp);
            }
        }
        vector<int> res;
        for(auto i : ans)
            res.push_back(i.val);
        return res;
    }
};


// T4