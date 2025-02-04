#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Coords {
    int x;
    int y;
};

struct Rectangle {
    Coords down_left;
    Coords up_right;
};

Rectangle FindInnerRectCoords(const vector<string>& lines, const Rectangle& outer_rect, bool is_on) {
    char element = (is_on ? '#' : '.');
    Rectangle inner_rect = {{-1, static_cast<int>(lines.size())}, {static_cast<int>(lines.size()), -1}};

    for (int i = outer_rect.up_right.x; i <= outer_rect.down_left.x; ++i) {
        for (int j = outer_rect.down_left.y; j <= outer_rect.up_right.y; ++j) {
            if (lines[i][j] == element && inner_rect.down_left.x < i) {
                inner_rect.down_left.x = i;
            }
            if (lines[i][j] == element && inner_rect.down_left.y > j) {
                inner_rect.down_left.y = j;
            }
            if (lines[i][j] == element && inner_rect.up_right.x > i) {
                inner_rect.up_right.x = i;
            }
            if (lines[i][j] == element && inner_rect.up_right.y < j) {
                inner_rect.up_right.y = j;
            }
        }
    }

    return inner_rect;
}

bool IsP(Rectangle diod_on_rect_1, Rectangle diod_off_rect_2, Rectangle diod_on_rect_2, Rectangle diod_off_rect_3) {
    return (diod_on_rect_1.down_left.x == diod_off_rect_2.down_left.x && diod_off_rect_2.down_left.x >= diod_on_rect_2.down_left.x + 1 &&
            diod_on_rect_2.down_left.x + 1 > diod_off_rect_3.down_left.x && diod_off_rect_3.down_left.x >= diod_off_rect_3.up_right.x &&
            diod_off_rect_3.up_right.x > diod_on_rect_1.up_right.x && diod_on_rect_1.down_left.y < diod_off_rect_2.down_left.y && 
            diod_off_rect_2.down_left.y == diod_on_rect_2.down_left.y && diod_on_rect_2.down_left.y <= diod_off_rect_3.up_right.y && 
            diod_off_rect_3.up_right.y < diod_off_rect_2.up_right.y && diod_off_rect_2.up_right.y == diod_on_rect_1.up_right.y);
}

bool IsH(Rectangle diod_on_rect_1, Rectangle diod_off_rect_2, Rectangle diod_on_rect_2) {
    return (diod_on_rect_1.down_left.x == diod_off_rect_2.down_left.x && diod_off_rect_2.down_left.x >= diod_on_rect_2.down_left.x + 1 &&
            diod_on_rect_2.down_left.x + 1 > diod_on_rect_2.up_right.x - 1 && diod_on_rect_2.up_right.x - 1 >= diod_off_rect_2.up_right.x &&
            diod_off_rect_2.up_right.x == diod_on_rect_1.up_right.x && diod_on_rect_1.down_left.y < diod_off_rect_2.down_left.y && 
            diod_off_rect_2.down_left.y == diod_on_rect_2.down_left.y && diod_on_rect_2.down_left.y <= diod_on_rect_2.up_right.y && 
            diod_on_rect_2.up_right.y == diod_off_rect_2.up_right.y && diod_off_rect_2.up_right.y < diod_on_rect_1.up_right.y);
}

bool IsO(Rectangle diod_on_rect_1, Rectangle diod_off_rect_2) {
    return (diod_on_rect_1.down_left.x > diod_off_rect_2.down_left.x && diod_off_rect_2.down_left.x >= diod_off_rect_2.up_right.x &&
            diod_off_rect_2.up_right.x > diod_on_rect_1.up_right.x && diod_on_rect_1.down_left.y < diod_off_rect_2.down_left.y && 
            diod_off_rect_2.down_left.y <= diod_off_rect_2.up_right.y && diod_off_rect_2.up_right.y < diod_on_rect_1.up_right.y);
}

bool IsC(Rectangle diod_on_rect_1, Rectangle diod_off_rect_2) {
    return (diod_on_rect_1.down_left.x > diod_off_rect_2.down_left.x && diod_off_rect_2.down_left.x >= diod_off_rect_2.up_right.x &&
            diod_off_rect_2.up_right.x > diod_on_rect_1.up_right.x && diod_on_rect_1.down_left.y < diod_off_rect_2.down_left.y && 
            diod_off_rect_2.down_left.y <= diod_off_rect_2.up_right.y && diod_off_rect_2.up_right.y == diod_on_rect_1.up_right.y);
}

bool IsL(Rectangle diod_on_rect_1, Rectangle diod_off_rect_2) {
    return (diod_on_rect_1.down_left.x > diod_off_rect_2.down_left.x && diod_off_rect_2.down_left.x >= diod_off_rect_2.up_right.x &&
            diod_off_rect_2.up_right.x == diod_on_rect_1.up_right.x && diod_on_rect_1.down_left.y < diod_off_rect_2.down_left.y && 
            diod_off_rect_2.down_left.y <= diod_off_rect_2.up_right.y && diod_off_rect_2.up_right.y == diod_on_rect_1.up_right.y);
}

string DetermineLetter(const vector<string>& lines) {
    Rectangle diod_off_rect_1 = {{lines.size() - 1, 0}, {0, lines.size() - 1}};
    Rectangle diod_on_rect_1 = FindInnerRectCoords(lines, diod_off_rect_1, true);
    if (diod_on_rect_1.down_left.x != -1) {
        Rectangle diod_off_rect_2 = FindInnerRectCoords(lines, diod_on_rect_1, false);
        if (diod_off_rect_2.down_left.x != -1) {
            Rectangle diod_on_rect_2 = FindInnerRectCoords(lines, diod_off_rect_2, true);
            if (diod_on_rect_2.down_left.x != -1) {
                Rectangle diod_off_rect_3 = FindInnerRectCoords(lines, diod_on_rect_2, false);
                if (diod_off_rect_3.down_left.x != -1) {
                    Rectangle diod_on_rect_3 = FindInnerRectCoords(lines, diod_off_rect_3, true);
                    if (diod_on_rect_3.down_left.x != -1) {
                        return "X"s;
                    } else {
                        if (IsP(diod_on_rect_1, diod_off_rect_2, diod_on_rect_2, diod_off_rect_3)) {
                            return "P"s;
                        } else {
                            return "X"s;
                        }
                    }
                } else {
                    if (IsH(diod_on_rect_1, diod_off_rect_2, diod_on_rect_2)) {
                            return "H"s;
                    } else {
                        return "X"s;
                    }
                }
            } else {
                if (IsO(diod_on_rect_1, diod_off_rect_2)) {
                    return "O"s;
                } else if (IsC(diod_on_rect_1, diod_off_rect_2)) {
                    return "C"s;
                } else if (IsL(diod_on_rect_1, diod_off_rect_2)) {
                    return "L"s;
                } else {
                    return "X"s;
                }
            }
        } else {
            return "I"s; 
        }
    } else {
        return "X"s;
    }
}

int main() {
    int n;
    cin >> n;

    vector<string> lines;
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;
        lines.push_back(line);
    }

    cout << DetermineLetter(lines) << endl;
}