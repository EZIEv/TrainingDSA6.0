#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

uint64_t FindMinMoves (const vector<int> workers, int n) {
    uint64_t total_workers = 0;
    for (int worker : workers) {
        total_workers += worker;
    }

    uint64_t cumulative_sum = 0;
    int median_index = 0;
    for (int i = 0; i < n; ++i) {
        cumulative_sum += workers[i];
        if (cumulative_sum >= (total_workers + 1) / 2) {
            median_index = i;
            break;
        }
    }

    uint64_t min_moves = 0;
    for (int i = 0; i < n; ++i) {
        min_moves += static_cast<uint64_t>(abs(i - median_index)) * workers[i];
    }

    return min_moves;
}

int main() {
    int n;
    cin >> n;

    vector<int> workers;
    workers.reserve(n);
    for (int i = 0; i < n; ++i) {
        int worker;
        cin >> worker;
        workers.push_back(worker);
    }

    cout << FindMinMoves(workers, n);
}