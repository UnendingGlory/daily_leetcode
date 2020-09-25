#include <bits/stdc++.h>
#include <cassert>
using namespace std;

int n;
const int id()
{
    return 10;
}

void print(const int ia[], size_t size)
{
    #ifndef NDEBUG
        // __func__是编译器定义的一个局部静态变量，用来存放函数名字
        cerr << __func__ << "array size is" << size << endl;
    #endif
}

template<typename T, typename U>
auto add3(T a, U b) -> decltype(a + b)
{
    return a + b;
}

// 这是一个lambda类，而不是函数
auto add4 = [](int a, int b)->int
{
    return a + b;
};

int main(int argc, char **argv)
{
    const string s = "Keep out!";
    vector<int> a{1, 2, 3};
    for(decltype(a.size()) i = 0; i < 0;);
    auto it = a.cbegin();
    const string st = "aaa";
    auto b = const_cast<string &>(st); 
    cout << b << endl;
    int sss[id()];
    cout << add3(5, 6) << endl;
    cout << add4(5, 6) << endl;
    return EXIT_SUCCESS;
}