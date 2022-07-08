#include <../header.h>

// 前序非递归，使用栈
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        if(root == nullptr) return ans;
        stack<TreeNode *> st;
        TreeNode *node = root;
        while(!st.empty() || node != nullptr)
        {
            // 将左子树全部入栈
            while (node != nullptr)
            {
                ans.emplace_back(node->val);
                st.push(node);
                node = node->left;
            }
            node = st.top();
            st.pop();
            // 出栈后直接转右子树，因为之前已经emplace back了
            node = node->right;
        }
        return ans;
    }
};


// 中序非递归，也使用栈，整体结构和前序是相同的，只是emplace_back的位置改变
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        stack<TreeNode *> s;
        while(root != nullptr || !s.empty())
        {
            while(root != nullptr)
            {
                s.push(root);
                root = root->left;
            }
            root = s.top();
            s.pop();
            ans.push_back(root->val);
            root = root->right;
        }
        return ans;
    }
};

// 后序非递归

// Morris遍历（动态线索二叉树）
// 可将树的遍历的空间复杂度降为 O(1)
// 正常的遍历 递归版：递归栈空间 O(logn)，非递归版：栈/队列空间 O(logn)
// 参考：https://juejin.cn/post/7021341254457753631
// https://blog.csdn.net/sinat_42483341/article/details/111301657
// Morris遍历利用叶结点中大量空间指针，以达到节省空间的目的。
// 注意，如果要求不能修改树结构，就不能使用Morris遍历。
// 可以面试用，笔试时以尽快 AC 为准。

// 二叉树遍历的核心问题就是遍历当前节点的左子树后，指针指向的位置为左子树的最右节点，
// 如何返回当前节点并继续访问当前节点的右子树。
// 常规方法是使用栈结构

// 步骤：
// 假设当前结点为 cur，最初 cur = root 根结点。
// 以以下顺序进行遍历：
// 1. cur 无左树，cur = cur.right
// 2. cur 有左树，在原未修改的树中，找到 cur 左树最右边的结点 pre
// ① 若 pre 右指针为空，pre.right = cur, cur = cur.left
// ② 若 pre 右指针指向当前结点 cur（会出现这种情况是因为①的存在），
//        	  pre.right = null, cur = cur.right
// 3. cur 为空，遍历结束。
// Morris 序规律：有左孩子的结点会遍历两次，没有左孩子的结点会遍历一次。
// 和线索二叉树之间的联系：Morris遍历本质上是在遍历的同时进行添加线索和去线索的过程，
// ①即加线索，②即去线索。
// 即寻找某个节点前驱和后继结点。

// Morris 中序遍历。
// 中序遍历 左根右。
// 1情况中添加答案，2②情况也添加答案，代表该结点已经被线索化过。
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> ans;
        TreeNode* cur = root, *pre;
        while (cur) {
            if (cur->left == nullptr) {
                ans.emplace_back(cur->val);
                cur = cur->right;
            } else {
                pre = cur->left;
                // 这里pre->right != cur，相当于防止情况 ② 中越过cur结点
                // 即在未修改的树中找到 pre
                while (pre->right && pre->right != cur) {
                    pre = pre->right;
                }
                if (pre->right == nullptr) { // pre 右子树为空，加线索
                    pre->right = cur;
                    cur = cur->left;
                } else { // pre 右子树不为空，去线索
                    pre->right = nullptr;
                    ans.emplace_back(cur->val); // cur 已经线索化过
                    cur = cur->right;
                }
            }
        }
        return ans;
    }
};

// Morris 先序遍历。
// 先序遍历 根左右。
// 1情况中添加答案，2①情况也添加答案，代表该结点已经被线索化过。
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ans;
        TreeNode* cur = root, *pre;
        while (cur) {
            if (cur->left == nullptr) {
                ans.emplace_back(cur->val);
                cur = cur->right;
            } else {
                pre = cur->left;
                // 这里pre->right != cur，相当于防止情况 ② 中越过cur结点
                // 即在未修改的树中找到 pre
                while (pre->right && pre->right != cur) {
                    pre = pre->right;
                }
                if (pre->right == nullptr) { // pre 右子树为空，加线索
                    ans.emplace_back(cur->val); // cur 已经线索化过
                    pre->right = cur;
                    cur = cur->left;
                } else { // pre 右子树不为空，去线索
                    pre->right = nullptr;
                    cur = cur->right;
                }
            }
        }
        return ans;
    }
};

// Morris 后序遍历。
// 后序遍历 左右根。
// 在2②情况中，代表某结点 cur 已经被线索化过。
// 不是打印 cur，而是将从结点 cur 到遍历到 pre 的路径逆序打印。
// 最终再将 root 逆序打印即可。
class Solution {
    vector<int> ans;
public:
    TreeNode* reverse(TreeNode* node) {
        TreeNode* pre = nullptr, *nxt;
        while (node) {
            nxt = node->right;
            node->right = pre;
            pre = node;
            node = nxt;
        }
        return pre;
    }

    // 这里不需要传引用，node本身也不需要修改
    void printEdge(TreeNode* node) {
        TreeNode* reversed_node = this->reverse(node), *cur = reversed_node;
        while (cur) {
            ans.emplace_back(cur->val);
            cur = cur->right;
        }
        // this->reverse(reversed_node);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* cur = root, *pre;
        while (cur) {
            if (cur->left == nullptr) {
                cur = cur->right;
            } else {
                pre = cur->left;
                // 这里pre->right != cur，相当于防止情况 ② 中越过cur结点
                // 即在未修改的树中找到 pre
                while (pre->right && pre->right != cur) {
                    pre = pre->right;
                }
                if (pre->right == nullptr) { // pre 右子树为空，加线索
                    pre->right = cur;
                    cur = cur->left;
                } else { // pre 右子树不为空，去线索
                    pre->right = nullptr;
                    printEdge(cur->left); // 注意，要在 pre->right赋值为空之后再逆置打印
                    cur = cur->right;
                }
            }
        }
        printEdge(root);
        return ans;
    }
};