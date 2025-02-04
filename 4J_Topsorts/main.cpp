#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

const int MOD = 1e9 + 7;

inline int add_mod(int a, int b) {
    return (a + b) % MOD;
}

inline int mul_mod(int a, int b) {
    return (1LL * a * b) % MOD;
}

int countTopSorts(int n, const vector<vector<int>>& graph) {
    vector<int> indegree(n, 0);

    for (int u = 0; u < n; ++u) {
        for (int v : graph[u]) {
            indegree[v]++;
        }
    }

    unordered_map<int, int> dp;
    dp[0] = 1;

    for (int mask = 0; mask < (1 << n); ++mask) {
        if (dp.find(mask) == dp.end()) continue;

        for (int v = 0; v < n; ++v) {
            if ((mask & (1 << v)) == 0) {
                bool canAdd = true;
                for (int u : graph[v]) {
                    if ((mask & (1 << u)) == 0) {
                        canAdd = false;
                        break;
                    }
                }

                if (canAdd) {
                    int nextMask = mask | (1 << v);
                    dp[nextMask] = add_mod(dp[nextMask], dp[mask]);
                }
            }
        }
    }

    return dp[(1 << n) - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        graph[u].push_back(v);
    }

    cout << countTopSorts(n, graph);
}
