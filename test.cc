#include <iostream>
#include <string>
#include <vector>
#include <array>
using namespace std;

void array_func(const size_t& count) {
    const size_t c = 10;
    array<int, c> arr;
    array<int, count> arr2;
}


int main() {
    array_func(1);
    return 0;
}
