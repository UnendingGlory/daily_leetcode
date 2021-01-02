#include "header.h"
#include <random>

// o(n), 滑动窗口 + 哈希
int has_anagram1(const string &str, const string &aim) {
    if (str.size() < aim.size()) {
        return -1;
    }
    unordered_map<char, int> occur, windows;
    for (int i = 0; i < 26; ++i) { // 使用unordered_map的比较要先预处理字符
        occur['a' + i] = windows['a' + i] = 0;
    }
    for (char c : aim) ++occur[c];
    for (int i = 0; i < aim.size(); ++i) {
        ++windows[str[i]];
    }
    if (windows == occur) return 0;
    for (int i = 1, j = aim.size(); j < str.size(); ++i, ++j) {
        --windows[str[i - 1]], ++windows[str[j]];
        if(windows == occur) return i;
    }
    return -1;
}

// 如果不是anagram一定会有一个负的
// 该方法寻找第一个位置，没有则返回-1
// 即不用哈希表，统计是否有负的就行，用一个变量记录
int has_anagram2(const string& str, const string& aim) {
    int count[26] = {0}, invalid = 0, r = 0, len = aim.size();
    for(const char c: aim) ++count[c - 'a'];
    for (; r < aim.size(); ++r) {
        if (--count[str[r] - 'a'] < 0) {
            ++invalid;
        }
    }
    for (; r < str.size(); ++r) {
        if (invalid == 0) {
            return r - len;
        }
        if (count[str[r] - 'a']-- == 0) {
            ++invalid;
        }
        if (count[str[r - len] - 'a']++ == -1) {
            --invalid;
        }
    }
    // 最后一个window
    return !invalid ? r - len : -1;
}

std::string random_string(size_t len) 
{
    auto randchar = []()->char {
        const string table = "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = table.size() - 1;
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(1, max_index);
        return table[distrib(gen)];
    };
    string ret;
    generate_n(ret.begin(), len, randchar);
    return ret;
}

int main()
{
    int testTimes = 5e4;
    while (testTimes--) {
        string str = random_string(8), aim = random_string(4);
        if (has_anagram1(str, aim) != has_anagram2(str, aim)) {
            std::cout << "Error!\n" << std::endl;
            break;
        }
    }
    std::cout << "Test finished!\n" << std::endl;
    return 0;
}