# include "header.h"
// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
// 注意，可以重复使用字典中的单词。

// 输入：s = "leetcode", wordDict = ["leet", "code"]
// 输出：true

// Solution1: 动态规划。
// dp[i] 表示 字符串 s 前 i 个字符串 s[0..i-1] 是否能被拆分。
// 从前往后计算转移方程，枚举 s[0...i-1] 中的分割点j
// 观察 s[0...j-1] 和 s[j...i-1] 是否均合法。
// 由于 dp[j] 已知，因此只需要判断 s[j...i-1] 是否合法即可。
// 转移方程：dp[i] = dp[j] && check(s[j...i-1])
//         check 表示 s[j...i-1] 是否在字典中
//         检查是否出现在字典中可以直接使用 哈希表 来快速判断。
// 边界条件：dp[0] = true, 表示空串合法。
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto wordDictSet = unordered_set <string> ();
        for (auto word: wordDict) {
            wordDictSet.insert(word);
        }
        auto dp = vector<bool> (s.size() + 1);
        dp[0] = true;
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordDictSet.find(s.substr(j, i - j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.size()];
    }
};

// Solution2：字典树中 dfs深搜。
// 字典树中存储 wordDict，形成一个字典树 Trie。
// 然后对于字符串 s，在字典树中进行dfs。
// dfs(s, i) 代表 s[i:] 字符串是否在字典树中。
// 从前往后递归，从后往前回溯。
struct TrieNode {
    TrieNode* next[26];
    bool isEnd;
    TrieNode()
    {
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
        isEnd = false;
    }
};
class Solution {
    TrieNode* root;
    int failMemo[301]; // 记录dfs中失败时对应的s中的index
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        root = new TrieNode();
        // 建树
        for (auto& word : wordDict)
        {
            TrieNode* p = root;
            for (auto& ch : word)
            {
                if (p->next[ch - 'a'] == nullptr)
                    p->next[ch - 'a'] = new TrieNode();
                p = p->next[ch - 'a'];                   
            }
            p->isEnd = true;            
        }
        return dfs(s, 0);
    }
    bool dfs(string& s, int startPos)
    {
        if (failMemo[startPos] == 1) return false;        
        if (startPos == s.size()) return true;
        TrieNode* p = root;        
        for (int i = startPos; i < s.size(); i++)
        {
            if (p->next[s[i] - 'a'] != nullptr)
            {
                p = p->next[s[i] - 'a'];
                if (p->isEnd == true && dfs(s, i+1))
                    return true;   
            }
            else break;   
        }
        failMemo[startPos] = 1;
        return false;
    }
};