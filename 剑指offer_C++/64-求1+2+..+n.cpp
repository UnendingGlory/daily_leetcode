#include "header.h"


// 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case
// 等关键字及条件判断语句（A?B:C）。

// Solution1: 第一种好想到的是递归
// 但是一般递归边界需要用到if语句
// 那递归边界如何判断？
// 可以想到使用 短路效应
// 对于语句 n > 1 && sumNums(n - 1)
// 如果n == 1，那么由于短路效应，sumNums(n - 1)便不会生效
class Solution {
    int ans = 0;
public:
    int sumNums(int n) {
        n > 1 && sumNums(n - 1);  // C++中允许这么写
        ans += n;
        return ans;
    }
};


// Solution2：类构造函数，构建n个类，最后一个类即结果
// 类的静态变量 + 静态函数（所有对象共享一个） + 构造函数
class Temp {
public:
    static int x = 0;
    static int sum = 0;
    Temp() {
        ++x;
        sum += x;
    }
    static void clear() {
        x = 0;
        sum = 0;
    }
};

class Solution {
public:
    int sumNums(int n) {
        Temp::clear(); // 需要清零，否则每一个测试用例会用同一个static
        Temp *p = new Temp[n];
        return Temp::sum;
    }
};

// Solution3：虚函数
// 使用两个函数，一个函数代表递归边界f1，一个函数代表相加f2
// 这两个函数使用虚函数的形式来表现
// 将整数n转化为bool变量，如果是true则执行f1，false则执行f2
// 如何转换呢？使用 !n 即可判断n是否是0，如果是0则执行f1, 否则执行f2
class A;
A* array[2];// 创建两个类对对象
class A {
public:
    virtual int sum(int n) {
        return 0;
    }
}

class B: class A {
public:
    virtual int sum(int n) {
        return array[!n]->sum(n-1) + n;
    }
}


class Solution {
public:
    int sumNums(int n) {
        A a;
        B b;
        array[0] = &b;
        array[1] = &a;
        int value = array[0]->sum(n);
        return value;
    }
};


// Solution4：C语言函数指针
// 与方法3类似，只是改用了函数指针数组
// typedef int (*func) (int);
int f1(int n)  {
    return 0;
}

int f2(int n)  {
    static int (*f[2])(int) = {f2, f1}; // 函数指针数组
    return n + f[!n](n-1);
}

class Solution {
public:
    int sumNums(int n) {
        return f2(n);
    }
};

// Solution5：模板元编程，编译阶段进行计算，而不是运行阶段
// 模板元编程的基础为enum hack
// 然而这种解法在题目中无法实现，因为特例化模板要求传入参数时是一个const
// 而题目中n是动态的
template <int n> 
struct Sum{
    enum {sum = Sum<n-1>::sum + n};
};

template <>
struct Sum<1> { // 特化1作为终止条件
    enum{ sum = 1 };
};

class Solution {
public:
    int sumNums(int n) {
        return Sum<n>::sum;  // 会报错，n需要是常量
    }
};
