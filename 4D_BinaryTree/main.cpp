#include <iostream>
#include <string>

using namespace std;

struct TreeNode {
    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}

    int value;
    TreeNode* left;
    TreeNode* right;
};

bool Add(TreeNode*& root, int value) {
    if (!root) {
        root = new TreeNode(value);
        return true;
    }
    if (value == root->value) {
        return false;
    }
    if (value < root->value) {
        return Add(root->left, value);
    } else {
        return Add(root->right, value);
    }
}

bool Search(TreeNode* root, int value) {
    if (!root) {
        return false;
    }
    if (value == root->value) {
        return true;
    }
    if (value < root->value) {
        return Search(root->left, value);
    } else {
        return Search(root->right, value);
    }
}

void PrintTree(TreeNode* root, int depth = 0) {
    if (!root) {
        return;
    }
    PrintTree(root->left, depth + 1);
    cout << string(depth, '.') << root->value << endl;
    PrintTree(root->right, depth + 1);
}

int main() {
    TreeNode* root = nullptr;
    string command;
    while (cin >> command) {
        if (command == "ADD") {
            int value;
            cin >> value;
            if (Add(root, value)) {
                cout << "DONE" << endl;
            } else {
                cout << "ALREADY" << endl;
            }
        } else if (command == "SEARCH") {
            int value;
            cin >> value;
            if (Search(root, value)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else if (command == "PRINTTREE") {
            PrintTree(root);
        }
    }
}
