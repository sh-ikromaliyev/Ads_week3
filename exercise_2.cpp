#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

int linearSearch(int A[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (A[i] == key) return i;
    }
    return -1;
}

int main() {
    srand(43);
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    cout << "n,best_us,avg_us,worst_us\n";
    for (int n : sizes) {
        int* A = new int[n];
        for (int i = 0; i < n; i++) A[i] = rand();
        long long best = 0, avg = 0, worst = 0;
        volatile int sink = 0;
        for (int r = 0; r < 5; r++) {
            auto s1 = high_resolution_clock::now();
            sink = linearSearch(A, n, A[0]);
            auto e1 = high_resolution_clock::now();
            best += duration_cast<microseconds>(e1 - s1).count();

            auto s2 = high_resolution_clock::now();
            sink = linearSearch(A, n, A[n / 2]);
            auto e2 = high_resolution_clock::now();
            avg += duration_cast<microseconds>(e2 - s2).count();

            auto s3 = high_resolution_clock::now();
            sink = linearSearch(A, n, -999999);
            auto e3 = high_resolution_clock::now();
            worst += duration_cast<microseconds>(e3 - s3).count();
        }
        cout << n << "," << fixed << setprecision(2)
             << best / 5.0 << "," << avg / 5.0 << "," << worst / 5.0 << "\n";
        delete[] A;
    }
    return 0;
}
