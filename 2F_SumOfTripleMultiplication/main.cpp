#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

uint64_t FindSumOfTripleMultiplication(const vector<uint64_t>& numbers, int n) {
    uint64_t sum = 0;

    vector<uint64_t> prefixsum_1;
    prefixsum_1.reserve(n + 1);
    prefixsum_1.push_back(0);
    vector<uint64_t> prefixsum_2;
    prefixsum_2.reserve(n - 1);
    prefixsum_2.push_back(0);

    for (int i = 0; i < n; ++i) {
        prefixsum_1.push_back((numbers[i] + prefixsum_1[i]) % 1000000007);
    }
    for (int i = 1; i < n - 1; ++i) {
        prefixsum_2.push_back(((numbers[i] * (prefixsum_1[n] - prefixsum_1[i + 1] + 1000000007) % 1000000007 + prefixsum_2[i - 1])) % 1000000007);
    }
    for (int i = 0; i < n - 2; ++i) {
        sum = (sum + (numbers[i] * (prefixsum_2[n - 2] - prefixsum_2[i] + 1000000007) % 1000000007)) % 1000000007;
    }

    return sum;
}

int main() {
    int n;
    cin >> n;

    vector<uint64_t> numbers;
    numbers.reserve(n);
    for (int i = 0; i < n; ++i) {
        uint64_t number;
        cin >> number;
        numbers.push_back(number);
    }

    cout << FindSumOfTripleMultiplication(numbers, n);
}