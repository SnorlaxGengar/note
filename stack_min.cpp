#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

using namespace std;

class MinStack {
public:
    void push(int val) {
        m_data.push_back(val);
        if (m_min.empty()) {
            m_min.push_back(val);
        } else {
            if (val <= m_min.back()) {
                m_min.push_back(val);
            }
        }
    }

    void pop() {
        if (m_data.empty()) {
            return;
        }

        int top = m_data.back();
        m_data.pop_back();
        if (top == m_min.back()) {
            m_min.pop_back();
        }
    }

    bool getMin(int& val) const {
        if (m_min.empty()) {
            return false;
        }

        val = m_min.back();
        return true;
    }

    void print() const {
        cout << "data:";
        copy(m_data.begin(), m_data.end(), ostream_iterator<int>(cout, ","));
        cout << endl;
        cout << "min:";
        copy(m_min.begin(), m_min.end(), ostream_iterator<int>(cout, ","));
        cout << endl;
    }
private:
    vector<int> m_data;
    vector<int> m_min;
};

int main(int argc, char const *argv[]) {
    MinStack stack;
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};
    uniform_int_distribution<int> dist {1, 10};
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
    vector<int> a(10);
    generate(a.begin(), a.end(), gen);
    for (auto v: a) {
        stack.push(v);
    }
    stack.print();
    int minVal {0};
    if (stack.getMin(minVal)) {
        cout << "min in stack:" << minVal << endl;
    }
    int len = a.size();
    while (len--) {
        cout << string(80, '#') << endl;
        stack.pop();
        stack.print();
    }
    return 0;
}