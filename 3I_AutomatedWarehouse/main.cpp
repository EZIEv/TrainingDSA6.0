#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

map<int, int> FindRoversSequence(size_t n, int a, int b, vector<tuple<int, int, size_t>> rovers) {
    map<int, int> result;

    vector<stack<tuple<int, int, size_t>>> roads(4);
    for (tuple<int, int, size_t> rover : rovers) {
        roads[get<1>(rover) - 1].push(rover);
    }

    int c, d;
    if ((a == 1 && b == 4) || (a == 4 && b == 1)) {
        c = 2;
        d = 3;
    } else if ((a == 1 && b == 3) || (a == 3 && b == 1)) {
        c = 2;
        d = 4;
    } else if ((a == 1 && b == 2) || (a == 2 && b == 1)) {
        c = 3;
        d = 4;
    } else if ((a == 2 && b == 4) || (a == 4 && b == 2)) {
        c = 1;
        d = 3;
    } else if ((a == 2 && b == 3) || (a == 3 && b == 2)) {
        c = 1;
        d = 4;
    } else if ((a == 3 && b == 4) || (a == 4 && b == 3)) {
        c = 1;
        d = 2;
    }
    map<int, int> must_yield = {{1, 4}, {2, 1}, {3, 2}, {4, 3}};

    int cur_time = 1;
    if (abs(a - b) == 2) {
        while (!roads[a - 1].empty() || !roads[b - 1].empty() || !roads[c - 1].empty() || !roads[d - 1].empty()) {
            if ((!roads[a - 1].empty() && cur_time >= get<2>(roads[a - 1].top())) || (!roads[b - 1].empty() && cur_time >= get<2>(roads[b - 1].top()))) {
                if (!roads[a - 1].empty() && cur_time >= get<2>(roads[a - 1].top())) {
                    result[get<0>(roads[a - 1].top())] = cur_time;
                    roads[a - 1].pop();
                }
                if (!roads[b - 1].empty() && cur_time >= get<2>(roads[b - 1].top())) {
                    result[get<0>(roads[b - 1].top())] = cur_time;
                    roads[b - 1].pop();
                }
            } else if (!roads[c - 1].empty() || !roads[d - 1].empty()) {
                if (!roads[c - 1].empty() && cur_time >= get<2>(roads[c - 1].top())) {
                    result[get<0>(roads[c - 1].top())] = cur_time;
                    roads[c - 1].pop();
                }
                if (!roads[d - 1].empty() && cur_time >= get<2>(roads[d - 1].top())) {
                    result[get<0>(roads[d - 1].top())] = cur_time;
                    roads[d - 1].pop();
                }
            }
            ++cur_time;
        }
    } else {
        while (!roads[a - 1].empty() || !roads[b - 1].empty() || !roads[c - 1].empty() || !roads[d - 1].empty()) {
            if (!roads[must_yield[a] == b ? b - 1 : a - 1].empty() && cur_time >= get<2>(roads[must_yield[a] == b ? b - 1 : a - 1].top())) {
                result[get<0>(roads[must_yield[a] == b ? b - 1 : a - 1].top())] = cur_time;
                roads[must_yield[a] == b ? b - 1 : a - 1].pop();
            } else if (!roads[must_yield[a] == b ? a - 1 : b - 1].empty() && cur_time >= get<2>(roads[must_yield[a] == b ? a - 1 : b - 1].top())) {
                result[get<0>(roads[must_yield[a] == b ? a - 1 : b - 1].top())] = cur_time;
                roads[must_yield[a] == b ? a - 1 : b - 1].pop();
            } else if (!roads[must_yield[c] == d ? d - 1 : c - 1].empty() && cur_time >= get<2>(roads[must_yield[c] == d ? d - 1 : c - 1].top())) {
                result[get<0>(roads[must_yield[c] == d ? d - 1 : c - 1].top())] = cur_time;
                roads[must_yield[c] == d ? d - 1 : c - 1].pop();
            } else if (!roads[must_yield[c] == d ? c - 1 : d - 1].empty() && cur_time >= get<2>(roads[must_yield[c] == d ? c - 1 : d - 1].top())) {
                result[get<0>(roads[must_yield[c] == d ? c - 1 : d - 1].top())] = cur_time;
                roads[must_yield[c] == d ? c - 1 : d - 1].pop();
            }
            ++cur_time;
        }
    }

    return result;
}

int main() {
    size_t n;
    cin >> n;

    int a, b;
    cin >> a >> b;

    int counter = 0;
    vector<tuple<int, int, size_t>> rovers(n);
    for (tuple<int, int, size_t>& rover : rovers) {
        get<0>(rover) = counter;
        cin >> get<1>(rover);
        cin >> get<2>(rover);
        ++counter;
    }
    sort(rovers.begin(), rovers.end(), [](const auto lhs, const auto rhs) { return get<2>(lhs) > get<2>(rhs); });

    map<int, int> result = FindRoversSequence(n, a, b, rovers);
    for (int i = 0; i < n; ++i) {
        cout << result[i] << endl;
    }
}