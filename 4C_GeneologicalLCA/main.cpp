#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

void FindSetOfParents(const string& name, map<string, string>& relations, set<string>& parents) {
    parents.insert(name);
    if (!relations.contains(name)) {
        return;
    }
    FindSetOfParents(relations[name], relations, parents);
}

string FindLCA(const string& name, map<string, string>& relations, set<string>& parents) {
    if (!relations.contains(name)) {
        return name;
    }
    if (parents.contains(name)) {
        return name;
    }
    return FindLCA(relations[name], relations, parents);
}

int main() {
    int n;
    cin >> n;
    
    map<string, string> relations;
    for (int i = 0; i < n - 1; ++i) {
        string child, parent;
        cin >> child >> parent;
        relations[child] = parent;
    }

    string temp;
    getline(cin, temp);

    string query;
    while (getline(cin, query)) {
        istringstream str(query);
        string child1, child2;
        str >> child1 >> child2;

        set<string> parents;
        FindSetOfParents(child1, relations, parents);
        cout << FindLCA(child2, relations, parents) << endl;
    }
}