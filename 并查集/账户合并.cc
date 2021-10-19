#include "header.h"

// 相同名称的有相同邮箱则是同一个，需要合并
// 否则不是
// 并查集对于账户进行合并
// 先遍历每一个邮箱地址，如果邮箱地址出现过
// 则将邮箱地址对应的账户合并

class UnionFindSet {
    vector<int> father;
public:
    UnionFindSet(int n) {
        father.resize(n);
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }

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
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        UnionFindSet ufs(n);
        unordered_map<string, int> email_to_per;
        // 如果该邮箱没出现过则赋值
        // 出现过则将对应账户合并
        for (int i = 0; i < n; ++i) {
            int nn = accounts[i].size();
            // 0位置是名称
            for (int j = 1; j < nn; ++j) {
                string str = accounts[i][j];
                if (email_to_per.find(str) == email_to_per.end()) {
                    email_to_per[str] = i;
                } else {
                    ufs.union_ab(i, email_to_per[str]);
                }
            }
        }

        // 合并答案，还需要排序
        vector<vector<string>> ans;
        unordered_map<int, vector<string>> id_emails;
        for (const auto& [email, id] : email_to_per) {
            id_emails[ufs.find(id)].emplace_back(email);
        }
        for (auto& [id, emails] : id_emails) {
            vector<string> tmp;
            sort(emails.begin(), emails.end());
            // 0位置是名称
            tmp.emplace_back(accounts[id][0]);
            tmp.insert(tmp.end(), emails.begin(), emails.end());
            ans.emplace_back(tmp);
        }
        return ans;
    }
};