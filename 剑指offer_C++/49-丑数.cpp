#include "header.h"

// 只包含2, 3, 5为因数的数为丑数
// 如果x为丑数，那么2x，3x，5x也为丑数


// Solution1: 使用优先级队列 + set去重
// 将第一个丑数1丢入优先级队列中
// 每次从优先级队列中取一个数x
// 再将2x, 3x, 5x也丢入优先级队列中
// 前面需要判断该数是否重复出现过
// 求第n个丑数
// 注意数据长度可能超过32位
class Solution {
public:
    int nthUglyNumber(int n) {
        int d[3] = {2, 3, 5};
        using LL = long long;
        std::priority_queue<LL, vector<LL>, greater<LL>> pq; // 最小堆
        std::unordered_map<LL, bool> has;
        pq.push(1);
        has[1] = true;
        for (int i = 1; ; ++i) {
            LL x = pq.top();
            pq.pop();

            if (i == n) {
                return x;
            }

            for (int j = 0; j < 3; ++j) {
                LL temp = x * d[j];
                if (has.find(temp) == has.end()) {
                    has[temp] = true;
                    pq.push(temp);
                }
            }
        }
        return -1;
    }
};


// Solution2: 三指针dp
// 在已有的丑数序列上每一个数都必须乘2， 乘3， 乘5， 这样才不会漏掉某些丑数。假设已有的丑数序列为[1, 2, 3, ..., n1, n2], 如果单纯的让每个丑数乘2， 乘3， 乘5顺序排列的话肯定会有问题，
// 比如如果按照这样的顺序排列下去肯定有问题[1*2, 1*3, 1*5, 2*2, 2*3, 2*5, 3*2, 3*3, 3*5, ... , n1 *2, n1 * 3, n1 * 5, n2 * 2, n3* 3, n2 * 5]
// 因为后面乘2的数据可能会比前面乘3乘5的数据要小，那这个乘2的数应该排在他们的前面， 后面乘3的数据也可能比前面乘5的数据要小，那这个乘3的数应该排在他们的前面。
// 每个数都必须乘2， 乘3， 乘5这样才能保证求出所有的丑数，而且还要保证丑数的顺序，这如何同时实现呢？
// 那就是记录每个丑数是否已经被乘2， 乘3， 乘5了， 具体的做法是
// 设置3个索引a, b, c，分别记录前几个数已经被乘2， 乘3， 乘5了
// 比如a表示前(a-1)个数都已经乘过一次2了，下次应该乘2的是第a个数；b表示前(b-1)个数都已经乘过一次3了，下次应该乘3的是第b个数；c表示前(c-1)个数都已经乘过一次5了，下次应该乘5的是第c个数；
// 对于某个状态下的丑数序列，我们知道此时第a个数还没有乘2(有没有乘3或者乘5不知道）， 第b个数还没有乘3(有没有乘2或者乘5不知道），第c个数还没有乘5(有没有乘2或者乘3不知道)
// 下一个丑数一定是从第a丑数乘2， 第b个数乘3， 第c个数乘5中获得，他们三者最小的那个就是下个丑数

// 状态转移公式：dp[i] = min(dp[a] * 2, dp[b] * 3, dp[c] * 5)
// 然后将对应最小的指针++
class Solution {
public:
    int nthUglyNumber(int n) {
        int a = 1, b = 1, c = 1, num1, num2, num3;
        vector<int> dp(n+1);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            num1 = dp[a] * 2, num2 = dp[b] * 3, num3 = dp[c] * 5;
            dp[i] = min(min(num1, num2), num3); // min的min，或者直接传迭代器
            if (dp[i] == num1) {
                ++a;
            }
            if (dp[i] == num2) {
                ++b;
            }
            if (dp[i] == num3) {
                ++c;
            }
        }
        return dp[n];
    }
};
