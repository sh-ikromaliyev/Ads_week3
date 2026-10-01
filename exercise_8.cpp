#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

long long fibRecursive(int n) {
    if (n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

long long fibIterative(int n) {
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        long long next = a + b;
        a = b;
        b = next;
    }
    return a;
}

int main() {
    vector<int> recursiveSizes = {20, 25, 30, 35};
    vector<int> iterativeSizes = {1000, 100000, 1000000};

    cout << "recursive\n";
    cout << "n,time_us\n";
    for (int n : recursiveSizes) {
        auto start = high_resolution_clock::now();
        volatile long long result = fibRecursive(n);
        auto stop = high_resolution_clock::now();
        cout << n << "," << duration_cast<microseconds>(stop - start).count() << "\n";
    }

    cout << "iterative\n";
    cout << "n,time_us\n";
    for (int n : iterativeSizes) {
        auto start = high_resolution_clock::now();
        volatile long long result = fibIterative(n);
        auto stop = high_resolution_clock::now();
        cout << n << "," << duration_cast<microseconds>(stop - start).count() << "\n";
    }
    return 0;
}
