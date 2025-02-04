#include <iostream>
#include <map>
#include <string>

using namespace std;

int FindHeights(const string& child, map<string, string>& relations, map<string, int>& heights) {
    if (heights.contains(child)) {
        return heights[child];
    }
    if (!relations.contains(child)) {
        return heights[child] = 0;
    }
    return heights[child] = FindHeights(relations[child], relations, heights) + 1;
}

int main() {
    int n;
    cin >> n;

    map<string, string> relations;
    map<string, int> heights;

    for (int i = 0; i < n - 1; ++i) {
        string child;
        string parent;
        cin >> child >> parent;
        relations[child] = parent;
    }

    for (const auto& [child, parent] : relations) {
        FindHeights(parent, relations, heights);
    }
    for (const auto& [child, parent] : relations) {
        FindHeights(child, relations, heights);
    }

    for (const auto& [name, height] : heights) {
        cout << name << ' ' << height << endl;
    }
}