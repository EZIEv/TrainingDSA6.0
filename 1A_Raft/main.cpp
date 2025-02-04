#include <iostream>
#include <string>

using namespace std;

string FindNearestSide(int x1, int y1, int x2, int y2, int x, int y) {
    if (x <= x1 && y >= y2) {
        return "NW"s;
    } else if (x < x1 && y > y1 && y < y2) {
        return "W"s;
    } else if (x <= x1 && y <= y1) {
        return "SW"s;
    } else if (x > x1 && x < x2 && y > y2) {
        return "N"s;
    } else if (x > x1 && x < x2 && y < y1) {
        return "S"s;
    } else if (x >= x2 && y >= y2) {
        return "NE"s;
    } else if (x > x2 && y > y1 && y < y2) {
        return "E"s;
    } else if (x >= x2 && y <= y1) {
        return "SE"s;
    }

    return ""s;
}

int main() {
    int x1, y1, x2, y2, x, y;
    cin >> x1 >> y1 >> x2 >> y2 >> x >> y;

    cout << FindNearestSide(x1, y1, x2, y2, x, y);
}