#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int FindMinDays(vector<int>& numbers, int n, int k) {
    sort(numbers.begin(), numbers.end());

    int lpointer = 0;
    int rpointer = 1;
    while (rpointer < n) {
        if (numbers[rpointer] - numbers[lpointer] <= k) {
            ++rpointer;
        } else {
            ++lpointer;
            ++rpointer;
        }
    }

    return rpointer - lpointer;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> numbers;
    numbers.reserve(n);
    for (int i = 0; i < n; ++i) {
        int number;
        cin >> number;
        numbers.push_back(number);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    }

    cout << FindMinDays(numbers, n, k);
}