#include <iostream>
#include <vector>

using namespace std;

int FindSubtreeSize(int node, int parent, vector<vector<int>>& tree, vector<int>& subtree_size) {
    subtree_size[node] = 1;
    for (int neighbor : tree[node]) {
        if (neighbor != parent) {
            subtree_size[node] += FindSubtreeSize(neighbor, node, tree, subtree_size);
        }
    }
    return subtree_size[node];
}

int main() {
    int V;
    cin >> V;
    
    vector<vector<int>> tree(V + 1);
    vector<int> subtree_size(V + 1);
    
    for (int i = 0; i < V - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    FindSubtreeSize(1, -1, tree, subtree_size);
    
    bool is_first = true;
    for (int i = 1; i <= V; ++i) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << subtree_size[i];
    }
}
