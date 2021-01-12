#include "../header.h"
// 三种方法

// 回溯法
class Solution {
public:
    bool isMatch(string s, string p) {

    }
};

// 动态规划法


// 使用编译原理相关知识
// 对于每一个pattern构造一个DFA
// 判断s是否能走到自动机的终点
// 如pattern: ab.*d
//                 / . \  
//     a        b  \   /  $        d
// 0 -----> 1 -----> 2  -----> 3 -----> 4
// 0是开始状态，4是结束状态，$代表空（因为*可以匹配0次）

// 如pattern: aba*c
//                 / a \  
//     a        b  \   /  $         c
// 0 -----> 1 -----> 2  -----> 3 -----> 4

// 构建完成后再通过循环或者递归的方式对s进行判断

class Solution {
    // 由于该题中一个状态下不会转移到多个状态
    // 所以直接用vector下标表示，而不用map
    // 下标为当前状态，char为输出，int为下一状态
    vector<pair<char, int>> table;
public:
    void construct_dfa(const string& s) {

    }

    bool isMatch(string s, string p) {
        
    }
};