#include "header.h"

// 给定一个变量对数组 equation 和 一个实数值数组 values作为已知条件。
// equations[i] = [Ai, Bi]
// 再给定一个数组 queries作为问题，其中 queries[j] = [Cj, Dj]，根据已知条件求 Cj / Dj = ?
// 如果不存在答案，返回 -1。

// 示例：
// 输入：equations = [["a","b"],["b","c"]], values = [2.0, 3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
// 输出：[6.00000, 0.50000, -1.00000, 1.00000, -1.00000]

// Solution: 并查集（有向图）。
// 将有倍数关系的字母放在一个集合中。
// 查询时，如果两个字母在一个集合中，固定一个转化的基底，总能在 O(1)的事件复杂度内得到结果。
//        如果两个字母不在一个集合中，那么返回 -1。
//        如果至少有一个字母不在所有集合中，那么也返回 -1。

// 实例：a / b = 2, b / c = 3; 即 a = 2b, b = 3c;
// 求 a / c = ? a 和 c在一个集合中，如果固定基底为c，那么 a = 2b = 2 * 3c = 6c -> a / c = 6;
// 求 b / a = ? b 和 a在一个集合中，如果固定基底为c，那么 b = 3c, a = 6c -> b / a = 0.5

// 建立并查集时，将 equations中的字母建立边关系（将分子作为分母的父结点），而 values作为边的权值。
// 比如 a / b = 2, 即 a ---> b，且边权为 2。
// 由于带权，有以下几点需要注意：
// 1. find 时的路径压缩，路径压缩将集合中所有结点直接连接到父结点，在本题中，父结点刚好可以作为基底。
//    由于边权是带值的，那么在路径压缩时如何处理边权呢？
//        2.0    3.0    4.0
//      a ---> b ---> c ---> d
//    路径压缩时，不能从 a开始压缩，要从 c开始压缩，c -> d为 4.0，b -> d为 b -> c -> d 即 3.0 * 4.0 = 12
//    a ---> d 为 a --> b ---> d 即 2.0 * 12 = 24.0
// 2. union 时的权值处理。
//    首先，由于进行了路径压缩，因此 union(a, b)时，a, b所在的树高度不会超过2。
//    假设 a -> b 为 2.0，c -> d 为 4.0，假设遍历到当前为 a / c = 4.0，
//    那么我们需要合并 a的父结点 b和 c的父结点 d，同时修改权值。
//    b    d    如左图，已知该关系，我们需要将 b指向 d，权值假设为 x。
//    ^    ^    a经过 c可以到达d，即 a = 4c = 4 * 4d = 16d
//   2|    |4   a经过 b也可以到达d，即 a = 2b = 2 * xd = 2xd
//    a -> c    则 16 = 2x => x = 8
//      4
//    即 x = value[i] * weight[c] / weight[a]。

// 实际编码时，需要将字符串映射为唯一的 id。
class UnionFindSet {
public:
    vector<int> father; // 结点 i指向的父结点
    vector<double> weight; // 
    UnionFindSet(int n) { // 构造函数
        father.resize(n);
        weight.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
            weight[i] = 1.0; // a / a = 1.0
        }
    }

    // find同时路径压缩，这里的路径压缩要从父结点往下，而不是
    // 迭代式的从下往上，因此需要采用递归。
    int find(int x) {
        if (x == father[x]) return x; // 递归边界
        int origin = father[x];
        father[x] = find(father[x]);
        weight[x] *= weight[origin]; // 乘以直接父结点指向根结点的权值
        return father[x];
    }

    void union_ab(int a, int b, double value) {
        int father_a = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
            weight[father_a] = value * weight[b] / weight[a];
        }
    }

    // 查找两个结点的数值关系，即 a / b，若不在一个集合中返回 -1。
    double fraction(int a, int b) {
        int father_a = find(a), father_b = find(b);
        if (father_a == father_b) {
            return weight[a] / weight[b];
        } else {
            return -1;
        }
    }
};


class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 第1步，将每一个字符串映射为 id。
        int n = equations.size();
        UnionFindSet ufs(2 * n); // 由于每个equation有两个字母，因此最多 2n个 id。
        unordered_map<string, int> s2id; // 字符串到id的映射。
        int id = 0;
        string numerator, denominator;
        for (int i = 0; i < n; ++i) {
            numerator = equations[i][0], denominator = equations[i][1];
            if (s2id.find(numerator) == s2id.end()) {
                s2id[numerator] = id++;
            }
            if (s2id.find(denominator) == s2id.end()) {
                s2id[denominator] = id++;
            }
            ufs.union_ab(s2id[numerator], s2id[denominator], values[i]);
        }
        // 第2步，查询。查询时如果不在映射id集合中也要返回-1。
        vector<double> ans;
        for (int i = 0; i < queries.size(); ++i) {
            numerator = queries[i][0], denominator = queries[i][1];
            if (s2id.find(numerator) == s2id.end() || s2id.find(denominator) == s2id.end()) {
                ans.emplace_back(-1);
            } else {
                ans.emplace_back(ufs.fraction(s2id[numerator], s2id[denominator]));
            }
        }
        return ans;
    }
};
