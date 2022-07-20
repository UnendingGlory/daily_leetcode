#include "../header.h"
#include "../ListNode.h"

// T1
// a ^ b = c
// 那么b = a ^ c
class Solution1 {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> ans = {first};
        for (int i : encoded) {
            ans.push_back(ans.back() ^ i);
        }
        return ans;
    }
};

// T2
// 交换链表的节点不用真正交换其节点，交换值即可
// 这和链表倒数第k个节点思路是一样的
// 1 2 3 4 5
// 2
// 1 4 3 2 5
class Solution2 {
public:
    ListNode* swapNodes(ListNode* head, int k) {
        // 正数第k个
        auto fir = head, sec = head, p = head;
        for (int i = 1; p; ++i) {
            if (i < k) fir = fir->next;
            // 这和链表倒数第k个节点思路是一样的
            if (i > k) sec = sec->next;
            p = p->next;
        }
        swap(fir->val, sec->val);
        return head;
    }
};

// T3
// 并查集 + 集合差分
// 集合差分采用哈希表实现
class Solution3 {
    vector<int> father;
public:
    int find(int x) {
        int z = x;
        while (x != father[x]) x = father[x];
        while (z != father[z]) {
            int father_z = father[z];
            father[z] = x;
            z = father_z;
        }
        return x;
    }

    void union_ab(int a, int b) {
        int father_a = find(a), father_b = find(b);
        if (father_a != father_b) {
            father[father_a] = father_b;
        }
    }

    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        int n = source.size();
        father.resize(n);
        for (int i = 0; i < n; ++i) father[i] = i;
        for (const auto& pair : allowedSwaps) {
            union_ab(pair[0], pair[1]);
        }
        // root以及对应的集合
        unordered_map<int, vector<int>> um;
        for (int i = 0; i < n; ++i) {
            um[find(i)].push_back(i);
        }
        // 先统计相同的个数
        int same = 0;
        // structured bindings in C++17
        // g++ -std=c++17
        // auto &[root, group] : um
        for (const auto& group : um) {
            // 使用哈希表
            unordered_map<int, int> sc, tc;
            for (int i : group.second) {
                sc[source[i]]++;
                tc[target[i]]++;
            }
            for (const auto& each : tc)
                // 相同则为个数，不同则为0
                same += min(each.second, sc[each.first]);
        }
        // 返回不同的个数
        return n - same;
    }
};

// template <class InputIterator1, class InputIterator2, class OutputIterator>
// OutputIterator set_xxx(InputIterator1 first1, InputIterator1 last1,
//                        InputIterator2 first2, InputIterator2 last2,
//                        OutputIterator result)
// {
//     ...
// }

int main() 
{
    // Solution3 s3;
    // vector<int> source{1, 2, 3, 4}, target{2, 1, 4, 5};
    // vector<vector<int>> allowedSwaps = {{0, 1}, {2, 3}};
    // s3.minimumHammingDistance(source, target, allowedSwaps);
    unordered_multiset<int> S1{1, 3, 5, 7, 9, 11}, S2{1, 1, 2, 3, 5, 8, 13};
    unordered_multiset<int> result;
    // vector<int> res(100);
    set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(result, result.begin()));
    // set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), res.begin());
    for (int i : result) cout << i << " ";
    // for (int i : res) cout << i << " ";
    return 0;
}