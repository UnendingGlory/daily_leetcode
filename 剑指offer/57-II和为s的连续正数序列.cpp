#include "header.h"


// Solution1: 暴力，枚举的下界为1，由于子序列至少有两个数，所以上界为(target-1) / 2
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ans;
        int limit = (target - 1) / 2, sum;
        for (int i = 1; i <= limit; ++i) {
            sum = 0;
            vector<int> vec;
            for (int j = i; ;++j) {
                sum += j;
                vec.emplace_back(j);
                if (sum > target) {
                    sum = 0;
                    break;
                } else if (sum == target) {
                    ans.emplace_back(vec);
                }
            }
        }
        return ans;
    }
};


// Solution2: 对方法1求解的方法优化
// 如果知道加和的最小数为x，最大数为y，那么和为(x + y) * (y - x + 1) / 2
// 给定下界x, x范围：[1, (target-1) / 2]
// 即有公式(x + y) * (y - x + 1) / 2 = target，求解y
// y^2 + y - x^2 + x - 2target = 0;
// a = 1, b = 1, c = - x^2 + x - 2target
// delta = b^2 - 4ac = 1 - 4c
// delta <= 0时无解
// y1 = (-1 + sqrt(delta)) / 2, y2 < 0不必考虑

// 如果是根则需要满足两个条件
// 1. delta开根是整数  t = (int)sqrt(delta + 0.5) 
//    若t * t == delta，则delta开根是整数
// 2. y的分子是偶数

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ans;
        vector<int> vec;
        int limit = (target - 1) / 2, delta;
        int c;
        for (int x = 1; x <= limit; ++i) {
            c = -x*x + x - 2*target;
            delta = 1 - 4*c;
            
            if (delta <= 0) continue;

            int t = (int)sqrt(delta + 0.5);
            if (t * t == delta && (t - 1) % 2) == 0) {
                int y1 = (-1 + sqrt(delta)) / 2;
                if (x < y) {
                    vec.clear();
                    for (int i = 1; i <= y; ++i) {
                        vec.emplace_back(i);
                    }
                    ans.emplace_back(vec);
                }
            }
        }
        return ans;
    }
};


// Solution3: 双指针法
// 两个指针l, r分别指向首尾
// 一个指针从1开始，一个指针从2
// 如果知道加和的最小数为l，最大数为r，那么和为(l + r) * (r - l + 1) / 2
// 如果和sum > target，则++l
// 如果和sum == target，则++l
// 如果和sum < target，则++r
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> ans;
        vector<int> vec;
        int l = 1, r = 2;
        while (l < r) {
            int sum = (l + r) * (r - l + 1) / 2;
            if (sum == target) {
                vec.clear();
                for (int i = l; i <= r; ++i) {
                    vec.emplace_back(i);
                }
                ans.emplace_back(vec);
                ++l;
            } else if (sum > target) {
                ++l;
            } else {
                ++r;
            }
        }
        return ans;
    }
};