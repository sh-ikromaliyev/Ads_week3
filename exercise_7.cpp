#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using namespace std::chrono;

int main() {
    vector<int> sizes = {50, 100, 200, 400};
    mt19937 rng(48);
    cout << "n,multiply_ms,approx_bytes\n";

    for (int n : sizes) {
        vector<vector<int>> A(n, vector<int>(n));
        vector<vector<int>> B(n, vector<int>(n));
        vector<vector<int>> C(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = static_cast<int>(rng() % 100);
                B[i][j] = static_cast<int>(rng() % 100);
            }

        auto start = high_resolution_clock::now();
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                for (int j = 0; j < n; j++)
                    C[i][j] += A[i][k] * B[k][j];
        auto stop = high_resolution_clock::now();

        double ms = duration<double, milli>(stop - start).count();
        unsigned long long bytes =
            3ULL * n * n * sizeof(int);

        cout << n << "," << fixed << setprecision(3) << ms << "," << bytes << "\n";
    }
    return 0;
}
