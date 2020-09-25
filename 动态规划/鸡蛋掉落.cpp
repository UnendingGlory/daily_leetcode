#include <bits/stdc++.h>
using namespace std;

/** 动态规划经典问题，谷歌经典面试题
 *  最巧妙办法：逆向思维，假设我们可以做T次操作，有K个鸡蛋，那么我们能找到答案最高的N是多少？
 *  如果我们求出了所有的f(T, K)，那么我们只需要找出最小的满足f(T, K) >= N 的T即可
 *  如何求f(T, K) ? 可以用动态规划
 *  扔出一个鸡蛋，如果鸡蛋没有碎，则对应f(T - 1, K)，即在这一层的上方可以有f(T - 1, K)层
 *  如果碎了，则对应f(T - 1, K - 1)，即在这一层的下方可以有f(T - 1, K - 1)层
 *  状态转移方程:f(T, K) = f(T- 1, K - 1) + f(T - 1, K) + 1层。
 *  即某个状态最多的楼层等于上面的楼层数 + 下面的楼层数 + 1当前楼层
 *  边界条件：f(T, 1) = T，f(1, K) = 1
 *  T最多是多少呢？T最多就是每次都不碎，一直到最高楼层，即N
 *  所以从边界出发，一直递推到T = N
 *  再在f(T, k)中寻找最小的满足f(T, K) >= N的T即可
 */

class Solution {
public:
    int superEggDrop(int K, int N) {
        int dp[N + 1][K + 1];
        for(int i = 1; i <= N; ++i) dp[i][1] = i;
        for(int i = 1; i <= K; ++i) dp[1][i] = 1;
        for(int i = 2; i <= N; ++i) // 已经讨论过一层楼的情况，所以从2层开始
        {
            for(int j = 2; j <= K; ++j)
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + 1;
            if(dp[i][K] >= N) return i;
        }
        return 1; // 一层楼只返回一次
    }
};