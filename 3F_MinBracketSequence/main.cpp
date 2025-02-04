#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void FindMinBracketSeq(string& brackets, map<char, int> lex_order, int n) {
    map<char, char> opposite_brackets {{'(', ')'}, {'[', ']'}};
    stack<char> bracket_stack;
    for (const char bracket : brackets) {
        if (bracket == '(' || bracket == '[') {
            bracket_stack.push(bracket);
        } else {
            bracket_stack.pop();
        }
    }
    
    while (n - brackets.size() != bracket_stack.size()) {
        vector<char> possible_brackets = {'(', '['};
        if (!bracket_stack.empty()) {
            possible_brackets.push_back(opposite_brackets[bracket_stack.top()]);
        }
        sort(possible_brackets.begin(), possible_brackets.end(), [&lex_order](const auto lhs, const auto rhs) { return lex_order[lhs] < lex_order[rhs]; });
        char min_bracket = possible_brackets[0];
        brackets += min_bracket;
        if (min_bracket == ')' || min_bracket == ']') {
            bracket_stack.pop();
        } else {
            bracket_stack.push(min_bracket);
        }
    }

    while (!bracket_stack.empty()) {
        brackets += opposite_brackets[bracket_stack.top()];
        bracket_stack.pop();
    }
}

int main() {
    int n;
    cin >> n;
    string temp;
    getline(cin, temp);

    map<char, int> lex_order;
    string str;
    getline(cin, str);
    for (int i = 0; i < str.size(); ++i) {
        lex_order[str[i]] = i;
    }

    string brackets;
    getline(cin, brackets);

    FindMinBracketSeq(brackets, lex_order, n);
    cout << brackets;
}