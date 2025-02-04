#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

bool IsSequenceRight(const string& brackets) {
    map<char, char> opposite_brackets {{')', '('}, {'}', '{'}, {']', '['}};

    stack<char> bracket_stack;
    for (const char bracket : brackets) {
        if (bracket == '(' || bracket == '{' || bracket == '[') {
            bracket_stack.push(bracket);
        } else {
            if (bracket_stack.empty() || bracket_stack.top() != opposite_brackets[bracket]) {
                return false;
            } else {
                bracket_stack.pop();
            }
        }
    }

    if (bracket_stack.empty()) {
        return true;
    }
    return false;
}

int main() {
    string brackets;
    getline(cin, brackets);

    cout << (IsSequenceRight(brackets) ? "yes"s : "no"s);
}