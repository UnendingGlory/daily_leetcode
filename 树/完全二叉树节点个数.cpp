#include "../header.h"
#include "binary_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
//
//  1
// 2 3
// bug
class Solution {
public:

    int countNodes(TreeNode* root) {
		int h = 0;
		auto p = root;
		while(p->left != nullptr)
			p = p->left, ++h;
		
		// h = 2
		// 2-3
		// from 1+2+...+2^(n - 2) + 1 = 2^(h - 1) to 2^h - 1
		// 前缀1，100-111
		int left = 1 << h, right = (1 << (h + 1)) - 1;
		while(left < right)
		{
			auto mid = (left + right) >> 1;
			int assis = 1 << (h - 1);
			p = root;
			while(p && assis)
			{
				// 左边是0，右边是1
				if(assis & mid) p = p->right;
				else p = p->left;
				assis >>= 1;
			}
			if(p == nullptr) right = mid - 1;
			else left = mid;
		}
		return left;
    }
};

// right
class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int level = 0;
        TreeNode* node = root;
        while (node->left != nullptr) {
            level++;
            node = node->left;
        }
        int low = 1 << level, high = (1 << (level + 1)) - 1;
        while (low < high) {
            int mid = (high - low + 1) / 2 + low;
            if (exists(root, level, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        return low;
    }

    bool exists(TreeNode* root, int level, int k) {
        int bits = 1 << (level - 1);
        TreeNode* node = root;
        while (node != nullptr && bits > 0) {
            if (!(bits & k)) {
                node = node->left;
            } else {
                node = node->right;
            }
            bits >>= 1;
        }
        return node != nullptr;
    }
};