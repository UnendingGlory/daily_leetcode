/* Sqrt(x)
 * 给定一个浮点数x，求x的开根号的结果，误差不超过1e-6，结果保留小数点后三位数
 * 2 -> 1.414
 * 0.09 -> 0.3
 */
#include <iostream>
#include <vector>
#include <iomanip>  // 浮点数控制函数
using namespace std;


// Solution 1：简单做法，二分法
float sqrt(float x) {
    if (x < 0) return -1; // 负数无结果
    float l = 0, r = x, mid;
    if(x < 1) r = 1; // 负数右边界需要处理，多迭代几次
    while (r - l > 1e-6) {
        mid = l + (r - l) / 2;
        if (mid * mid > x) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return mid;
}


// Solution2：梯度下降法
// 转换思路，即 y = x^2，给定y，求解x
// 可以通过学习的方法来实现
// 以x^2为预测值，y为实际值，目标：最小化L = (y - x^2)^2
// L' = 2*(y - x^2)*(-2x) = -4x(y - x^2)
// 根据梯度下降法，xnew = x - lr * L'
// 而在机器学习中，L一般是loss function，L = f(y, y')
// 然而预测值x和权重w和偏置b有关，因此梯度下降更新的是w和b
// y = w1 * x1 + w2 * x2 + ...
// wnew = w - lr * L'
float sqrtGD(float y) {
    if (y < 0) return -1;
    float lr = 0.001;     //学习率不能太大
    float x = 1, der_l = 1;  // x理论上可以设置为任意值
    // 迭代终止条件，导数绝对值小到某个值
    // 或者abs(x * x - y)小于某个值
    while (abs(der_l) > 1e-4) {
        der_l = -4 * x * (y - x * x);  // l的导数
        // cout << der_l << endl;
        x = x - lr * der_l;
    }
    return x;
}
// 学习率，迭代终止条件，起始点x都是可以调的参数

// Solution3：牛顿迭代法


int main() {
    int n;
    float x;
    // cin >> x;
    // setprecision保留有效数字
    // 需要fixed和setprecision合用保留小数点后几位
    cout << fixed << setprecision(3) << sqrt(2) << endl;
    cout << fixed << setprecision(3) << sqrtGD(2) << endl;

    cout << fixed << setprecision(3) << sqrt(0.09) << endl;
    cout << fixed << setprecision(3) << sqrtGD(0.09) << endl;
    return 0;
}
