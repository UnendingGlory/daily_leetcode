#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//中序遍历，修改右指针，将二叉树转换为链表 
class Solution {
    TreeNode* pre;
public:
    // 递归遍历处理，中序遍历的同时将pre的右指针指向自己即可
    void inOrder(TreeNode *root) // pre的值要传给上一层，所以用引用或者全局
    {
        if(root == nullptr) return;
        inOrder(root->left);
        root->left = nullptr; // 当前遍历节点左指针为空
        pre->right = root;
        pre = root;
        inOrder(root->right);
    }

    TreeNode* convertBiNode(TreeNode* root) {
        // 先声明一个节点作为最左下的临时节点给pre初始化，返回时返回其right即可
        TreeNode* ans = new TreeNode(0);
        pre = ans;
        inOrder(root);
        return ans->right;
    }
};

// 非递归版本中序遍历树
// 若结点有左孩子，则左孩子入栈，直至无左孩子
// 取栈顶结点，访问之，然后右孩子入栈
class Solution {
public:
    TreeNode* convertBiNode(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* ans = new TreeNode(0);
        TreeNode* cur = root, *pre = ans;
        while(cur || !s.empty()) // 中序遍历非递归的while判断条件
        {
            while(cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            if(!s.empty())
            {
                cur = s.top();
                s.pop();
                cur->left = nullptr; // 当前左指针为空
                pre->right = cur;
                pre = cur;
                cur = cur->right; // 栈顶结点的右孩子入栈
            }
        }
        return ans->right;
    }
};

int main()
{
    return 0;
}