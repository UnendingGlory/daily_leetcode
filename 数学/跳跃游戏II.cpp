#include <bits/stdc++.h>
using namespace std;

// 跳跃到最后一位需要的最少次数，贪心算法,o(n)
class Solution {
public:
    int jump(vector<int>& nums) {
        int maxPos = 0, n = nums.size(), end = 0, step = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (maxPos >= i) { // 即在区间[i, maxPos]中寻找
                maxPos = max(maxPos, i + nums[i]);
                if (i == end) {
                    end = maxPos;
                    ++step;
                }
            }
        }
        return step;
    }
};

int main()
{

    return 0;
}