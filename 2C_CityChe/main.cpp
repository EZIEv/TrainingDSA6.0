#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

void FindSuitableWays(const vector<int>& distances, int n, int r) {
    uint64_t ways = 0;

    int rpointer = 0;
    for (int lpointer = 0; lpointer < n; ++lpointer) {
        while (rpointer < n && distances[rpointer] - distances[lpointer] <= r) {
            ++rpointer;
        } 
        ways += static_cast<uint64_t>(n - rpointer);
    }

    cout << ways;
}

int main() {
    int n, r;
    cin >> n >> r;

    vector<int> distances;
    distances.reserve(n);
    for (int i = 0; i < n; ++i) {
        int distance;
        cin >> distance;
        distances.push_back(distance);
    }

    FindSuitableWays(distances, n, r);
}