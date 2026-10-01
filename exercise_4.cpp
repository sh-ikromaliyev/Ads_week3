#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

const int CAP = 100000;
int A[CAP];

int main() {
    srand(45);
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    cout << "n,static_us,dynamic_us,dynamic_bytes\n";
    for (int n : sizes) {
        int* B = new int[n];
        long long staticTotal = 0;
        long long dynamicTotal = 0;
        volatile int sink = 0;

        for (int r = 0; r < 5; r++) {
            auto s1 = high_resolution_clock::now();
            for (int i = 0; i < n; i++) A[i] = rand();
            auto e1 = high_resolution_clock::now();
            staticTotal += duration_cast<microseconds>(e1 - s1).count();

            auto s2 = high_resolution_clock::now();
            for (int i = 0; i < n; i++) B[i] = rand();
            auto e2 = high_resolution_clock::now();
            dynamicTotal += duration_cast<microseconds>(e2 - s2).count();
            sink += A[n - 1] + B[n - 1];
        }

        cout << n << "," << fixed << setprecision(2)
             << staticTotal / 5.0 << "," << dynamicTotal / 5.0 << ","
             << n * sizeof(int) << "\n";
        delete[] B;
    }
    return 0;
}
