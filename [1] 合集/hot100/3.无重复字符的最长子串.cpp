// 滑窗的逻辑插入要根据不同题目而灵活变化。

// Solution1：基本滑窗
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 0, r = 0, ans = 0;
        unordered_set<int> hashtable;
        while (r < s.size()) {
            while (hashtable.find(s[r]) != hashtable.end()) { // 如果有重复字符
                hashtable.erase(s[l]);
                ++l;
            }
            ans = max(ans, r - l + 1);
            hashtable.insert(s[r]);
            ++r;
        }
        return ans;
    }
};

// Solution2：优化
// 如果有重复字符，l 不需要每次都前进一步。
// 可以直接前进到 s[r]字符对应的索引。
// 滑窗过程中记录每一个字符的索引即可。
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int l = 0, r = 0, ans = 0;
        unordered_map<char, int> index;
        while (r < s.size()) {
            // 如果有重复字符且左侧小于记录的索引
            while (index.find(s[r]) != index.end() && l <= index[s[r]]) {
                l = index[s[r]] + 1; // 跳到下一个索引
            }
            ans = max(ans, r - l + 1);
            index[s[r]] = r; // 同值会覆盖
            ++r;
        }
        return ans;
    }
};