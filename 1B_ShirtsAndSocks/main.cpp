#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> FindMinQuantity(int blue_shirts, int red_shirts, int blue_socks, int red_socks) {
    if ((blue_shirts == 0 && blue_socks == 0) || (red_shirts == 0 && red_socks == 0)) {
        return pair<int, int>(1, 1);
    }

    if (red_shirts == blue_shirts || red_socks == blue_socks) {
        if (min(blue_shirts, blue_socks) == blue_shirts) {
            return pair<int, int>({blue_shirts + 1, 1});
        } else {
            return pair<int, int>({1, blue_socks + 1});
        }
    }

    if (blue_shirts == 0) {
        return pair<int, int>({1, blue_socks + 1});
    } else if (red_shirts == 0) {
        return pair<int, int>({1, red_socks + 1});
    } else if (blue_socks == 0) {
        return pair<int, int>({blue_shirts + 1, 1});
    } else if (red_socks == 0) {
        return pair<int, int>({red_shirts + 1, 1});
    }

    vector<int> options;
    options.push_back(max(blue_shirts + 1, red_shirts + 1) + 1);
    options.push_back(max(blue_socks + 1, red_socks + 1) + 1);
    options.push_back(blue_shirts + 1 + blue_socks + 1);
    options.push_back(red_shirts + 1 + red_socks + 1);
    int minimum = *min_element(options.begin(), options.end());
    if (minimum == options[0]) {
        return pair<int, int>({max(blue_shirts + 1, red_shirts + 1), 1});
    } else if (minimum == options[1]) {
        return pair<int, int>({1, max(blue_socks + 1, red_socks + 1)});
    } else if (minimum == options[2]) {
        return pair<int, int>({blue_shirts + 1, blue_socks + 1});
    } else {
        return pair<int, int>({red_shirts + 1, red_socks + 1});
    }
}

int main() {
    int blue_shirts, red_shirts, blue_socks, red_socks;
    cin >> blue_shirts >> red_shirts >> blue_socks >> red_socks;
    pair<int, int> result = FindMinQuantity(blue_shirts, red_shirts, blue_socks, red_socks);
    cout << result.first << ' ' << result.second;
}