#include "header.h"

// 给你一个由 n 个正整数组成的数组 nums 。
// 你可以对数组的任意元素执行任意次数的两类操作：
// 如果元素是 偶数 ，除以 2。
// 例如，如果数组是 [1,2,3,4] ，那么你可以对最后一个元素执行此操作，使其变成 [1,2,3,2]。
// 如果元素是 奇数 ，乘上 2。
// 例如，如果数组是 [1,2,3,4] ，那么你可以对第一个元素执行此操作，使其变成 [2,2,3,4]
// 数组的 偏移量 是数组中任意两个元素之间的 [最大差值] 。
// 返回数组在执行某些操作之后可以拥有的 最小偏移量 。

// 输入：nums = [1,2,3,4]
// 输出：1
// 解释：你可以将数组转换为 [1,2,3,2]，然后转换成 [2,2,3,2]，偏移量是 3 - 2 = 1

// 输入：nums = [4,1,5,20,3]
// 输出：3
// 解释：两次操作后，你可以将数组转换为 [4,2,5,5,3]，偏移量是 5 - 2 = 3

// Solution：贪心 + 优先级队列。
// 1. 先对问题进行转化，先考虑将所有的数化为能到达的最大形式。
//    观察可知，如果原数是奇数 a，则需要 ✖️2转化成偶数 a'。
//    而偶数 a'经过 ➗2又转化成了 a。
//    因此可以先将所有的奇数 ✖️2转化为偶数。
// 2. 要想使得最大差值最小，需要将最大值变小。
//    因此使用一个优先级队列存储最大数，
//    如果最大值是偶数，那么将其 ➗2，能够将最大值变小，使得结果变小。
//    如果最大值是奇数，由于只能对计数进行 ✖️2，会使得最小值变大，
//    如果对其他的偶数变小，又会使得最大差值变大，因此此时 最大值 - 最小值就是答案。
//    算法过程中需要维护最小值。
// 时间复杂度：O(n * logn * log(num_max))，空间复杂度：O(n)。
class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        priority_queue<int, vector<int>, less<int>> pq;
        int min_num = INT_MAX; // 维护最小数
        for (int &i: nums) {
            if (i & 1) {
                i <<= 1;
            }
            pq.push(i);
            min_num = min(min_num, i);
        }
        int ans = INT_MAX;
        while(!pq.empty()) {
            int max_num = pq.top();
            pq.pop();
            ans = min(ans, max_num - min_num);
            if (max_num & 1) {
                break;
            }
            min_num = min(min_num, max_num >> 1);
            pq.push(max_num >> 1);
        }
        return 0;
    }
};
