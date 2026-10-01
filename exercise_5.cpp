#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

int main() {
    srand(46);
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    cout << "n,push_back_us,reserve_push_back_us\n";

    for (int n : sizes) {
        long long noReserveTotal = 0;
        long long reserveTotal = 0;
        volatile int sink = 0;

        for (int r = 0; r < 5; r++) {
            vector<int> v;
            auto s1 = high_resolution_clock::now();
            for (int i = 0; i < n; i++) v.push_back(rand());
            auto e1 = high_resolution_clock::now();
            noReserveTotal += duration_cast<microseconds>(e1 - s1).count();
            sink += v[n - 1];

            vector<int> w;
            w.reserve(n);
            auto s2 = high_resolution_clock::now();
            for (int i = 0; i < n; i++) w.push_back(rand());
            auto e2 = high_resolution_clock::now();
            reserveTotal += duration_cast<microseconds>(e2 - s2).count();
            sink += w[n - 1];
        }

        cout << n << "," << fixed << setprecision(2)
             << noReserveTotal / 5.0 << "," << reserveTotal / 5.0 << "\n";
    }

    vector<int> v;
    cout << "capacity_jumps:";
    size_t previous = v.capacity();
    for (int i = 0; i < 100000; i++) {
        v.push_back(i);
        if (v.capacity() != previous) {
            cout << " " << v.capacity();
            previous = v.capacity();
        }
    }
    cout << "\n";
    return 0;
}
