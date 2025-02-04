#include <iostream>
#include <map>
#include <vector>

using namespace std;

map<int, int> FindPrefixsumByValue(const vector<int>& cars) {
    map<int, int> prefixsum_by_value = {{0, 1}};

    int now_sum = 0;
    for (const int car : cars) {
        now_sum += car;
        ++prefixsum_by_value[now_sum];
    }

    return prefixsum_by_value;
}

int FindSetOfCars(const map<int, int>& prefixsum_by_value, int k) {
    int ranges = 0;

    for (const auto [nowsum, quantity] : prefixsum_by_value) {
        if (prefixsum_by_value.contains(nowsum + k)) {
            ranges += quantity * prefixsum_by_value.at(nowsum + k);
        }
    }

    return ranges;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> cars;
    cars.reserve(n);
    for (int i = 0; i < n; ++i) {
        int car;
        cin >> car;
        cars.push_back(car);
    }

    cout << FindSetOfCars(FindPrefixsumByValue(cars), k);
}