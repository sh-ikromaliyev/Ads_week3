#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace std::chrono;

int arraySum(int A[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) sum += A[i];
    return sum;
}

void bubbleSort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (A[j] > A[j + 1]) {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}

int main() {
    srand(44);
    vector<int> sizes = {1000, 5000, 10000, 20000, 30000};
    cout << "n,sum_us,bubble_us\n";
    for (int n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; i++) base[i] = rand();

        int sumA = arraySum(base.data(), n);
        long long sumTotal = 0;
        long long bubbleTotal = 0;
        volatile int sink = sumA;

        for (int r = 0; r < 3; r++) {
            auto s1 = high_resolution_clock::now();
            sink = arraySum(base.data(), n);
            auto e1 = high_resolution_clock::now();
            sumTotal += duration_cast<microseconds>(e1 - s1).count();

            vector<int> copy = base;
            auto s2 = high_resolution_clock::now();
            bubbleSort(copy.data(), n);
            auto e2 = high_resolution_clock::now();
            bubbleTotal += duration_cast<microseconds>(e2 - s2).count();
        }
        cout << n << "," << fixed << setprecision(2)
             << sumTotal / 3.0 << "," << bubbleTotal / 3.0 << "\n";
    }
    return 0;
}
