#include "header.h"

// 不管用什么算法均可，只要能将树转化成字符串
// 再将字符串解码成树结构


// Solution: 先序遍历保存二叉树的值
// 为了保证树的唯一性，在遇到空节点的时候记录为None
// 节点之间使用逗号作为分隔符
// 解码时，使用数组保存串用逗号分割后的结果，递归建树即可

class Codec {
public:
    void preorder(TreeNode* root, string &str) {
        if (root == nullptr) {
            str += "None,";
            return;
        }
        str += to_string(root->val) + ",";
        preorder(root->left, str);
        preorder(root->right, str);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        // 先序遍历这个二叉树
        string str;
        preorder(root, str);
        return str;
    }

    TreeNode* build_tree(vector<string> &nodes, int &idx) {
        if (nodes[idx] == "None" || idx >= nodes.size()) {
            ++idx;
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(nodes[idx]));
        ++idx;
        root->left = build_tree(nodes, idx);
        root->right = build_tree(nodes, idx);
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> nodes;
        string node;
        for (char &c: data) {
            if (c == ',') {
                nodes.emplace_back(node);
                node.clear();
            } else {
                node.push_back(c);
            }
        }
        int idx = 0; 
        TreeNode * root = build_tree(nodes, idx);
        return root;
    }
};
