#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

int arraySum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int main() {
    srand(42);
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    cout << "n,avg_us\n";
    for (int n : sizes) {
        int* A = new int[n];
        for (int i = 0; i < n; i++) A[i] = rand();
        long long total = 0;
        volatile int sink = 0;
        for (int r = 0; r < 5; r++) {
            auto start = high_resolution_clock::now();
            sink = arraySum(A, n);
            auto stop = high_resolution_clock::now();
            total += duration_cast<microseconds>(stop - start).count();
        }
        cout << n << "," << fixed << setprecision(2) << total / 5.0 << "\n";
        delete[] A;
    }
    return 0;
}
