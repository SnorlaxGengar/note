#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

double bin_sqrt(double val) {
    double l {1}, r {val};
    if (val < l) {
        swap(l, r);
    }
    double mid = l + (r - l)/2;
    while (abs(val - mid*mid) > 0.0000001) {
        if (val > mid*mid) {
            l = mid;
        } else {
            r = mid;
        }
        mid = l + (r - l)/2;
    }
    return mid;
}

int main(int argc, char const *argv[])
{
    vector<double> nums {0.09, 0.25, 1, 9, 15, 64};
    transform(nums.begin(), nums.end(), nums.begin(), bin_sqrt);
    copy(nums.begin(), nums.end(), ostream_iterator<double>(cout, ","));
    cout << endl;
    return 0;
}