#include "header.h"

// 给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。
// 任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。
// 在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。
// 然而，两个 相同种类 的任务之间必须有长度为整数 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
// 你需要计算完成所有任务所需要的 最短时间 。

// 输入：tasks = ["A", "A", "A", "B", "B", "B"], n = 2
// 输出：8
// 解释：A -> B -> (待命) -> A -> B -> (待命) -> A -> B
//     在本示例中，两个相同类型任务之间必须间隔长度为 n = 2 的冷却时间，而执行一个任务只需要一个单位时间，所以中间出现了（待命）状态。 


// Solution1: 贪心模拟。
// 完成所有任务的最短时间取决于 [出现次数最多的任务数量]。
// 先挑选剩余执行次数最多的任务，可以在两个该种任务之间穿插进其他任务。
// 将每种任务的剩余执行次数尽可能平均，使得 CPU处于待命的状态尽可能少。

// 贪心模拟：每一时刻模拟，初始时刻为 0。
// 每个任务至少需要一个时间片，因此遍历 tasks数组的长度。
// 二元组 (nextValid, rest)。
// nextValid表示某个任务因为冷却限制可以执行的最早时间，rest表示剩余的执行次数。
// 在 t时刻时，挑选未在冷却中且 剩余执行次数最多的任务。
// 即我们需要找到 nextValid <= t且 rest最大的那个任务。
// 挑选该任务执行后，将该任务的二元组更新为 (time + n + 1, rest - 1)。
// 若 rest == 0，那么遍历时可以忽略。
// 首先采用一个哈希表记录字符和 rest之间的映射关系。
// 再建立 nextValid 和 rest数组。
// 注意点：t时刻若 CPU处于待命状态，所有任务的 nextValid 均 > t。
//        因此每次遍历之前我们可以尝试直接将 time更新为 nextValid中的最小值 min，跳过待命状态。
//        当然，需要保证 min > t才需要更新。
// 时间复杂度：O(tasks * m)，m为任务种类数；空间复杂度：O(m)；
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for (char c: tasks) {
            freq[c]++;
        }
        vector<int> nextValid, rest;
        for (auto kv: freq) {
            nextValid.emplace_back(1);
            rest.emplace_back(kv.second);
        }
        int time = 0;
        // 每个任务至少需要一个时间片，某个task更新时间
        for (int i = 0; i < tasks.size(); ++i) {
            ++time;

            // 尝试跳过待命状态
            int minNextValid = INT_MAX;
            for (int j = 0; j < nextValid.size(); ++j) { // freq 和 nextValid、rest 大小相等
                if (rest[j] > 0) {
                    minNextValid = min(minNextValid, nextValid[j]);
                }
            }
            time = max(time, minNextValid);

            // 挑选中的任务下标
            int picked = -1;
            for (int j = 0; j < rest.size(); ++j) {
                if (rest[j] && nextValid[j] <= time) {
                    if (picked == -1 || rest[j] > rest[picked]) {
                        picked = j;
                    }
                }
            }
            // 更新选中的任务状态
            nextValid[picked] = time + n + 1;
            --rest[picked];
        }
        return time;
    }
};

// Solution2: 桶子构造。
// https://leetcode.cn/problems/task-scheduler/solution/ren-wu-diao-du-qi-by-leetcode-solution-ur9w/
// 我们可以建立大小为 n + 1 的桶子，个数为任务数量最多的那个任务。
// 假如等待时间为 2，A为最多的任务，数量为 6，桶大小为 3。

// 情况1：没有其他任务
// 桶1：A 无 无
// 桶2：A 无 无
// 桶3：A 无 无
// 桶4：A 无 无
// 桶5：A 无 无
// 桶6：A 无 无
// 完成的最少时间为 (6 - 1) * 3 + 1 = 16

// 情况2：添加一些其他任务
// 桶1：A B C
// 桶2：A B C
// 桶3：A B 无
// 桶4：A B 无
// 桶5：A B 无
// 桶6：A B 无
// 完成的最少时间为 (6 - 1) * 3 + 2 = 17
// 前面两种情况，总结起来：
// ans1 = (桶个数 - 1) * (n + 1) + 最后一个桶的任务数

// 情况3：任务数非常紧密时
// 桶1：A B C
// 桶2：A B C
// 桶3：A B D
// 桶4：A B D
// 桶5：A B D
// 桶6：A B 无
// 假设此时还需要执行两次任务 F，怎么办呢？
// 我们可以临时拓展某些桶子的大小，插进任务F。
// 桶1：A B C F
// 桶2：A B C F
// 桶3：A B D
// 桶4：A B D
// 桶5：A B D
// 桶6：A B 无
// 此时执行任务所需时间，就是任务的数量。
// ans2 = tasks.size()

// 综上所述，ans = min(ans1, ans2)
// 时间复杂度：O(tasks)，空间复杂度：O(m)，m为任务种类数。
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> freq;
        for (char c: tasks) {
            freq[c]++;
        }

        // 先找寻桶个数，即最多数量任务数
        int maxExec = -1;
        for (auto kv: freq) {
            maxExec = max(maxExec, kv.second);
        }
        
        // 计算最后一桶剩余任务数，即任务数量并列最多的任务有多少个
        int remain = 0;
        for (auto kv: freq) {
            if (maxExec == kv.second) {
                ++remain;
            }
        }

        int ans = (maxExec - 1) * (n + 1) + remain;
        return max(ans, (int)tasks.size());
    }
};
