#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> removeMedians(vector<int>& numbers) {
    vector<int> result;
    sort(numbers.begin(), numbers.end());

    int left = (numbers.size() - 1) / 2;
    int right = numbers.size() / 2;

    while (!numbers.empty()) {
        int median;
        if (numbers.size() % 2 == 1) {
            median = numbers[left];
        } else {
            median = numbers[left];
        }

        result.push_back(median);
        numbers.erase(numbers.begin() + left);

        if (numbers.size() % 2 == 1) {
            left = right = numbers.size() / 2;
        } else {
            left = numbers.size() / 2 - 1;
            right = numbers.size() / 2;
        }
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    
    vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    vector<int> result = removeMedians(numbers);

    for (int x : result) {
        cout << x << " ";
    }
    cout << endl;
}
