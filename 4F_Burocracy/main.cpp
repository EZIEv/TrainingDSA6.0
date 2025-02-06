#include <cstdint>
#include <iostream>
#include <vector>
#include <sys/resource.h>

using namespace std;

pair<uint64_t, uint64_t> CountCoins(int employee, vector<vector<int>>& subordinates, vector<pair<uint64_t, uint64_t>>& coins) {
    uint64_t total_coins = 0;
    uint64_t emp_size = 0;

    for (int subordinate : subordinates[employee]) {
        ++emp_size;
        ++total_coins;
        pair<uint64_t, uint64_t> res = CountCoins(subordinate, subordinates, coins);
        total_coins += res.first;
        emp_size += res.second;
    }
    ++total_coins;

    coins[employee].first = total_coins;
    coins[employee].second = emp_size;
    return {total_coins + emp_size, emp_size};
}

int main() {
    const rlim_t kStackSize = 16 * 1024 * 1024;
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);

    int N;
    cin >> N;

    vector<vector<int>> subordinates(N + 1);
    vector<pair<uint64_t, uint64_t>> coins(N + 1);

    for (int i = 2; i <= N; ++i) {
        int boss;
        cin >> boss;
        subordinates[boss].push_back(i);
    }

    CountCoins(1, subordinates, coins);

    bool is_first = true;
    for (int i = 1; i <= N; ++i) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << coins[i].first;
    }
}
