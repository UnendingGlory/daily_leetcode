#include <bits/stdc++.h>
using namespace std;

/*
 * 判断一个数组是否能划分为两个子集，且这两个子集等和
 * 可以转换为背包问题，即是否能够选取一些数，使得这些数恰好等于数组和的一半
 * 这就转换成了0, 1背包问题的变形，假设数组和的一半为target
 * 创建一个二维数组dp，第一维为数组的长度len，第二维为从0……target
 * 其中dp[i][j]表示从数组的[0……i]下标范围内选取若干个正整数，
 * 是否存在一种选取方案使得这些数的和为j
 * 状态转移方程：
 * dp[i][j] = dp[i - 1][j]， 不选取第i个数
 * dp[i][j] = dp[i - 1][j - nums[i]]， 选第i个数
 * 转移完了之后最后输出的dp[len - 1][target]即结果
 * 表示从数组中所有数种选取，能否得到target
 * 预处理时要考虑到很多边界情况
 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size(), sum = 0, maxNum = -1;
        for(auto i : nums) sum += i, maxNum = max(maxNum, i);
        // 和为奇数则返回false
        if(sum & 0x01) return false;
        int target = sum / 2;
        if(maxNum > target) return false;
        // 创建一个二维数组，类型为bool
        vector<vector<bool>> dp(len, vector<bool>(target + 1, false));
        // 第一列初始化为True，总和为0，不管几个数，都不取即可
        for(int j = 0; j < len; ++j) dp[j][0] = true;
        // 第一行是边界，只选第一个数，否则会越界
        dp[0][nums[0]] = true;
        // 接下来从第二行开始
        for(int i = 1; i < len; ++i)
        {
            for(int j = 0; j <= target; ++j)
            {
                // 如果背包的容量比当前新加的数小，状态显然应该继承
                if(j < nums[i]) dp[i][j] = dp[i - 1][j];
                else
                {
                    // 如果大的话再讨论不选和选
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
                }
            }
        }
        // 最终所有的数到target的情况
        return dp[len - 1][target];
    }
};

// 空间优化，由于每一行的dp值只和上一行的dp值有关，所以可以直接进行覆盖操作
// 优化成：dp[j] = dp[j] | dp[j - nums[i]]

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size(), sum = 0, maxNum = -1;
        for(auto i : nums) sum += i, maxNum = max(maxNum, i);
        // 和为奇数则返回false
        if(sum & 0x01) return false;
        int target = sum / 2;
        if(maxNum > target) return false;
        // 创建一个二维数组，类型为bool
        vector<bool> dp(target + 1, false);
        // 第一列初始化为True，总和为0，不管几个数，都不取即可
        dp[0] = true;
        for(int i = 0; i < len; i++) {
            int num = nums[i];
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j] | dp[j - num];
            }
        }
        return dp[target];
    }
};