#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

// Fast exponentiation to compute a^b mod MOD
ll pow_mod_func(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    // Build the adjacency list with directed edges from a to b
    vector<vector<int>> adj(N+1, vector<int>());
    // To perform topological sort, we need to know the incoming edges
    vector<int> in_degree(N+1, 0);
    for(int i=0;i<N-1;i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        in_degree[b]++;
    }
    
    // Implement backtracking for small N
    if(N <= 15){
        // Initialize dependencies
        vector< vector<int> > dependencies(N+1, vector<int>());
        for(int u=1; u<=N; u++){
            for(auto &v: adj[u]){
                dependencies[v].push_back(u);
            }
        }
        // Initialize in-degree copy
        vector<int> in_deg_copy = in_degree;
        // Initialize used nodes
        vector<bool> used(N+1, false);
        ll total =0;
        // Recursive function
        function<void()> backtrack = [&](void) {
            // Find all available nodes (in-degree 0 and not used)
            vector<int> available;
            for(int u=1; u<=N; u++) {
                if(!used[u] && in_deg_copy[u]==0){
                    available.push_back(u);
                }
            }
            if(available.empty()){
                // All nodes used
                total = (total +1) % MOD;
                return;
            }
            for(auto &u: available){
                // Choose u
                used[u] = true;
                // Decrease in-degree of its children
                vector<int> children = adj[u];
                for(auto &v: children){
                    in_deg_copy[v]--;
                }
                // Recurse
                backtrack();
                // Backtrack
                for(auto &v: children){
                    in_deg_copy[v]++;
                }
                used[u] = false;
            }
        };
        backtrack();
        cout << total;
        return 0;
    }
    
    // For larger N (15 < N <= 3000), implement DP approach
    // Precompute factorial and inverse factorial
    int MAX = N;
    vector<long long> fact(MAX+1, 1);
    for(int i=1;i<=MAX;i++) {
        fact[i] = fact[i-1] * i % MOD;
    }
    // Compute inverse factorial using Fermat's Little Theorem
    vector<long long> inv_fact(MAX+1, 1);
    inv_fact[MAX] = pow_mod_func(fact[MAX], MOD-2);
    for(int i=MAX-1;i>=0;i--){
        inv_fact[i] = inv_fact[i+1] * (i+1) % MOD;
    }
    
    // Perform topological sort using Kahn's algorithm
    vector<int> topo_order;
    queue<int> q;
    for(int u=1; u<=N; u++) {
        if(in_degree[u] ==0){
            q.push(u);
        }
    }
    while(!q.empty()){
        int u = q.front(); q.pop();
        topo_order.push_back(u);
        for(auto &v: adj[u]){
            in_degree[v]--;
            if(in_degree[v] ==0){
                q.push(v);
            }
        }
    }
    
    // Check if topological sort includes all nodes
    if(topo_order.size() != N){
        // Not a DAG, but as per initial code, assume it's a DAG
        // If not a DAG, output 0
        cout << 0;
        return 0;
    }
    
    // Reverse topological order for DP (process children before parents)
    reverse(topo_order.begin(), topo_order.end());
    
    // Initialize dp and size arrays
    vector<long long> dp(N+1, 1);
    vector<int> size_subtree(N+1, 1);
    
    for(auto &u: topo_order){
        // If u has no children, dp[u] =1 and size[u]=1
        if(adj[u].empty()){
            dp[u] =1;
            size_subtree[u] =1;
            continue;
        }
        // Else, compute dp[u] and size[u]
        ll current_dp =1;
        int sum_s =0;
        for(auto &v: adj[u]){
            current_dp = current_dp * dp[v] % MOD;
            sum_s += size_subtree[v];
        }
        // Multiply by fact[sum_s]
        current_dp = current_dp * fact[sum_s] % MOD;
        // Multiply by inv_fact[size[v]] for each child
        for(auto &v: adj[u]){
            current_dp = current_dp * inv_fact[size_subtree[v]] % MOD;
        }
        dp[u] = current_dp;
        size_subtree[u] = 1 + sum_s;
    }
    
    // Find all roots (nodes with in-degree zero)
    vector<int> roots;
    // Recompute in-degree
    vector<int> final_in_degree(N+1, 0);
    for(int u=1; u<=N; u++){
        for(auto &v: adj[u]){
            final_in_degree[v]++;
        }
    }
    for(int u=1; u<=N; u++){
        if(final_in_degree[u] ==0){
            roots.push_back(u);
        }
    }
    
    // If no roots found, it's not a DAG
    if(roots.empty()){
        cout << 0;
        return 0;
    }
    
    // Compute the total number of topological orderings
    // Total = (product of dp[root_i]) * fact[N] * (prod inv_fact[s_i]) % MOD
    ll total =1;
    vector<int> sizes;
    for(auto &root: roots){
        total = total * dp[root] % MOD;
        sizes.push_back(size_subtree[root]);
    }
    // Multiply by fact[N]
    total = total * fact[N] % MOD;
    // Multiply by inv_fact[s_i] for each root
    for(auto &s: sizes){
        total = total * inv_fact[s] % MOD;
    }
    cout << total;
}