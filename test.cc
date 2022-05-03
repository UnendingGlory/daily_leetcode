#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;

template <int n> 
struct Sum{
    enum { sum = Sum<n-1>::sum + n };
};

template <>
struct Sum<1> { // 特化1作为终止条件
    enum{ sum = 1 };
};

class Solution {
public:
    int sumNums(int n) {
        return Sum<n>::sum;
    }
};




int main() {
    Solution s;
    s.sumNums(10);
    return 0;
}
