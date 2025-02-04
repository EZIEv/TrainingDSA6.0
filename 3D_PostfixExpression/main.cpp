#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

int EvalPostfix(const string& postfix) {
    stringstream str_stream(postfix);

    string str;
    stack<int> numbers;
    int num1, num2;
    while (str_stream >> str) {
        if (str == "+"s) {
            num2 = numbers.top();
            numbers.pop();
            num1 = numbers.top();
            numbers.pop();
            numbers.push(num1 + num2);
        } else if (str == "-"s) {
            num2 = numbers.top();
            numbers.pop();
            num1 = numbers.top();
            numbers.pop();
            numbers.push(num1 - num2);
        } else if (str == "*"s) {
            num2 = numbers.top();
            numbers.pop();
            num1 = numbers.top();
            numbers.pop();
            numbers.push(num1 * num2);
        } else {
            numbers.push(stoi(str));
        }
    }

    return numbers.top();
}

int main() {
    string postfix;
    getline(cin, postfix);
    cout << EvalPostfix(postfix);
}