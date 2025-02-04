#include <deque>
#include <iostream>
#include <vector>

using namespace std;

vector<int> FindMinOnSegment(vector<int>& nums, int n, int k) {
    vector<int> mins_on_segments;

    deque<int> window;
    for (int i = 0; i < k; ++i) {
        while (!window.empty() && window.back() > nums[i]) {
            window.pop_back();
        }
        window.push_back(nums[i]);
    }
    mins_on_segments.push_back(window.front());
    for (int i = k; i < n; ++i) {
        if (nums[i - k] == window.front()) {
            window.pop_front();
        }
        while (!window.empty() && window.back() > nums[i]) {
            window.pop_back();
        }
        window.push_back(nums[i]);
        mins_on_segments.push_back(window.front());
    }

    return mins_on_segments;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (auto& i : nums) cin >> i;

    for (auto i : FindMinOnSegment(nums, n, k)) {
        cout << i << endl;
    }
}