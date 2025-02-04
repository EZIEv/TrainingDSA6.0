#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <climits>
#include <string>
#include <unordered_map>

using namespace std;

int EvalPostfix(const string& postfix) {
    stack<int> values;
    stringstream tokens(postfix);
    string token;

    while (tokens >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            values.push(stoi(token));
        } else if (token == "+" || token == "-" || token == "*") {
            if (values.size() < 2) return INT_MAX;
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            if (token == "+") values.push(a + b);
            else if (token == "-") values.push(a - b);
            else if (token == "*") values.push(a * b);
        }
    }

    return (values.size() == 1) ? values.top() : INT_MAX;
}

bool IsOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '(' || c == ')';
}

int Precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*') return 2;
    return 0;
}

bool IsValidinfixession(const string& infix) {
    int bracket_open = 0;
    int bracket_close = 0;
    for (char c : infix) {
        if (c == '(') {
            ++bracket_open;
        } else if (c == ')') {
            ++bracket_close;
        }
        if (!isdigit(c) && !IsOperator(c) && !isspace(c)) {
            return false;
        }
    }

    return bracket_close == bracket_open;
}

string ConvertInfixToPostfix(const string& infix) {
    stack<char> operators;
    stringstream postfix;
    bool expectUnary = true;

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];

        if (isspace(c)) continue;

        if (isdigit(c) || (c == '-' && expectUnary)) {
            if (c == '-') postfix << c;
            else postfix << c;

            while (i + 1 < infix.size() && isdigit(infix[i + 1])) {
                postfix << infix[++i];
            }
            postfix << ' ';
            expectUnary = false;
        } else if (c == '(') {
            operators.push(c);
            expectUnary = true;
        } else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
            expectUnary = false;
        } else if (IsOperator(c)) {
            while (!operators.empty() && Precedence(operators.top()) >= Precedence(c)) {
                postfix << operators.top() << ' ';
                operators.pop();
            }
            operators.push(c);
            expectUnary = true;
        }
    }

    while (!operators.empty()) {
        postfix << operators.top() << ' ';
        operators.pop();
    }
    return postfix.str();
}

int main() {
    string infix;
    getline(cin, infix);

    if (!IsValidinfixession(infix)) {
        cout << "WRONG\n";
        return 0;
    }

    string postfix = ConvertInfixToPostfix(infix);
    int value = EvalPostfix(postfix);

    if (value == INT_MAX) {
        cout << "WRONG\n";
    } else {
        cout << value << '\n';
    }
}