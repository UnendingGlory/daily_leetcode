#include <bits/stdc++.h>
using namespace std;

class Trie
{
public:
    bool is_end;
    Trie *next[26];
    Trie()
    {
        is_end = false;
        for(int i = 0; i < 26; ++i) next[i] = nullptr;
    }

    void insert(const string& word) // 前缀树的插入操作
    {
        Trie *t = this;
        for(auto c : word)
        {
            if(t->next[c - 'a'] == nullptr) t->next[c - 'a'] = new Trie();
            t = t->next[c - 'a'];
        }
        t->is_end = true;
    }

    bool search(const string &word, Trie *root)
    {
        Trie *t = root;
        for(int i = 0; i < word.size(); ++i)
        {
            if(word[i] == '.')
            {
                for(int j = 0; j < 26; ++j)
                {
                    if(t->next[j] != nullptr && search(word.substr(i + 1), t->next[j]))
                        return true;
                }
                return false; // next均为nullptr
            }
            else if(t->next[word[i] - 'a'] == nullptr) return false;
            else t = t->next[word[i] - 'a']; // 存在则往下搜索
        }
        return t->is_end; // 返回标记位
    }
};

class WordDictionary {
    Trie *root;
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new Trie();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        root->insert(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return root->search(word, root);
    } 
};