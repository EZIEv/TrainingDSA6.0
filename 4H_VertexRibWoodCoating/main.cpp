#include <iostream>
#include <vector>
#include <algorithm>
//#include <sys/resource.h>

using namespace std;

struct TreeNode {
    int id;
    long long cost;
    vector<int> neighbors;
};

void DFS(int node, int parent, vector<TreeNode>& tree, vector<vector<long long>>& dp) {
    dp[node][1] = tree[node].cost;
    dp[node][0] = 0;

    for (int neighbor : tree[node].neighbors) {
        if (neighbor == parent) continue;

        DFS(neighbor, node, tree, dp);

        dp[node][1] += min(dp[neighbor][0], dp[neighbor][1]);
        dp[node][0] += dp[neighbor][1];
    }
}

void CollectMarked(int node, int parent, vector<TreeNode>& tree, vector<vector<long long>>& dp, vector<int>& marked, bool flag = false) {
    bool is_marked;
    
    if (flag) {
        is_marked = true;
    } else {
        is_marked = dp[node][1] <= dp[node][0];
    }

    if (is_marked) {
        marked.push_back(node);
    }

    for (int neighbor : tree[node].neighbors) {
        if (neighbor == parent) continue;

        if (!is_marked) {
            CollectMarked(neighbor, node, tree, dp, marked, true);
        } else if (!is_marked && tree[neighbor].neighbors.size() == 1) {
            CollectMarked(neighbor, node, tree, dp, marked, true);
        } else {
            CollectMarked(neighbor, node, tree, dp, marked);
        }
    }
}

int main() {
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);

    int n;
    cin >> n;

    vector<TreeNode> tree(n + 1);
    for (int i = 1; i <= n; ++i) {
        tree[i].id = i;
    }

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].neighbors.push_back(v);
        tree[v].neighbors.push_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        cin >> tree[i].cost;
    }

    if (n == 1) {
        cout << tree[1].cost << " " << 1 << endl;
        cout << 1 << " ";
    } else {
        vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));
        DFS(1, -1, tree, dp);

        vector<int> marked;
        CollectMarked(1, -1, tree, dp, marked);

        long long min_cost = min(dp[1][0], dp[1][1]);

        cout << min_cost << " " << marked.size() << endl;
        for (int vertex : marked) {
            cout << vertex << " ";
        }
    }
}
