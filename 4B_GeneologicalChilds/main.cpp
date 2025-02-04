#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

int FindChilds(const string& name, map<string, vector<string>>& relations, map<string, int>& childs) {
    if (childs.contains(name)) {
        return childs[name];
    }
    if (!relations.contains(name)) {
        return childs[name] = 0;
    }
    childs[name] = relations[name].size();
    for (const string& next_name : relations[name]) {
        childs[name] += FindChilds(next_name, relations, childs);
    }
    return childs[name];
}

int main() {
    int n;
    cin >> n;

    map<string, vector<string>> relations;
    map<string, int> childs;

    for (int i = 0; i < n - 1; ++i) {
        string child;
        string parent;
        cin >> child >> parent;
        relations[parent].push_back(child);
    }

    for (const auto& [parent, par_childs] : relations) {
        for (const string& child : par_childs) {
            FindChilds(child, relations, childs);
        }
    }
    for (const auto& [parent, child] : relations) {
        FindChilds(parent, relations, childs);
    }

    for (const auto& [name, n] : childs) {
        cout << name << ' ' << n << endl;
    }
}