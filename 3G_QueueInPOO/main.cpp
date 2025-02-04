#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

uint64_t FindSumClientsTime(vector<int> clients, int n, int k) {
    uint64_t sum_time = 0;

    uint64_t cur_clients = 0;
    for (int i = 0; i < n; ++i) {
        cur_clients += clients[i];
        sum_time += cur_clients;
        cur_clients -= k > cur_clients ? cur_clients : k;
    }
    sum_time += cur_clients;

    return sum_time;
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<int> clients(n);
    for (int& client_i : clients) cin >> client_i;

    cout << FindSumClientsTime(clients, n, k);
}