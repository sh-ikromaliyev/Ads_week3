#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* next;
};

Node* buildList(const vector<int>& data) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int x : data) {
        Node* node = new Node{x, nullptr};
        if (!head) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

bool searchList(Node* head, int key) {
    Node* current = head;
    while (current) {
        if (current->data == key) return true;
        current = current->next;
    }
    return false;
}

void freeList(Node* head) {
    while (head) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

int main() {
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    mt19937 rng(49);
    cout << "n,structure,insert_us,search_us,bytes_per_element,total_bytes\n";

    for (int n : sizes) {
        vector<int> data(n);
        for (int& x : data) x = static_cast<int>(rng());

        vector<int> v;
        auto vs = high_resolution_clock::now();
        for (int x : data) v.push_back(x);
        auto ve = high_resolution_clock::now();
        auto vsearchStart = high_resolution_clock::now();
        volatile auto vit = find(v.begin(), v.end(), data[n - 2]);
        auto vsearchEnd = high_resolution_clock::now();

        int* a = new int[n];
        auto as = high_resolution_clock::now();
        for (int i = 0; i < n; i++) a[i] = data[i];
        auto ae = high_resolution_clock::now();
        auto asearchStart = high_resolution_clock::now();
        volatile int apos = -1;
        for (int i = 0; i < n; i++) {
            if (a[i] == data[n - 2]) {
                apos = i;
                break;
            }
        }
        auto asearchEnd = high_resolution_clock::now();

        auto ls = high_resolution_clock::now();
        Node* head = buildList(data);
        auto le = high_resolution_clock::now();
        auto lsearchStart = high_resolution_clock::now();
        volatile bool found = searchList(head, data[n - 2]);
        auto lsearchEnd = high_resolution_clock::now();

        size_t vectorBytes = v.capacity() * sizeof(int);
        size_t arrayBytes = n * sizeof(int);
        size_t nodeBytes = n * sizeof(Node);

        cout << n << ",vector,"
             << duration_cast<microseconds>(ve - vs).count() << ","
             << duration_cast<microseconds>(vsearchEnd - vsearchStart).count() << ","
             << sizeof(int) << "," << vectorBytes << "\n";

        cout << n << ",array,"
             << duration_cast<microseconds>(ae - as).count() << ","
             << duration_cast<microseconds>(asearchEnd - asearchStart).count() << ","
             << sizeof(int) << "," << arrayBytes << "\n";

        cout << n << ",linked_list,"
             << duration_cast<microseconds>(le - ls).count() << ","
             << duration_cast<microseconds>(lsearchEnd - lsearchStart).count() << ","
             << sizeof(Node) << "," << nodeBytes << "\n";

        delete[] a;
        freeList(head);
    }
    return 0;
}
