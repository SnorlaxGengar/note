#include <iostream>
#include <sys/stat.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

using namespace std;

int main(int argc, char const *argv[]) {
    atomic_int status {0};
    mutex lock_status;
    condition_variable cv;
    mutex lock_exit;

    for (char ch = 'A'; ch <= 'C'; ++ch) {
        thread t([ &, ch]() {
            for (auto i = 0; i < 10; ++i) {
                unique_lock<mutex> l(lock_status);
                cv.wait(l, [&]() {
                    return status % 3 == ch - 'A';
                });
                string tab(ch-'A', '\t');
                cout << tab << ch << '(' << this_thread::get_id() << ')' << endl;
                ++status;
                cv.notify_all();
            }
        });
        t.detach();
    }

    unique_lock<mutex> l(lock_exit);
    cv.wait(l, [&]() {
        return status == 30;
    });
    return 0;
}