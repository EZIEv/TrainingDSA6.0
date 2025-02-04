#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

int MaxSubstrWork(const string& s, int n, uint64_t c) {
    uint64_t censor_sum = 0;
    uint64_t a_counter = 0;
    uint64_t b_counter = 0;

    int l = 0;
    int r = 0;
    int best_l = 0;
    int best_r = 0;

    while (r < n) {
        if (censor_sum <= c) {
            if (r - l > best_r - best_l) {
                best_r = r;
                best_l = l;
            }
            if (s[r] == 'a') {
                ++a_counter;
            } else if (a_counter > 0 && s[r] == 'b') {
                b_counter += 1;
                censor_sum += a_counter;
            }
            ++r;
        } else {
            while (l < n && censor_sum > c) {
                if (s[l] == 'a') {
                    --a_counter;
                    censor_sum -= b_counter;
                    int i = l + 1;
                    while (i < n && i < r && s[i] != 'a') {
                        if (s[i] == 'b') {
                            --b_counter;
                        }
                        ++i;
                    }
                }
                ++l;
            }
        }
    }

    if (censor_sum <= c) {
        if (r - l > best_r - best_l) {
            best_r = r;
            best_l = l;
        }
    } else {
        while (l < n && censor_sum > c) {
                if (s[l] == 'a') {
                    --a_counter;
                    censor_sum -= b_counter;
                    int i = l + 1;
                    while (i < n && i < r && s[i] != 'a') {
                        if (s[i] == 'b') {
                            --b_counter;
                        }
                        ++i;
                    }
                }
                ++l;
            }
        if (censor_sum <= c) {
            if (r - l > best_r - best_l) {
                best_r = r;
                best_l = l;
            }
        }
    }

    return best_r - best_l;
}

int main() {
    int n;
    uint64_t c;
    cin >> n >> c;

    string s;
    cin >> s;

    cout << MaxSubstrWork(s, n, c);
}