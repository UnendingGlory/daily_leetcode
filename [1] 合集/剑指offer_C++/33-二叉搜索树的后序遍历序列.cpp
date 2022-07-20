#include "header.h"


// 判断数组是不是二叉搜索树的后序遍历结果
// 二叉搜索树：左子树小于根节点，右子树大于根节点

// 递归判断
class Solution {
public:
    bool recur(vector<int>& nums, int l, int r) {
      if (l >= r) return true;

      int root = nums[r]; // 根结点的值
      int i = r - 1; // 往前找第一个小于根结点的值
      while (i >= 0 && nums[i] > root) --i;
      // <= i 的是左子树范围, [i+1, r-1]的是右子树
      int mid = i;
      while (i >= 0 && nums[i] < root) --i;
      if (i >= 0) return false; // 如果是二叉搜索树，i = -1
      return recur(nums, l, mid) && recur(nums, mid + 1, r - 1);
    }

    bool verifyPostorder(vector<int>& postorder) {
      int n = postorder.size();
      if (n == 0) return false;
      return recur(postorder, 0, n - 1);
    }
};
