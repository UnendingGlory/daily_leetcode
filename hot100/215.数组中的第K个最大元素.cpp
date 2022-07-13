#include "../header.h"

// Solution1: 即从大到小排序后，返回第 k 个数。
// class Solution:
//     def findKthLargest(self, nums: List[int], k: int) -> int:
//         nums.sort(reverse=True)
//         return nums[k]
        
// Solution2: 基于快速排序的 partition 算法。
// 该算法称为快速选择算法。
// 快排中，partition 操作：
// 将数组 a[l...r] 划分为两个子数组 a[l...q-1]、a[q+1...r]，
// 使得 a[l...q-1] 中的每个元素小于等于 a[q]，a[q+1...r]中的每个元素大于等于a[q]。
// 每次 partition 过后，可以发现元素 a[q] 位置被固定，和排序后的位置相同。
// 因此，我们不需要关心排序的结果，只需要 某个元素作为 pivot，
// 刚好被固定在倒数第 k 个位置，即第 n - k 个位置。（或者从大到小，即正数第 k 个位置）。

// 编码时，可以如此操作：
// 对于序列 [l, r]，选择一个枢轴元素 pivot，
// partition 后，左边元素均大于等于 pivot，右边元素均小于等于 pivot。
// 假设 partition 后 pivot 位置为 q。
// 若 k < q，那么对 a[l...q-1] 进行partition。
// 若 k = q，返回 a[q] 作为结果。
// 若 k > q，那么对 a[q+1, r] 进行 partition。
// 时间复杂度分析：最坏情况为先完全递归 n 的序列，再完全递归 n/2的序列... 即 o(n^2)。
// 枢轴元素最好随机选择，可以将平均时间复杂度降低为 O(n)。
// 空间复杂度：递归栈 O(logn)。
class Solution {
public:
    int quickSelect(vector<int>&nums, int l, int r, int k) {
        int q = this->randomPartition(nums, l, r, k);
        if (q == k) {
            return nums[q];
        } else {
            return k < q ? quickSelect(nums, l, q-1, k) : quickSelect(nums, q+1, r, k);
        }
    }

    int randomPartition(vector<int>&nums, int l, int r, int k) {
        // 随机选择一个pivot
        int random_idx = rand() % (r - l + 1) + l;
        int pivot = nums[random_idx];
        swap(nums[random_idx], nums[l]); 
        int x = l, y = r;
        while (x < y) {
            while (x < y && nums[y] <= pivot) --y;
            // 此时 y 位于 nums[y] > pivot的位置
            swap(nums[x], nums[y]);
            while (x < y && nums[x] >= pivot) ++x;
            // 此时 x 位于 nums[x] < pivot的位置
            swap(nums[x], nums[y]);
        }
        // 到这里 x 左边的元素均 >= pivot，右边的元素均 <= pivot
        return x;
    }

    int findKthLargest(vector<int>& nums, int k) {
        // 下标要减一
        return quickSelect(nums, 0, nums.size() - 1, k - 1);
    }
};

// Solution3: 大根堆。
// 不需要进行堆排，只需要建立一个大根堆后，进行 k - 1次删除操作。
// 那么堆顶元素即为答案。
// 时间复杂度：O(nlogk)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        buildHeap(nums);
        // 删除操作，将堆顶元素和末尾元素交换，然后向下调整一次。
        for (int i = 0; i < k - 1; ++i) {
            swap(nums[0], nums[nums.size() - 1]);
            nums.pop_back();
            downAdjust(nums, 0);
        }
        return nums[0];
    }

    // downAdjust 之前只会修改一个位置。
    // 因此位置 i 向下一次调整即可，路径上只需要一次调整。
    void downAdjust(vector<int>& nums, int i) {
         // high 为末端
        int high = nums.size() - 1;
        int j = 2 * i + 1; // 左孩子结点
        while (j <= high) {
            // 如果右孩子更大
            if (j + 1 <= high && nums[j + 1] > nums[j]) { 
                j = j + 1;
            }
            // 子结点比父结点大
            if (nums[j] > nums[i]) {
                swap(nums[j], nums[i]);
                i = j; // 往下走
                j = 2 * i + 1;
            } else {
                break;
            }
        }
    }

    // 建堆，倒着往前数，从第一个非叶结点开始向下调整。
    void buildHeap(vector<int>& nums) {
        int n = nums.size();
        for (int i = (n - 1) / 2; i >= 0; --i) {
            downAdjust(nums, i);
        }
    }
};


int main() {
    vector<int> a {3,2,1,5,6,4};
    int k = 2;
    Solution s;
    int ans = s.findKthLargest(a, k);
    std::cout << ans << std::endl;
    return 0;
}
