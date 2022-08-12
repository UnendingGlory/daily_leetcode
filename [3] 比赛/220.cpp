#include "header.h"

// T1
class Solution:
    def reformatNumber(self, number: str) -> str:
        number = number.replace(' ', '')
        number = number.replace('-', '')
        ans = ""
        cnt = 0
        if len(number) < 3:
            return number
        rem = 3 * (len(number) // 3 - 1)
        for i in range(rem):
            ans += number[i]
            cnt += 1
            if cnt % 3 == 0:
                cnt = 0
                ans += "-"
        if len(number) - rem < 4:
            ans += number[rem:]
        elif len(number) - rem == 4:
            ans += number[rem:rem+2]
            ans += "-"
            ans += number[rem+2:]
        elif len(number) - rem == 5:
            ans += number[rem:rem+3]
            ans += "-"
            ans += number[rem+3:]
        return ans

// T2
// 子数组必须包含不同元素
// 最大不重复子序列和
// 前缀和 + 双指针 + 哈希
class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        int n = nums.size(), j = 0;
        unordered_map<int, int> um;
        int ans = 0;
        vector<int> sum(n + 1, 0);
        for (int i = 1; i < n + 1; ++i) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
        for (int i = 0; i < n; ++i) {
            ++um[nums[i]];
            // 保证j-i之间，nums[i]只有一个
            while (j <= i && um[nums[i]] > 1) --um[nums[j++]];
            ans = max(ans, sum[i + 1] - sum[j]);
        }
        return ans;
    }
};

// T3
// 跳跃游戏，最多向前跳k步
// 滑动窗口问题

class Solution1{
public:
class MonotonicQueue {
private:
    deque<int> data;
public:
    void push(int n) {
        while (!data.empty() && data.back() < n) 
            data.pop_back();
        data.push_back(n);
    }
    
    int max() { return data.front(); }
    
    void pop(int n) {
        if (!data.empty() && data.front() == n)
            data.pop_front();
    }
};

public:
int maxSlidingWindow(vector<int>& nums, int k) {
    MonotonicQueue window;
    for (int i = 0; i < nums.size(); i++) {
        if (i < k - 1) { //先填满窗口的前 k - 1
            window.push(nums[i]);
        } else { // 窗口向前滑动
            window.push(nums[i]);
            //res.push_back(window.max());
            window.pop(nums[i - k + 1]);
        }
    }
    return window.max();
}
};

class Solution {
public:
    int maxResult(vector<int>& nums, int k) {
        int ans = nums[0];
        for (int i = 1; i < nums.size(); ) {
            vector<int> temp(nums.begin() + i, nums.begin() + i + k >= nums.end() ? nums.end() : nums.begin() + i + k);
            i += k;
            Solution1 a;
            ans += a.maxSlidingWindow(temp, k);
        }
        return ans;
    }
};

// T4