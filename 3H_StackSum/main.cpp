#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class StackSum {
public:
    void AddNumber(int n) {
        stack_sum_.push(n);
        prefix_sum_.push_back(static_cast<uint64_t>(n) + prefix_sum_.back());
    }

    int DelTop() {
        int num = stack_sum_.top();
        stack_sum_.pop();
        prefix_sum_.pop_back();
        return num;
    }

    uint64_t GetSum(int k) {
        return prefix_sum_.back() - prefix_sum_[prefix_sum_.size() - k - 1];
    }

private:
    stack<int> stack_sum_;
    vector<uint64_t> prefix_sum_ = {0};
};

int main() {
    int n;
    cin >> n;

    StackSum stack_sum;
    for (int i = 0; i < n; ++i) {
        string query;
        cin >> query;
        if (query[0] == '+') {
            stack_sum.AddNumber(stoi(query.substr(1, query.size() - 1)));
        } else if (query[0] == '-') {
            cout << stack_sum.DelTop() << endl;;
        } else if (query[0] == '?') {
            cout << stack_sum.GetSum(stoi(query.substr(1, query.size() - 1))) << endl;
        }
    }
}