class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int lchild = 
    }

    // 位置 i 向下调整
    void downAdjust(vector<int>& nums, int i) {
         // high 为末端
        int high = nums.size() - 1;
        int j = 2 * i + 1; // 左孩子结点
        while (j <= high) {
            
        }
    }

    // 建堆，倒着往前数，从第一个非叶结点开始向下调整。
    void buildHeap(vector<int>& nums) {
        int n = nums.size();
        for (int i = (n-1) / 2; i >= 0; --i) {
            downAdjust(nums, i);
        }
    }
};
