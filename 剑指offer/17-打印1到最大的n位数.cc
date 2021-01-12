#include "../header.h"

// 返回结果保证了最终的结果不会溢出int范围
// 所以可以用简单的数值方法
// 时间复杂度: O(10^n)
class Solution {
public:
    vector<int> printNumbers(int n) {
        // 先得到最大的数即n个9
        int max_number = static_cast<int>(pow(10, n)) - 1;
        vector<int> ans;
        for (int i = 1; i <= max_number; ++i) {
            ans.push_back(i);
        }
        return ans;
    }
};

// 那假设溢出呢？那么返回结果应该是string
// 如果考虑大数问题
// 正常的大数问题数字在字符串中是倒着放的
// 字符串模拟整数加法即可
// 时间复杂度: O(n * 10^n)
// 因为n位字符串加1如果有进位则复杂度为O(n)
class MySolution {
public:
    void increString(string& s) {
        int n = s.size();
        // 从最低位开始
        for (int i = 0; i < n; ++i) {
            if (s[i] != '9') {
                s[i] += 1;
                break;
            } else {
                s[i] = '0';
                // 如果是最高位且为9
                if (i == n - 1) s.push_back('1');
            }
        }
    }

    void printNum(const string s) {
        for (int i = s.size() - 1; i >= 0; --i) {
            printf("%c", s[i]);
        }
    }

    // 这里改成直接打印，注意前缀0的处理
    virtual void printNumbers(int n) {
        string cur = "1";
        int cur_size = 1, last_size = 1;
        while (cur_size <= n) {
            printNum(cur);
            printf(" ");
            increString(cur);
            cur_size = cur.size();
            if (cur_size != last_size) printf("\n");
            last_size = cur_size;
        }
    }
};

// 考虑全排列解决该问题
// 全排列如n = 3，使用基本算法排列出000-999
// 如果递归字符串的第一位是0就不继续递归即可
// 时间复杂度：O(10^n)

// 需要解决的问题：删除前缀0的问题
// 在push_back进temp前进行判断

class RecurSolution : public MySolution {
    string temp;
    vector<string> ans;
public:
    void printRecur(int index, int n) {
        if (index == n) {
            if (!temp.empty()) ans.emplace_back(temp);
            return;
        }
        for (char i = '0'; i <= '9'; ++i) {
            // 不让前缀为0的输入答案
            if (!temp.empty() || (temp.empty() && i != '0')) {
                temp.push_back(i);
            }
            printRecur(index + 1, n);
            if (!temp.empty()) temp.pop_back();
        }
    }

    void printNumbers(int n) override{
        printRecur(0, n);
        cout << ans.size() << "\n";
        for (const auto& s : ans) cout << s << " ";
        cout << "\n";
    }

    void clearAns() {
        ans.clear();
    }
};


int main()
{
    MySolution *pS = new MySolution();
    pS->printNumbers(2);
    pS->printNumbers(3);
    delete pS;
    auto pRe = new RecurSolution();
    pS = pRe;
    pS->printNumbers(2);
    // 要清空否则结果会累积
    pRe->clearAns();
    pS->printNumbers(3);
    delete pS;
    return 0;
}