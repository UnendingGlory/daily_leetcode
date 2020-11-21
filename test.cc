#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <algorithm>
#include <forward_list>
#include <map>

using std::vector;

class Foo
{
    int v1;
    double v2;
};

template <typename T>
class Foo2 : public Foo
{

};
void fun2(int &&a)
{
    a = 20;
}

void fun(int &a)
{
    a = 10;
    fun2(std::move(a));
}


int main()
{
    std::list<int> ll;
    for(int i = 0; i < 10; ++i)
        ll.push_back(i);
    ll.sort([](int a, int b){
        return a > b;
    });
    for(auto &i : ll)
        std::cout << i;
    return 0;
}