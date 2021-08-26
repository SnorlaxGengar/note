#include <iostream>
#include <vector>

using namespace std;

int binary_serach(const vector<int> &a, int val) {
    // XXX: mid用size_t类型的话,在val<0的情况下会出现死循环
    if (a[0] > val) {
        return -1;
    }

    size_t l = 0;
    size_t r = a.size() - 1;

    while (l <= r) {
        size_t mid = l + (r - l) / 2;

        if (a[mid] == val) {
            return mid;

        } else if (a[mid] > val) {
            r = mid - 1;

        } else {
            l = mid + 1;
        }
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    vector<int> a{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = -5; i < 15; ++i) {
        cout << binary_serach(a, i) << endl;
    }

    return 0;
}