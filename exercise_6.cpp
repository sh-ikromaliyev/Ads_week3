#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using namespace std::chrono;

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
    vector<int> sizes = {1000, 5000, 10000, 20000, 30000, 50000, 100000};
    mt19937 rng(47);
    cout << "n,bubble_ms,std_sort_ms,ratio\n";

    for (int n : sizes) {
        vector<int> base(n);
        for (int& x : base) x = static_cast<int>(rng());

        vector<int> a = base;
        auto s1 = high_resolution_clock::now();
        bubbleSort(a.data(), n);
        auto e1 = high_resolution_clock::now();

        vector<int> b = base;
        auto s2 = high_resolution_clock::now();
        sort(b.begin(), b.end());
        auto e2 = high_resolution_clock::now();

        double bubble = duration<double, milli>(e1 - s1).count();
        double standard = duration<double, milli>(e2 - s2).count();
        cout << n << "," << fixed << setprecision(3) << bubble << ","
             << standard << "," << bubble / standard << "\n";
    }
    return 0;
}
