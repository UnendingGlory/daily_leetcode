// 序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
// 设计一个算法实现二叉树的序列化和反序列化。
# include "header.h"

// Solution：要将二叉树编码为字符串，同时能够通过字符串解码得到二叉树。
// 编码：直接对二叉树中的值进行先序遍历即可，将值用分隔符 ',' 分开，遇到空结点时要解析为 None。
// 解码：通过带空结点的确定的先序序列进行解码 dfs 建树，遇到空节点返回空，先构建左子树，再构建右子树。
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string ret;
        dfs_serial(root, ret);
        std::cout << ret << std::endl;
        return ret;
    }

    void dfs_serial(TreeNode* root, string &str) {
        if (root == nullptr) {
            str += "None,";
            return;
        }
        str += to_string(root->val) + ",";
        dfs_serial(root->left, str);
        dfs_serial(root->right, str);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        vector<string> nodes; // vector + 下标模拟即可
        string tmp;
        for (int i = 0; i < data.size(); ++i) {
            if (data[i] == ',') {
                nodes.emplace_back(tmp);
                tmp.clear();
                continue;
            }
            tmp.push_back(data[i]);
        }
        int index = 0;
        return dfs_deserial(nodes, index);
    }

    TreeNode* dfs_deserial(vector<string> &nodes, int &i) {
        if (nodes[i] == "None") {
            i += 1;
            return nullptr;
        }
        TreeNode *root = new TreeNode(stoi(nodes[i]));
        i += 1;
        root->left = dfs_deserial(nodes, i);
        root->right = dfs_deserial(nodes, i);
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

