#include <iostream>
#include <vector>

using namespace std;

vector<int> FindPrefixSum(const vector<int>& numbers) {
    vector<int> prefix_sum;
    prefix_sum.reserve(numbers.size() + 1);
    prefix_sum.push_back(0);

    for (size_t i = 0; i < numbers.size(); ++i) {
        prefix_sum.push_back(numbers[i] + prefix_sum[i]);
    }

    return prefix_sum;
}

int main() {
    int n;
    cin >> n;

    vector<int> numbers;
    numbers.reserve(n);
    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        numbers.push_back(number);
    }

    vector<int> prefix_sum = FindPrefixSum(numbers);

    bool is_first = true;
    for (size_t i = 1; i <= n; ++i) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << prefix_sum[i];
    }
}