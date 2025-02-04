#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// The function returns vector in reversed state
vector<int> FindCheaperCities(vector<int>& cities_prices) {
    vector<int> cheaper_cities;

    stack<pair<int, int>> cheapest_cities;
    for (int i = cities_prices.size() - 1; i >= 0; --i) {
        while (!cheapest_cities.empty() && cheapest_cities.top().first >= cities_prices[i]) {
            cheapest_cities.pop();
        }
        if (cheapest_cities.empty()) {
            cheaper_cities.push_back(-1);
        } else {
            cheaper_cities.push_back(cheapest_cities.top().second);
        }
        cheapest_cities.push({cities_prices[i], i});
    }

    return cheaper_cities;
}

int main() {
    int n;
    cin >> n;

    vector<int> cities_prices(n);
    for (auto& price : cities_prices) cin >> price;

    vector<int> cheaper_cities = FindCheaperCities(cities_prices);
    bool is_first = true;
    for (int i = n - 1; i >= 0; --i) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << cheaper_cities[i]; 
    }
}