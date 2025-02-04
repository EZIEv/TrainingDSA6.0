#include <algorithm>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

vector<int> FindAlgorithmOrder(const vector<tuple<int, int, int>>& algorithms, const vector<int>& mood, int n) {
    vector<tuple<int, int, int>> sorted_by_interest = algorithms;
    sort(sorted_by_interest.begin(), sorted_by_interest.end(), 
        [](const auto &a, const auto &b) {
            if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
            if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
            return get<2>(a) < get<2>(b);
        }
    );

    vector<tuple<int, int, int>> sorted_by_usefulness = algorithms;
    sort(sorted_by_usefulness.begin(), sorted_by_usefulness.end(), 
        [](const auto &a, const auto &b) {
            if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
            if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
            return get<2>(a) < get<2>(b);
        }
    );

    map<int, bool> history;
    int interest_ptr = 0, usefulness_ptr = 0;
    vector<int> result;
    for (int i = 0; i < n; ++i) {
        if (mood[i] == 0) {
            while (interest_ptr < n && history[get<2>(sorted_by_interest[interest_ptr])]) {
                ++interest_ptr;
            }
            result.push_back(get<2>(sorted_by_interest[interest_ptr]));
            history[get<2>(sorted_by_interest[interest_ptr])] = true;
            ++interest_ptr;
        } else {
            while (usefulness_ptr < n && history[get<2>(sorted_by_usefulness[usefulness_ptr])]) {
                ++usefulness_ptr;
            }
            result.push_back(get<2>(sorted_by_usefulness[usefulness_ptr]));
            history[get<2>(sorted_by_usefulness[usefulness_ptr])] = true;
            ++usefulness_ptr;
        }
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> interest(n), usefulness(n), mood(n);
    for (int i = 0; i < n; ++i) cin >> interest[i];
    for (int i = 0; i < n; ++i) cin >> usefulness[i];
    for (int i = 0; i < n; ++i) cin >> mood[i];

    vector<tuple<int, int, int>> algorithms;
    for (int i = 0; i < n; ++i) {
        algorithms.push_back(tuple(interest[i], usefulness[i], i + 1));
    }

    vector<int> result = FindAlgorithmOrder(algorithms, mood, n);
    bool is_first = true;
    for (int i = 0; i < n; ++i) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << result[i];
    }
}