#include <bits/stdc++.h>
using namespace std;

// 字典树从根节点开始向下搜寻，路径上的字符被收集成一个个单词
class Trie {
    bool is_end; // 当前是否是一个单词的结尾
    Trie *next[26]; // 该节点往下
public:
    /** Initialize your data structure here. */
    Trie() {
        is_end = false;
        for(int i = 0; i < 26; ++i) next[i] = nullptr;
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *root = this;
        for(int i = 0; i < word.size(); ++i)
        {
            if(root->next[word[i] - 'a'] == nullptr) root->next[word[i] - 'a'] = new Trie();
            root = root->next[word[i] - 'a'];
        }
        root->is_end = true; // 最后一个单词的下一个结点标记为end
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *root = this;
        for(int i = 0; i < word.size(); ++i)
        {
            if(root->next[word[i] - 'a'] == nullptr) return false;
            root = root->next[word[i] - 'a'];
        }
        return root->is_end;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *root = this;
        for(int i = 0; i < prefix.size(); ++i)
        {
            if(root->next[prefix[i] - 'a'] == nullptr) return false;
            root = root->next[prefix[i] - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */