#include <bits/stdc++.h>
using namespace std;

// 即寻找所有不是其他单词后缀的单词
// 使用前缀树，先将单词倒转，然后建树，最后遍历之即可

// 节点
class Trie
{
    bool is_end;
    string word;
    Trie *next[26];
public:
    Trie()
    {
        is_end = false;
        for(int i = 0; i < 26; ++i) next[i] = nullptr;
    }

    void insert(string s)
    {
        Trie *root = this;
        for(char i : s)
        {
            if(root->next[i - 'a'] == nullptr) root->next[i - 'a'] = new Trie();
            root = root->next[i - 'a'];
        }
        root->is_end = true; // 该节点是一个单词的结尾
        root->word = s; // 存储该单词
    }

    // DFS递归遍历字典树并得到结果
    void traverse(Trie *root, int &ans)
    {
        bool flag = true; // 是叶节点
        for(int i = 0; i < 26; ++i)
        {
            if(root->next[i] != nullptr)
            {
                traverse(root->next[i], ans);
                flag = false;
            }
        }
        if(flag) ans += (root->word.size() + 1); // 是叶子节点多加一个'#'
    }
};

class Solution {
    Trie *root;
public:
    int minimumLengthEncoding(vector<string>& words) {
        root = new Trie();
        int ans = 0;
        for(auto i : words)
        {
            reverse(i.begin(), i.end());
            root->insert(i);
        }
        root->traverse(root, ans);
        return ans;
    }
};

int main()
{
    return 0;

}
