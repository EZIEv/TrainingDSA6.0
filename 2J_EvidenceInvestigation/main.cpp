#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int> FindLastEvedences(const vector<int>& evidences, int n, int m, int k, const vector<int>& indexes) {
    map<int, int> last_evidences = {{1, 1}};

    int lpointer = 0;
    int rpointer = 1;
    int counter = 0;
    int last = evidences[0];
    while (rpointer < n) {
        if (evidences[rpointer] == last) {
            ++counter;
            if (counter > k) {
                ++lpointer;
                while (lpointer < rpointer && evidences[lpointer] != evidences[lpointer - 1]) {
                    ++lpointer;
                }
                --counter;
            }
        } else if (evidences[rpointer] > last) {
            last = evidences[rpointer];
        } else {
            lpointer = rpointer;
            counter = 0;
            last = evidences[rpointer];
        }

        last_evidences[rpointer + 1] = lpointer + 1;
        ++rpointer;
    }

    vector<int> result(m);
    for (int i = 0; i < m; ++i) {
        result[i] = last_evidences[indexes[i]];
    }

    return result;
}

int main() {
    int n;
    cin >> n;

    vector<int> evidences(n);
    for (int& i : evidences) cin >> i;

    int m, k;
    cin >> m >> k;

    vector<int> indexes(m);
    for (int& i : indexes) cin >> i;

    bool is_first = true;
    for (int i : FindLastEvedences(evidences, n, m, k, indexes)) {
        if (!is_first) {
            cout << ' ';
        }
        is_first = false;
        cout << i;
    }
}