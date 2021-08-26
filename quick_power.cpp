#include <iostream>

using namespace std;

using my_type = unsigned long long;
// 2^5, 5=0b1001
// =2^4*2^1
my_type quick_power(my_type val, unsigned n) {
    if (n == 0) {return 1;}
    my_type result {1};
    my_type tmp {val};
    // 按位遍历指数,将对应位的结果累乘
    while (n) {
        // 如果指数对应的位为1,则将当前的结果乘入结果
        if (n&1) {
            result *= tmp;
        }
        tmp = tmp*tmp;
        n >>= 1;
    }

    return result;
}

int main(int argc, char const *argv[])
{
    for (unsigned n = 0; n < 100; ++n) {
        my_type result = quick_power(2, n);
        cout << "2^" << n << "=" << result << endl;
        if (result == 0) {
            break;
        }
    }
    return 0;
}