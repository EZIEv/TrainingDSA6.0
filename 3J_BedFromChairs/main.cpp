#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int FindMinInconvenience(vector<pair<int, int>>& chairs, int h) {
    int min_inconvenience = 2e9;
    int current_height = 0;
    deque<pair<int, int>> chair_window;
    deque<int> inconvenience;

    for (int i = 0; i < chairs.size(); ++i) {
        current_height += chairs[i].second;
        chair_window.push_back(chairs[i]);
        if (i != 0) {
            int cur_inconvenience = chairs[i].first - chairs[i - 1].first;
            while (!inconvenience.empty() && inconvenience.back() < cur_inconvenience) {
                inconvenience.pop_back();
            }
            inconvenience.push_back(cur_inconvenience);
        }
        while (current_height >= h) {
            min_inconvenience = min(min_inconvenience, chairs.size() == 1 ? 0 : inconvenience.front());
            current_height -= chair_window[0].second;
            if (chair_window[1].first - chair_window[0].first == inconvenience[0]) {
                inconvenience.pop_front();
            }
            chair_window.pop_front();
        }
    }

    return min_inconvenience;
}

int main() {
    int n, h;
    cin >> n >> h;

    vector<pair<int, int>> chairs(n);
    for (pair<int, int>& chair : chairs) cin >> chair.first;
    for (pair<int, int>& chair : chairs) cin >> chair.second;
    sort(chairs.begin(), chairs.end(), [](const auto& lhs, const auto& rhs){ return lhs.first < rhs.first; });

    cout << FindMinInconvenience(chairs, h);
}