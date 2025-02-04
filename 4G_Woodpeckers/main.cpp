#include <iostream>
#include <vector>
#include <queue>
#include <cstdint>

using namespace std;

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

uint64_t factorialMod(uint64_t n, uint64_t mod) {
    uint64_t result = 1;
    for (uint64_t i = 2; i <= n; ++i) {
        result = (result * (i % mod)) % mod;
    }
    return result;
}

uint64_t otherFactorialMod(int n, int m, int mod) {
    uint64_t result = 1;
    for (int i = n + 1; i <= m; ++i) {
        result = (result * (i % mod)) % mod;
    }
    return result;
}

void BFS(int n, const vector<vector<int>>& graph, int& tracks, int& isolated_tracks, int& isolated, vector<pair<int, bool>>& leafs, bool& res_flag) {
    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; ++i) {
        if (visited[i]) continue;

        if (graph[i].empty()) {
            ++isolated;
        } else if (graph[i].size() == 1 && !visited[graph[i][0]] && graph[graph[i][0]].size() == 1) {
            ++isolated_tracks;
            visited[graph[i][0]] = true;
        } else {
            ++tracks;

            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int cur_vertex = q.front();
                q.pop();

                bool only_leafs = true;
                int res_counter = 0;
                int visited_counter = 0;

                for (int neighbor : graph[cur_vertex]) {
                    if (graph[neighbor].size() == 1) {
                        ++leafs[cur_vertex].first;
                    } else {
                        only_leafs = false;
                        ++res_counter;
                    }

                    if (!visited[neighbor]) {
                        q.push(neighbor);
                    } else {
                        ++visited_counter;
                    }
                }
                if (res_counter > 2 || visited_counter > 1) {
                    res_flag = false;
                    return;
                }
                leafs[cur_vertex].second = only_leafs;
                visited[cur_vertex] = true;
            }
        }
        visited[i] = true;
    }
}

uint64_t FindMaxCombinations(int n, int k, const vector<vector<int>>& graph) {
    int isolated_tracks = 0;
    int tracks = 0;
    int isolated = 0;
    vector<pair<int, bool>> leafs(n + 1, {0, false});

    bool res_flag = true;
    BFS(n, graph, tracks, isolated_tracks, isolated, leafs, res_flag);
    if (!res_flag) {
        return 0;
    }

    uint64_t leafs_perms = 1;
    for (auto [val, flag] : leafs) {
        uint64_t res = factorialMod(static_cast<uint64_t>(val), static_cast<uint64_t>(k));
        if (flag) {
            --tracks;
            ++isolated_tracks;
        }
        leafs_perms = (leafs_perms * res) % k;
    }

    uint64_t tracks_factorial = factorialMod(tracks + isolated_tracks, k);
    uint64_t tracks_power = modPow(4, tracks, k);
    uint64_t isolated_tracks_power = modPow(2, isolated_tracks, k);
    uint64_t isolated_factorial = isolated == 0 ? 1 : otherFactorialMod(n + 1 - isolated, n + 1, k);

    return (((((tracks_factorial * tracks_power) % k) * isolated_tracks_power) % k * leafs_perms % k) * isolated_factorial) % k;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> graph(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << FindMaxCombinations(n, k, graph) << endl;
}
