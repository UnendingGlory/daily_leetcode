#include "../header.h"
// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
// 算法的时间复杂度必须低于 O(nlogn)。

// 可以先使用哈希表进行统计，然后在哈希表的 [出现次数数组] 中求前K个最大的。
// 与第 215题非常类似，只是 215题求的是第 K个大的，该题求前 K个最大的，解法也类似。

// Solution1：堆，建立一个小顶堆，然后遍历 [出现次数数组]。
// 解法类似于题目 [数据流中前K个元素] 的解法。
// 遍历到当前元素时，
// 1. 如果堆的个数小于 K，那么将 [对应的原数] 直接插入堆中。
// 2. 如果堆的个数大于 K，那么需要比较堆顶的元素和 当前元素大小。
//    若当前元素更大，则弹出堆顶，将 [对应的原数] 插入堆中。
//    否则，说明当前元素比堆顶中的都小，直接跳过。

// 优先用优先级队列，也可以手动建堆。
// 时间复杂度：O(nlogk)
class Solution {
public:
    unordered_map<int, int> occur; // 原数 -> 出现次数
    vector<int> topKFrequent(vector<int>& nums, int k) {
        for (int num: nums) {
            occur[num]++;
        }
        // 原数是唯一的，但是出现次数不一定唯一。
        // 即需要原数和出现次数的映射关系，又需要对出现次数进行比较。
        // 即对值进行比较，需要使用自定义比较函数，小顶堆的比较是大于。
        // 但是如果对键进行比较使用标准库的模板，那么是 less<...>
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
        for (auto &occ: occur) {
            if (pq.size() < k) {
                pq.emplace(occ.first, occ.second);
            } else {
                if (occ.second > pq.top().second) {
                    pq.pop();
                    pq.emplace(occ.first, occ.second);
                }
            }
        }
        vector<int> ans;
        while (!pq.empty()) {
            ans.emplace_back(pq.top().first);
            pq.pop();
        }
        return ans;
    }

    // 优先级队列比较 采用结构体重载括号的方式
    struct cmp {
        bool operator() (pair<int, int> &a, pair<int, int> &b) const {
            return a.second > b.second;
        }
    };
};

// Solution2：基于快速排序算法。
// 由于快排的一次 partition操作可以使得枢轴左侧元素均 [大于等于] 枢轴元素，枢轴右侧元素均 [小于] 枢轴元素。
// 因此对于 arr[l...r]，一次 partition后，
// arr[l...q-1] 均大于等于 arr[q]，arr[q+1...r] 均小于枢轴元素。
// 此时，我们根据 k与左侧子数组的长度 (q - l) 关系进行判断：
// 1. 如果 k <= q - l，则 arr前 k大的值，就是 arr[l...q-1]前 k大的值。
// 2. 如果 k > q - l，则 arr前 k大的值，等于 arr[l...q]全部元素 + arr[q+1...r] 中前 k - (q - l - 1)大的值。
// 对于此题，对 [出现次数数组] 进行该快速排序算法即可。

// 时间复杂度：O(n)
// 原版快排时间复杂度为 O(nlogn)，而我们只需要选择一个分支进行递归，时间复杂度降为 O(n)。

// 注意，编码时，由于需要映射回原数，因此也需要使用 pair，存储 值 -> 出现次数。
class Solution {
public:
    vector<int> ans;
    unordered_map<int, int> occurrence;
    vector<int> topKFrequent(vector<int>& nums, int k) {
        for (int num: nums) occurrence[num]++;
        vector<pair<int, int>> occur;
        for (auto &kv: occurrence) {
            occur.emplace_back(kv);
        }
        quickSort(occur, 0, occur.size() - 1, k);
        return ans;
    }

    // 在 occur数组中寻找 前k大的值
    void quickSort(vector<pair<int, int>> &occur, int l, int r, int k) {
        int random_idx = rand() % (r - l + 1) + l;
        int pivot = occur[random_idx].second;
        swap(occur[l], occur[random_idx]); // 要记得交换位置
        int x = l, y = r;
        while (x < y) { // 从大到小排序
            while (x < y && occur[y].second < pivot) --y;
            swap(occur[x], occur[y]);
            while (x < y && occur[x].second >= pivot) ++x;
            swap(occur[x], occur[y]);
        }
        if (k <= x - l) {
            quickSort(occur, l, x - 1, k);
        } else {
            for (int i = l; i <= x; ++i) {
                ans.emplace_back(occur[i].first);
            }
            if (k - (x + 1 - l) > 0) { // 如果剩余元素大于 0
                quickSort(occur, x + 1, r, k - (x + 1 - l));
            }
        }
    }
};