#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <glut.h>

using namespace std;

/*                                              _______
        0 1 2                                  |       |
        3 4 5                                  |  up   |
        6 7 8                          _______ |_______| _______  _______
 0 1 2  0 1 2  0 1 2  0 1 2           |       ||       ||       ||       |
 3 4 5  3 4 5  3 4 5  3 4 5           | left  || front || right || back  |
 6 7 8  6 7 8  6 7 8  6 7 8           |_______||_______||_______||_______|
        0 1 2                                  |       |
        3 4 5                                  | down  |
        6 7 8                                  |_______|
*/


ofstream out("Cube.out");

class Cube {
private:
    char left[3][3], right[3][3], up[3][3], front[3][3], back[3][3], down[3][3];

public:
    Cube() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                left[i][j] = 'g';
                front[i][j] = 'w';
                right[i][j] = 'b';
                back[i][j] = 'y';
                up[i][j] = 'o';
                down[i][j] = 'r';
            }
        }
    }

    bool colors = true;
    bool check_cube() {
        return colors;
    }

    void show() {
        out << endl;
        for (int i = 0; i < 3; i++) {
            out << "    ";
            for (int j = 0; j < 3; j++) {
                out << up[i][j];
            }
            out << endl;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                out << left[i][j];
            }

            out << " ";

            for (int j = 0; j < 3; j++) {
                out << front[i][j];
            }

            out << " ";

            for (int j = 0; j < 3; j++) {
                out << right[i][j];
            }

            out << " ";

            for (int j = 0; j < 3; j++) {
                out << back[i][j];
            }

            out << endl;
        }

        for (int i = 0; i < 3; i++) {
            out << "    ";
            for (int j = 0; j < 3; j++) {
                out << down[i][j];
            }
            out << endl;
        }

        out << endl;
    }

    void save(string str) {
        ofstream fout(str);

        for (int i = 0; i < 3; i++) {
            fout << "    ";
            for (int j = 0; j < 3; j++) {
                fout << up[i][j];
            }
            fout << endl;
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                fout << left[i][j];
            }

            fout << " ";

            for (int j = 0; j < 3; j++) {
                fout << front[i][j];
            }

            fout << " ";

            for (int j = 0; j < 3; j++) {
                fout << right[i][j];
            }

            fout << " ";

            for (int j = 0; j < 3; j++) {
                fout << back[i][j];
            }

            fout << endl;
        }

        for (int i = 0; i < 3; i++) {
            fout << "    ";
            for (int j = 0; j < 3; j++) {
                fout << down[i][j];
            }
            fout << endl;
        }

        fout << endl;

        fout.close();
    }

    void read() {
        ifstream fin("cube.in");
        int red = 0, white = 0, yellow = 0, blue = 0, green = 0, orange = 0;
        for (int i = 0; i < 6; i++) {  
            char tmp[3][3];
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    fin >> tmp[j][k];
                    if (tmp[j][k] == 'r') red++;
                    if (tmp[j][k] == 'w') white++;
                    if (tmp[j][k] == 'o') orange++;
                    if (tmp[j][k] == 'b') blue++;
                    if (tmp[j][k] == 'g') green++;
                    if (tmp[j][k] == 'y') yellow++;
                }
            }
            
            if (tmp[1][1] == 'w') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        front[j][k] = tmp[j][k];
                    }
                }
            }
            if (tmp[1][1] == 'b') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        right[j][k] = tmp[j][k];
                    }
                }
            }
            if (tmp[1][1] == 'g') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        left[j][k] = tmp[j][k];
                    }
                }
            }
            if (tmp[1][1] == 'y') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        back[j][k] = tmp[j][k];
                    }
                }
            }
            if (tmp[1][1] == 'o') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        up[j][k] = tmp[j][k];
                    }
                }
            }
            if (tmp[1][1] == 'r') {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        down[j][k] = tmp[j][k];
                    }
                }
            }
        }
        if (red != 9 || white != 9 || yellow != 9 || blue != 9 || green != 9 || orange != 9) colors = false;

        fin.close();
    }
    //повороты по часовой стрелке

    void Left() {
        out << "L";
        int k = left[0][0];
        int c;
        int l;

        left[0][0] = left[2][0];
        left[2][0] = left[2][2];
        left[2][2] = left[0][2];
        left[0][2] = k;

        k = left[0][1];

        left[0][1] = left[1][0];
        left[1][0] = left[2][1];
        left[2][1] = left[1][2];
        left[1][2] = k;

        k = back[0][2];
        c = back[1][2];
        l = back[2][2];

        back[0][2] = down[2][0];
        back[1][2] = down[1][0];
        back[2][2] = down[0][0];

        down[2][0] = front[2][0];
        down[1][0] = front[1][0];
        down[0][0] = front[0][0];

        front[2][0] = up[2][0];
        front[1][0] = up[1][0];
        front[0][0] = up[0][0];

        up[2][0] = k;
        up[1][0] = c;
        up[0][0] = l;

      
    }

    void Right() {
        out << "R";
        int k = right[0][0];
        int c;
        int l;

        right[0][0] = right[2][0];
        right[2][0] = right[2][2];
        right[2][2] = right[0][2];
        right[0][2] = k;

        k = right[0][1];

        right[0][1] = right[1][0];
        right[1][0] = right[2][1];
        right[2][1] = right[1][2];
        right[1][2] = k;

        k = back[0][0];
        c = back[1][0];
        l = back[2][0];

        back[0][0] = up[2][2];
        back[1][0] = up[1][2];
        back[2][0] = up[0][2];

        up[2][2] = front[2][2];
        up[1][2] = front[1][2];
        up[0][2] = front[0][2];

        front[2][2] = down[2][2];
        front[1][2] = down[1][2];
        front[0][2] = down[0][2];

        down[2][2] = k;
        down[1][2] = c;
        down[0][2] = l;

       
    }

    void Front() {
        out << "F";
        int k = front[0][0];
        int c;
        int l;

        front[0][0] = front[2][0];
        front[2][0] = front[2][2];
        front[2][2] = front[0][2];
        front[0][2] = k;

        k = front[0][1];

        front[0][1] = front[1][0];
        front[1][0] = front[2][1];
        front[2][1] = front[1][2];
        front[1][2] = k;

        k = up[2][0];
        c = up[2][1];
        l = up[2][2];

        up[2][0] = left[2][2];
        up[2][1] = left[1][2];
        up[2][2] = left[0][2];

        left[2][2] = down[0][2];
        left[1][2] = down[0][1];
        left[0][2] = down[0][0];

        down[0][2] = right[0][0];
        down[0][1] = right[1][0];
        down[0][0] = right[2][0];

        right[0][0] = k;
        right[1][0] = c;
        right[2][0] = l;

    }

    void Back() {
        out << "B";
        int k = back[0][0];
        int c;
        int l;

        back[0][0] = back[2][0];
        back[2][0] = back[2][2];
        back[2][2] = back[0][2];
        back[0][2] = k;

        k = back[0][1];

        back[0][1] = back[1][0];
        back[1][0] = back[2][1];
        back[2][1] = back[1][2];
        back[1][2] = k;

        k = up[0][0];
        c = up[0][1];
        l = up[0][2];

        up[0][0] = right[0][2];
        up[0][1] = right[1][2];
        up[0][2] = right[2][2];

        right[2][2] = down[2][0];
        right[1][2] = down[2][1];
        right[0][2] = down[2][2];

        down[2][2] = left[2][0];
        down[2][1] = left[1][0];
        down[2][0] = left[0][0];

        left[0][0] = l;
        left[1][0] = c;
        left[2][0] = k;

       
    }

    void Up() {
        out << "U";
        int k = up[0][0];
        int c;
        int l;

        up[0][0] = up[2][0];
        up[2][0] = up[2][2];
        up[2][2] = up[0][2];
        up[0][2] = k;

        k = up[0][1];

        up[0][1] = up[1][0];
        up[1][0] = up[2][1];
        up[2][1] = up[1][2];
        up[1][2] = k;

        k = left[0][0];
        c = left[0][1];
        l = left[0][2];

        left[0][0] = front[0][0];
        left[0][1] = front[0][1];
        left[0][2] = front[0][2];

        front[0][0] = right[0][0];
        front[0][1] = right[0][1];
        front[0][2] = right[0][2];

        right[0][0] = back[0][0];
        right[0][1] = back[0][1];
        right[0][2] = back[0][2];

        back[0][0] = k;
        back[0][1] = c;
        back[0][2] = l;

    }

    void Down() {
        out << "D";
        int k = down[0][0];
        int c;
        int l;

        down[0][0] = down[2][0];
        down[2][0] = down[2][2];
        down[2][2] = down[0][2];
        down[0][2] = k;

        k = down[0][1];

        down[0][1] = down[1][0];
        down[1][0] = down[2][1];
        down[2][1] = down[1][2];
        down[1][2] = k;

        k = left[2][0];
        c = left[2][1];
        l = left[2][2];

        left[2][0] = back[2][0];
        left[2][1] = back[2][1];
        left[2][2] = back[2][2];

        back[2][0] = right[2][0];
        back[2][1] = right[2][1];
        back[2][2] = right[2][2];

        right[2][0] = front[2][0];
        right[2][1] = front[2][1];
        right[2][2] = front[2][2];

        front[2][0] = k;
        front[2][1] = c;
        front[2][2] = l;

    }
    //повороты против часовой стрелки

    void LeftB() {
        out << "L'";
        int k = left[0][0];
        int c;
        int l;

        left[0][0] = left[0][2];
        left[0][2] = left[2][2];
        left[2][2] = left[2][0];
        left[2][0] = k;

        k = left[0][1];

        left[0][1] = left[1][2];
        left[1][2] = left[2][1];
        left[2][1] = left[1][0];
        left[1][0] = k;

        k = back[0][2];
        c = back[1][2];
        l = back[2][2];

        back[0][2] = up[2][0];
        back[1][2] = up[1][0];
        back[2][2] = up[0][0];

        up[2][0] = front[2][0];
        up[1][0] = front[1][0];
        up[0][0] = front[0][0];

        front[2][0] = down[2][0];
        front[1][0] = down[1][0];
        front[0][0] = down[0][0];

        down[2][0] = k;
        down[1][0] = c;
        down[0][0] = l;

    }

    void RightB() {
        out << "R'";
        int k = right[0][0];
        int c;
        int l;

        right[0][0] = right[0][2];
        right[0][2] = right[2][2];
        right[2][2] = right[2][0];
        right[2][0] = k;

        k = right[0][1];

        right[0][1] = right[1][2];
        right[1][2] = right[2][1];
        right[2][1] = right[1][0];
        right[1][0] = k;

        k = back[0][0];
        c = back[1][0];
        l = back[2][0];

        back[0][0] = down[2][2];
        back[1][0] = down[1][2];
        back[2][0] = down[0][2];

        down[2][2] = front[2][2];
        down[1][2] = front[1][2];
        down[0][2] = front[0][2];

        front[2][2] = up[2][2];
        front[1][2] = up[1][2];
        front[0][2] = up[0][2];

        up[2][2] = k;
        up[1][2] = c;
        up[0][2] = l;

    }

    void FrontB() {
        out << "F'";
        int k = front[0][0];
        int c;
        int l;

        front[0][0] = front[0][2];
        front[0][2] = front[2][2];
        front[2][2] = front[2][0];
        front[2][0] = k;

        k = front[0][1];

        front[0][1] = front[1][2];
        front[1][2] = front[2][1];
        front[2][1] = front[1][0];
        front[1][0] = k;

        k = up[2][0];
        c = up[2][1];
        l = up[2][2];

        up[2][0] = right[0][0];
        up[2][1] = right[1][0];
        up[2][2] = right[2][0];

        right[0][0] = down[0][2];
        right[1][0] = down[0][1];
        right[2][0] = down[0][0];

        down[0][2] = left[2][2];
        down[0][1] = left[1][2];
        down[0][0] = left[0][2];

        left[0][2] = l;
        left[1][2] = c;
        left[2][2] = k;

    }

    void BackB() {
        out << "B'";
        int k = back[0][0];
        int c;
        int l;

        back[0][0] = back[0][2];
        back[0][2] = back[2][2];
        back[2][2] = back[2][0];
        back[2][0] = k;

        k = back[0][1];

        back[0][1] = back[1][2];
        back[1][2] = back[2][1];
        back[2][1] = back[1][0];
        back[1][0] = k;

        k = up[0][0];
        c = up[0][1];
        l = up[0][2];

        up[0][0] = left[2][0];
        up[0][1] = left[1][0];
        up[0][2] = left[0][0];

        left[2][0] = down[2][2];
        left[1][0] = down[2][1];
        left[0][0] = down[2][0];

        down[2][2] = right[0][2];
        down[2][1] = right[1][2];
        down[2][0] = right[2][2];

        right[0][2] = k;
        right[1][2] = c;
        right[2][2] = l;

    }

    void UpB() {
        out << "U'";
        int k = up[0][0];
        int c;
        int l;

        up[0][0] = up[0][2];
        up[0][2] = up[2][2];
        up[2][2] = up[2][0];
        up[2][0] = k;

        k = up[0][1];

        up[0][1] = up[1][2];
        up[1][2] = up[2][1];
        up[2][1] = up[1][0];
        up[1][0] = k;

        k = left[0][0];
        c = left[0][1];
        l = left[0][2];

        left[0][0] = back[0][0];
        left[0][1] = back[0][1];
        left[0][2] = back[0][2];

        back[0][0] = right[0][0];
        back[0][1] = right[0][1];
        back[0][2] = right[0][2];

        right[0][0] = front[0][0];
        right[0][1] = front[0][1];
        right[0][2] = front[0][2];

        front[0][0] = k;
        front[0][1] = c;
        front[0][2] = l;

    }

    void DownB() {
        out << "D'";
        int k = down[0][0];
        int c;
        int l;

        down[0][0] = down[0][2];
        down[0][2] = down[2][2];
        down[2][2] = down[2][0];
        down[2][0] = k;

        k = down[0][1];

        down[0][1] = down[1][2];
        down[1][2] = down[2][1];
        down[2][1] = down[1][0];
        down[1][0] = k;

        k = left[2][0];
        c = left[2][1];
        l = left[2][2];

        left[2][0] = front[2][0];
        left[2][1] = front[2][1];
        left[2][2] = front[2][2];

        front[2][0] = right[2][0];
        front[2][1] = right[2][1];
        front[2][2] = right[2][2];

        right[2][0] = back[2][0];
        right[2][1] = back[2][1];
        right[2][2] = back[2][2];

        back[2][0] = k;
        back[2][1] = c;
        back[2][2] = l;

    }

    void rotation() {
        string k;
        int count;
        cin >> k >> count;

        if (k == "left") {
            for (int i = 0; i < count; i++) {
                Left();
                show();
            }
        }
        else if (k == "right") {
            for (int i = 0; i < count; i++) {
                Right();
                show();
            }
        }
        else if (k == "front") {
            for (int i = 0; i < count; i++) {
                Front();
                show();
            }
        }
        else if (k == "back") {
            for (int i = 0; i < count; i++) {
                Back();
                show();
            }
        }
        else if (k == "up") {
            for (int i = 0; i < count; i++) {
                Up();
                show();
            }
        }
        else if (k == "down") {
            for (int i = 0; i < count; i++) {
                Down();
                show();
            }
        }
        else if (k == "leftB") {
            for (int i = 0; i < count; i++) {
                LeftB();
                show();
            }
        }
        else if (k == "rightB") {
            for (int i = 0; i < count; i++) {
                RightB();
                show();
            }
        }
        else if (k == "frontB") {
            for (int i = 0; i < count; i++) {
                FrontB();
                show();
            }
        }
        else if (k == "backB") {
            for (int i = 0; i < count; i++) {
                BackB();
                show();
            }
        }
        else if (k == "upB") {
            for (int i = 0; i < count; i++) {
                UpB();
                show();
            }
        }
        else if (k == "downB") {
            for (int i = 0; i < count; i++) {
                DownB();
                show();
            }
        }
    }

    void Random() {
        srand(time(0));
        int k = rand() % 50 + 15;
        int l;
        int rotation;

        for (int i = 0; i < k; i++) {
            l = rand() % 2;
            rotation = rand() % 5;

            if (rotation == 0) {
                for (int j = 0; j < l; j++) {
                    Left();
                }
            }
            else if (rotation == 1) {
                for (int j = 0; j < l; j++) {
                    Right();
                }
            }
            else if (rotation == 2) {
                for (int j = 0; j < l; j++) {
                    Front();
                }
            }
            else if (rotation == 3) {
                for (int j = 0; j < l; j++) {
                    Back();
                }
            }
            else if (rotation == 4) {
                for (int j = 0; j < l; j++) {
                    Up();
                }
            }
            else if (rotation == 5) {
                for (int j = 0; j < l; j++) {
                    Down();
                }
            }
        }

        cout << k << " different turns for random cube" << endl;
        show();
    }

    bool check() {
        bool ch = true;

        if (up[0][1] != 'r') {
            ch = false;
        }
        else if (up[1][2] != 'r') {
            ch = false;
        }
        else if (up[2][1] != 'r') {
            ch = false;
        }
        else if (up[1][0] != 'r') {
            ch = false;
        }

        return ch;
    }

    bool check1() {
        bool ch = true;

        if (up[2][1] != 'r' || front[0][1] != 'w') {
            ch = false;
        }

        return ch;
    }

    bool check2() {
        bool ch = true;

        if (up[1][2] != 'r' || right[0][1] != 'b') {
            ch = false;
        }

        return ch;
    }

    bool check3() {
        bool ch = true;

        if (up[0][1] != 'r' || back[0][1] != 'y') {
            ch = false;
        }

        return ch;
    }

    bool check4() {
        bool ch = true;

        if (up[1][0] != 'r' || left[0][1] != 'g') {
            ch = false;
        }

        return ch;
    }

    bool orange_cross_check() {
        bool ch = true;

        if (up[0][1] != 'o' || up[1][2] != 'o' || up[2][1] != 'o' || up[1][0] != 'o') {
            ch = false;
        }

        return ch;
    }

    bool check_orange_right_cross() {
        bool ch = true;

        if (up[0][1] != 'o' || up[1][2] != 'o' || up[2][1] != 'o' || up[1][0] != 'o') {
            ch = false;
        }

        if (front[0][1] != 'w' || right[0][1] != 'b' || back[0][1] != 'y' || left[0][1] != 'g') {
            ch = false;
        }

        return ch;
    }

    bool check_middle() {
        bool ch = true;

        if (front[1][0] != 'w' || front[1][2] != 'w' || right[1][0] != 'b' || right[1][2] != 'b' || back[1][0] != 'y' || back[1][2] != 'y' || left[1][0] != 'g' || left[1][2] != 'g') {
            ch = false;
        }

        return ch;
    }

    bool check_edge() {
        bool ch = true;

        for (int i = 0; i < 3; i++) {
            if (front[2][i] != 'w' || right[2][i] != 'b' || back[2][i] != 'y' || left[2][i] != 'g') {
                ch = false;
            }
        }

        if (down[0][0] != 'r' || down[0][2] != 'r' || down[2][0] != 'r' || down[2][2] != 'r') {
            ch = false;
        }

        return ch;
    }

    bool assembly_check() {
        bool ch = true;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (front[i][j] != 'w' || right[i][j] != 'b' || back[i][j] != 'y' || left[i][j] != 'g' || up[i][j] != 'o' || down[i][j] != 'r') {
                    ch = false;
                }
            }
        }

        return ch;
    }

    bool check_upper_edges() {
        return ((up[2][2] == 'o' && front[0][2] == 'w' && right[0][0] == 'b') ||
            (up[2][2] == 'o' && front[0][2] == 'b' && right[0][0] == 'w') ||
            (up[2][2] == 'w' && front[0][2] == 'o' && right[0][0] == 'b') ||
            (up[2][2] == 'w' && front[0][2] == 'b' && right[0][0] == 'o') ||
            (up[2][2] == 'b' && front[0][2] == 'w' && right[0][0] == 'o') ||
            (up[2][2] == 'b' && front[0][2] == 'o' && right[0][0] == 'w')) &&
            ((front[0][0] == 'w' && left[0][2] == 'g' && up[2][0] == 'o') ||
                (front[0][0] == 'w' && left[0][2] == 'o' && up[2][0] == 'g') ||
                (front[0][0] == 'g' && left[0][2] == 'o' && up[2][0] == 'w') ||
                (front[0][0] == 'g' && left[0][2] == 'w' && up[2][0] == 'o') ||
                (front[0][0] == 'o' && left[0][2] == 'g' && up[2][0] == 'w') ||
                (front[0][0] == 'o' && left[0][2] == 'w' && up[2][0] == 'g')) &&
            ((up[0][2] == 'o' && right[0][2] == 'b' && back[0][0] == 'y') ||
                (up[0][2] == 'o' && right[0][2] == 'y' && back[0][0] == 'b') ||
                (up[0][2] == 'b' && right[0][2] == 'o' && back[0][0] == 'y') ||
                (up[0][2] == 'b' && right[0][2] == 'y' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'b' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'o' && back[0][0] == 'b')) &&
            ((up[0][0] == 'o' && back[0][2] == 'y' && left[0][0] == 'g') ||
                (up[0][0] == 'o' && back[0][2] == 'g' && left[0][0] == 'y') ||
                (up[0][0] == 'g' && back[0][2] == 'y' && left[0][0] == 'o') ||
                (up[0][0] == 'g' && back[0][2] == 'o' && left[0][0] == 'y') ||
                (up[0][0] == 'y' && back[0][2] == 'o' && left[0][0] == 'g') ||
                (up[0][0] == 'y' && back[0][2] == 'g' && left[0][0] == 'o'));
    }


    void Front_pif_paf() {
        Front();
        Up();
        FrontB();
        UpB();
    }

    void Back_pif_paf() {
        Back();
        Up();
        BackB();
        UpB();
    }

    void Right_pif_paf() {
        Right();
        Up();
        RightB();
        UpB();
    }

    void Left_pif_paf() {
        Left();
        Up();
        LeftB();
        UpB();
    }


    void first() {
        //Первый этап сборки
        while (!check()) {
            show();
            if (front[1][2] == 'r' && up[1][2] != 'r') {
                Right();
            }
            else if (front[1][2] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
            }

            if (front[1][0] == 'r' && up[1][0] != 'r') {
                LeftB();
            }
            else if (front[1][0] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                LeftB();
            }

            if (down[1][0] == 'r' && up[1][0] != 'r') {
                LeftB();
                LeftB();
            }
            else if (down[1][0] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                LeftB();
                LeftB();
            }

            if (down[1][2] == 'r' && up[1][2] != 'r') {
                Right();
                Right();
            }
            else if (down[1][2] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
                Right();
            }

            if (left[1][0] == 'r' && up[0][1] != 'r') {
                BackB();
            }
            else if (left[1][0] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                BackB();
            }

            if (left[1][2] == 'r' && up[2][1] != 'r') {
                Front();
            }
            else if (left[1][2] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Front();
            }

            if (right[1][0] == 'r' && up[2][1] != 'r') {
                FrontB();
            }
            else if (right[1][0] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                FrontB();
            }

            if (right[1][2] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (right[1][2] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (back[1][0] == 'r' && up[1][2] != 'r') {
                RightB();
            }
            else if (back[1][0] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                RightB();
            }

            if (back[1][2] == 'r' && up[1][0] != 'r') {
                Left();
            }
            else if (back[1][2] == 'r') {
                while (up[1][0] == 'r') {
                    Up();
                }
                Left();
            }

            if (front[0][1] == 'r' && up[1][2] != 'r') {
                Front();
                Right();
            }
            else if (front[0][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Front();
                Right();
            }

            if (front[2][1] == 'r' && up[1][2] != 'r') {
                FrontB();
                Right();
            }
            else if (front[2][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                FrontB();
                Right();
            }

            if (left[0][1] == 'r' && up[2][1] != 'r') {
                Left();
                Front();
            }
            else if (left[0][1] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Left();
                Front();
            }

            if (left[2][1] == 'r' && up[0][1] != 'r') {
                Left();
                BackB();
            }
            else if (left[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Left();
                BackB();
            }

            if (right[0][1] == 'r' && up[0][1] != 'r') {
                Right();
                Back();
            }
            else if (right[0][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Right();
                Back();
            }

            if (right[2][1] == 'r' && up[1][2] != 'r') {
                Right();
            }
            else if (right[2][1] == 'r') {
                while (up[1][2] == 'r') {
                    Up();
                }
                Right();
            }

            if (back[0][1] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (back[0][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (back[2][1] == 'r' && up[0][1] != 'r') {
                Back();
            }
            else if (back[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
            }

            if (down[0][1] == 'r' && up[2][1] != 'r') {
                Front();
                Front();
            }
            else if (down[0][1] == 'r') {
                while (up[2][1] == 'r') {
                    Up();
                }
                Front();
                Front();
            }

            if (down[2][1] == 'r' && up[0][1] != 'r') {
                Back();
                Back();
            }
            else if (down[2][1] == 'r') {
                while (up[0][1] == 'r') {
                    Up();
                }
                Back();
                Back();
            }
        }
        //Правильный крест
        show();
        if (!check1()) {
            while (!check1()) {
                Up();
            }
            Front();
            Front();
        }
        else if (check1()) {
            Front();
            Front();
        }

        if (!check2()) {
            while (!check2()) {
                Up();
            }
            Right();
            Right();
        }
        else if (check2()) {
            Right();
            Right();
        }

        if (!check3()) {
            while (!check3()) {
                Up();
            }
            Back();
            Back();
        }
        else if (check3()) {
            Back();
            Back();
        }

        if (!check4()) {
            while (!check4()) {
                Up();
            }
            Left();
            Left();
        }
        else if (check4()) {
            Left();
            Left();
        }
        

        //Второй этап сборки (первый слой до конца)
        while (!check_edge()) {
            if ((front[0][2] == 'r' && right[0][0] == 'b' && up[2][2] == 'w') || (front[0][2] == 'r' && right[0][0] == 'w' && up[2][2] == 'b')
                || (front[0][2] == 'w' && right[0][0] == 'r' && up[2][2] == 'b') || (front[0][2] == 'w' && right[0][0] == 'b' && up[2][2] == 'r')
                || (front[0][2] == 'b' && right[0][0] == 'r' && up[2][2] == 'w') || (front[0][2] == 'b' && right[0][0] == 'w' && up[2][2] == 'r')) {
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((front[0][2] == 'w' && right[0][0] == 'g' && up[2][2] == 'r') || (front[0][2] == 'w' && right[0][0] == 'r' && up[2][2] == 'g')
                || (front[0][2] == 'r' && right[0][0] == 'w' && up[2][2] == 'g') || (front[0][2] == 'r' && right[0][0] == 'g' && up[2][2] == 'w')
                || (front[0][2] == 'g' && right[0][0] == 'r' && up[2][2] == 'w') || (front[0][2] == 'g' && right[0][0] == 'w' && up[2][2] == 'r')) {
                Up();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((front[0][2] == 'b' && right[0][0] == 'y' && up[2][2] == 'r') || (front[0][2] == 'b' && right[0][0] == 'r' && up[2][2] == 'y')
                || (front[0][2] == 'r' && right[0][0] == 'b' && up[2][2] == 'y') || (front[0][2] == 'r' && right[0][0] == 'y' && up[2][2] == 'b')
                || (front[0][2] == 'y' && right[0][0] == 'b' && up[2][2] == 'r') || (front[0][2] == 'y' && right[0][0] == 'r' && up[2][2] == 'b')) {
                UpB();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((front[0][2] == 'r' && right[0][0] == 'g' && up[2][2] == 'y') || (front[0][2] == 'r' && right[0][0] == 'y' && up[2][2] == 'g')
                || (front[0][2] == 'y' && right[0][0] == 'r' && up[2][2] == 'g') || (front[0][2] == 'y' && right[0][0] == 'g' && up[2][2] == 'r')
                || (front[0][2] == 'g' && right[0][0] == 'y' && up[2][2] == 'r') || (front[0][2] == 'g' && right[0][0] == 'r' && up[2][2] == 'y')) {
                Up();
                Up();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            } //рассмотрен первый угол сверху

            if ((right[0][2] == 'r' && back[0][0] == 'b' && up[0][2] == 'w') || (right[0][2] == 'r' && back[0][0] == 'w' && up[0][2] == 'b')
                || (right[0][2] == 'w' && back[0][0] == 'r' && up[0][2] == 'b') || (right[0][2] == 'w' && back[0][0] == 'b' && up[0][2] == 'r')
                || (right[0][2] == 'b' && back[0][0] == 'r' && up[0][2] == 'w') || (right[0][2] == 'b' && back[0][0] == 'w' && up[0][2] == 'r')) {
                Up();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((right[0][2] == 'w' && back[0][0] == 'g' && up[0][2] == 'r') || (right[0][2] == 'w' && back[0][0] == 'r' && up[0][2] == 'g')
                || (right[0][2] == 'r' && back[0][0] == 'w' && up[0][2] == 'g') || (right[0][2] == 'r' && back[0][0] == 'g' && up[0][2] == 'w')
                || (right[0][2] == 'g' && back[0][0] == 'r' && up[0][2] == 'w') || (right[0][2] == 'g' && back[0][0] == 'w' && up[0][2] == 'r')) {
                Up();
                Up();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((right[0][2] == 'b' && back[0][0] == 'y' && up[0][2] == 'r') || (right[0][2] == 'b' && back[0][0] == 'r' && up[0][2] == 'y')
                || (right[0][2] == 'r' && back[0][0] == 'b' && up[0][2] == 'y') || (right[0][2] == 'r' && back[0][0] == 'y' && up[0][2] == 'b')
                || (right[0][2] == 'y' && back[0][0] == 'b' && up[0][2] == 'r') || (right[0][2] == 'y' && back[0][0] == 'r' && up[0][2] == 'b')) {
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((right[0][2] == 'r' && back[0][0] == 'g' && up[0][2] == 'y') || (right[0][2] == 'r' && back[0][0] == 'y' && up[0][2] == 'g')
                || (right[0][2] == 'y' && back[0][0] == 'r' && up[0][2] == 'g') || (right[0][2] == 'y' && back[0][0] == 'g' && up[0][2] == 'r')
                || (right[0][2] == 'g' && back[0][0] == 'y' && up[0][2] == 'r') || (right[0][2] == 'g' && back[0][0] == 'r' && up[0][2] == 'y')) {
                UpB();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            } //рассмотрен второй угол сверху

            if ((back[0][2] == 'r' && left[0][0] == 'b' && up[0][0] == 'w') || (back[0][2] == 'r' && left[0][0] == 'w' && up[0][0] == 'b')
                || (back[0][2] == 'w' && left[0][0] == 'r' && up[0][0] == 'b') || (back[0][2] == 'w' && left[0][0] == 'b' && up[0][0] == 'r')
                || (back[0][2] == 'b' && left[0][0] == 'r' && up[0][0] == 'w') || (back[0][2] == 'b' && left[0][0] == 'w' && up[0][0] == 'r')) {
                UpB();
                UpB();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((back[0][2] == 'w' && left[0][0] == 'g' && up[0][0] == 'r') || (back[0][2] == 'w' && left[0][0] == 'r' && up[0][0] == 'g')
                || (back[0][2] == 'r' && left[0][0] == 'w' && up[0][0] == 'g') || (back[0][2] == 'r' && left[0][0] == 'g' && up[0][0] == 'w')
                || (back[0][2] == 'g' && left[0][0] == 'r' && up[0][0] == 'w') || (back[0][2] == 'g' && left[0][0] == 'w' && up[0][0] == 'r')) {
                UpB();
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((back[0][2] == 'b' && left[0][0] == 'y' && up[0][0] == 'r') || (back[0][2] == 'b' && left[0][0] == 'r' && up[0][0] == 'y')
                || (back[0][2] == 'r' && left[0][0] == 'b' && up[0][0] == 'y') || (back[0][2] == 'r' && left[0][0] == 'y' && up[0][0] == 'b')
                || (back[0][2] == 'y' && left[0][0] == 'b' && up[0][0] == 'r') || (back[0][2] == 'y' && left[0][0] == 'r' && up[0][0] == 'b')) {
                Up();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((back[0][2] == 'r' && left[0][0] == 'g' && up[0][0] == 'y') || (back[0][2] == 'r' && left[0][0] == 'y' && up[0][0] == 'g')
                || (back[0][2] == 'y' && left[0][0] == 'r' && up[0][0] == 'g') || (back[0][2] == 'y' && left[0][0] == 'g' && up[0][0] == 'r')
                || (back[0][2] == 'g' && left[0][0] == 'y' && up[0][0] == 'r') || (back[0][2] == 'g' && left[0][0] == 'r' && up[0][0] == 'y')) {
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            } //рассмотрен третий угол сверху

            if ((left[0][2] == 'r' && front[0][0] == 'b' && up[2][0] == 'w') || (left[0][2] == 'r' && front[0][0] == 'w' && up[2][0] == 'b')
                || (left[0][2] == 'w' && front[0][0] == 'r' && up[2][0] == 'b') || (left[0][2] == 'w' && front[0][0] == 'b' && up[2][0] == 'r')
                || (left[0][2] == 'b' && front[0][0] == 'r' && up[2][0] == 'w') || (left[0][2] == 'b' && front[0][0] == 'w' && up[2][0] == 'r')) {
                UpB();
                while (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                    Right_pif_paf();
                }
            }

            if ((left[0][2] == 'w' && front[0][0] == 'g' && up[2][0] == 'r') || (left[0][2] == 'w' && front[0][0] == 'r' && up[2][0] == 'g')
                || (left[0][2] == 'r' && front[0][0] == 'w' && up[2][0] == 'g') || (left[0][2] == 'r' && front[0][0] == 'g' && up[2][0] == 'w')
                || (left[0][2] == 'g' && front[0][0] == 'r' && up[2][0] == 'w') || (left[0][2] == 'g' && front[0][0] == 'w' && up[2][0] == 'r')) {
                while (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                    Front_pif_paf();
                }
            }

            if ((left[0][2] == 'b' && front[0][0] == 'y' && up[2][0] == 'r') || (left[0][2] == 'b' && front[0][0] == 'r' && up[2][0] == 'y')
                || (left[0][2] == 'r' && front[0][0] == 'b' && up[2][0] == 'y') || (left[0][2] == 'r' && front[0][0] == 'y' && up[2][0] == 'b')
                || (left[0][2] == 'y' && front[0][0] == 'b' && up[2][0] == 'r') || (left[0][2] == 'y' && front[0][0] == 'r' && up[2][0] == 'b')) {
                Up();
                Up();
                while (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                    Back_pif_paf();
                }
            }

            if ((left[0][2] == 'r' && front[0][0] == 'g' && up[2][0] == 'y') || (left[0][2] == 'r' && front[0][0] == 'y' && up[2][0] == 'g')
                || (left[0][2] == 'y' && front[0][0] == 'r' && up[2][0] == 'g') || (left[0][2] == 'y' && front[0][0] == 'g' && up[2][0] == 'r')
                || (left[0][2] == 'g' && front[0][0] == 'y' && up[2][0] == 'r') || (left[0][2] == 'g' && front[0][0] == 'r' && up[2][0] == 'y')) {
                Up();
                while (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                    Left_pif_paf();
                }
            } //рассмотрен четвертый угол сверху

            if (front[2][2] != 'w' || right[2][0] != 'b' || down[0][2] != 'r') {
                if (front[2][2] == 'r' || right[2][0] == 'r' || down[0][2] == 'r') {
                    Right_pif_paf();
                }
            }

            if (front[2][0] != 'w' || left[2][2] != 'g' || down[0][0] != 'r') {
                if (front[2][0] == 'r' || left[2][2] == 'r' || down[0][0] == 'r') {
                    Front_pif_paf();
                }
            }

            if (back[2][0] != 'y' || right[2][2] != 'b' || down[2][2] != 'r') {
                if (back[2][0] == 'r' || right[2][2] == 'r' || down[2][2] == 'r') {
                    Back_pif_paf();
                }
            }

            if (back[2][2] != 'y' || left[2][0] != 'g' || down[2][0] != 'r') {
                if (back[2][2] == 'r' || left[2][0] == 'r' || down[2][0] == 'r') {
                    Left_pif_paf();
                }
            }
            // первый слой собран  
        }
        
    }
    //собран нижний слой
    

    void second() {
        int p, c;

        while (!check_middle()) {
            c = 0;
            p = -1;
            
            while (c > p) {
                p = c;

                if (front[0][1] == 'w' || right[0][1] == 'w' || back[0][1] == 'w' || left[0][1] == 'w') {
                    if (front[0][1] != 'w') {
                        while (front[0][1] != 'w') {
                            Up();
                        }
                    }

                    if (up[2][1] == 'b') {
                        c++;
                        Up();
                        Right_pif_paf();
                        FrontB();
                        UpB();
                        Front();
                        Up();
                    }
                    else if (up[2][1] == 'g') {
                        c++;
                        UpB();
                        LeftB();
                        UpB();
                        Left();
                        Up();
                        Front_pif_paf();
                    }
                }

                if (front[0][1] == 'b' || right[0][1] == 'b' || back[0][1] == 'b' || left[0][1] == 'b') {
                    if (right[0][1] != 'b') {
                        while (right[0][1] != 'b') {
                            Up();
                        }
                    }

                    if (up[1][2] == 'y') {
                        c++;
                        Up();
                        Back_pif_paf();
                        RightB();
                        UpB();
                        Right();
                        Up();
                    }
                    else if (up[1][2] == 'w') {
                        c++;
                        UpB();
                        FrontB();
                        UpB();
                        Front();
                        Up();
                        Right_pif_paf();
                    }
                }

                if (front[0][1] == 'y' || right[0][1] == 'y' || back[0][1] == 'y' || left[0][1] == 'y') {
                    if (back[0][1] != 'y') {
                        while (back[0][1] != 'y') {
                            Up();
                        }
                    }

                    if (up[0][1] == 'g') {
                        c++;
                        Up();
                        Left_pif_paf();
                        BackB();
                        UpB();
                        Back();
                        Up();
                    }
                    else if (up[0][1] == 'b') {
                        c++;
                        UpB();
                        RightB();
                        UpB();
                        Right();
                        Up();
                        Back_pif_paf();
                    }
                }

                if (front[0][1] == 'g' || right[0][1] == 'g' || back[0][1] == 'g' || left[0][1] == 'g') {
                    if (left[0][1] != 'g') {
                        while (left[0][1] != 'g') {
                            Up();
                        }
                    }

                    if (up[1][0] == 'w') {
                        c++;
                        Up();
                        Front_pif_paf();
                        LeftB();
                        UpB();
                        Left();
                        Up();
                    }
                    else if (up[1][0] == 'y') {
                        c++;
                        UpB();
                        BackB();
                        UpB();
                        Back();
                        Up();
                        Left_pif_paf();
                    }
                }
            }
            
            if (front[1][2] != 'w') {
                Right_pif_paf();
                FrontB();
                UpB();
                Front();
                Up();
            }

            if (right[1][2] != 'b') {
                Back_pif_paf();
                RightB();
                UpB();
                Right();
                Up();
            }

            if (back[1][2] != 'y') {
                Left_pif_paf();
                BackB();
                UpB();
                Back();
                Up();
            }

            if (left[1][2] != 'g') {
                Front_pif_paf();
                LeftB();
                UpB();
                Left();
                Up();
            }
            show();
        }

    }
    //собраны 2 нижних слоя


    void third() {
        while (!orange_cross_check()) {
            if (up[0][1] == 'o' && up[1][2] == 'o' && up[2][1] != 'o' && up[1][0] != 'o') {
                Left();
                Front_pif_paf();
                LeftB();
            }
            else if (up[0][1] == 'o' && up[1][2] != 'o' && up[2][1] == 'o' && up[1][0] != 'o') {
                Left();
                Front_pif_paf();
                LeftB();
            }
            else if (up[0][1] != 'o' && up[1][2] == 'o' && up[2][1] == 'o' && up[1][0] != 'o') {
                Back();
                Left_pif_paf();
                BackB();
            }
            else if (up[0][1] == 'o' && up[1][2] != 'o' && up[2][1] != 'o' && up[1][0] == 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
            else if (up[0][1] != 'o' && up[1][2] == 'o' && up[2][1] != 'o' && up[1][0] == 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
            else if (up[0][1] != 'o' && up[1][2] != 'o' && up[2][1] == 'o' && up[1][0] == 'o') {
                Right();
                Back_pif_paf();
                RightB();
            }
            else if (up[0][1] != 'o' && up[1][2] != 'o' && up[2][1] != 'o' && up[1][0] != 'o') {
                Front();
                Right_pif_paf();
                FrontB();
            }
        } // собран оранжевый крест наверху

        bool ch = false;
        if (check_orange_right_cross())
            ch = true;
        else {
            Up();
            if (check_orange_right_cross())
                ch = true;
            else {
                Up();
                if (check_orange_right_cross())
                    ch = true;
                else {
                    Up();
                    if (check_orange_right_cross())
                        ch = true;
                }
            } // проверка на правильный оранжевый крест
        }

        if (!ch) {
            while (!check_orange_right_cross()) {
                Up();
                if (right[0][1] == 'b' && back[0][1] == 'y') {
                    Right();
                    Up();
                    RightB();
                    Up();
                    Right();
                    Up();
                    Up();
                    RightB();
                    Up();
                }
                else if (right[0][1] == 'b' && front[0][1] == 'w') {
                    Front();
                    Up();
                    FrontB();
                    Up();
                    Front();
                    Up();
                    Up();
                    FrontB();
                    Up();
                }
                else if (front[0][1] == 'w' && left[0][1] == 'g') {
                    Left();
                    Up();
                    LeftB();
                    Up();
                    Left();
                    Up();
                    Up();
                    LeftB();
                    Up();
                }
                else if (left[0][1] == 'g' && back[0][1] == 'y') {
                    Back();
                    Up();
                    BackB();
                    Up();
                    Back();
                    Up();
                    Up();
                    BackB();
                    Up();
                }
                else if (right[0][1] == 'b' && left[0][1] == 'g') {
                    Back();
                    Up();
                    BackB();
                    Up();
                    Back();
                    Up();
                    Up();
                    BackB();
                }
                else if (front[0][1] == 'w' && back[0][1] == 'y') {
                    Right();
                    Up();
                    RightB();
                    Up();
                    Right();
                    Up();
                    Up();
                    RightB();
                }
            }
        }  // собран правильный оранжевый крест

        
        show();

        while (!check_upper_edges()) {
            if ((up[2][2] == 'o' && front[0][2] == 'w' && right[0][0] == 'b') || (up[2][2] == 'o' && front[0][2] == 'b' && right[0][0] == 'w') ||
                (up[2][2] == 'w' && front[0][2] == 'o' && right[0][0] == 'b') || (up[2][2] == 'w' && front[0][2] == 'b' && right[0][0] == 'o') ||
                (up[2][2] == 'b' && front[0][2] == 'w' && right[0][0] == 'o') || (up[2][2] == 'b' && front[0][2] == 'o' && right[0][0] == 'w')) {
                Up();
                Right();
                UpB();
                LeftB();
                Up();
                RightB();
                UpB();
                Left();
            }
            else if ((front[0][0] == 'w' && left[0][2] == 'g' && up[2][0] == 'o') || (front[0][0] == 'w' && left[0][2] == 'o' && up[2][0] == 'g') ||
                (front[0][0] == 'g' && left[0][2] == 'o' && up[2][0] == 'w') || (front[0][0] == 'g' && left[0][2] == 'w' && up[2][0] == 'o') ||
                (front[0][0] == 'o' && left[0][2] == 'g' && up[2][0] == 'w') || (front[0][0] == 'o' && left[0][2] == 'w' && up[2][0] == 'g')) {
                Up();
                Front();
                UpB();
                BackB();
                Up();
                FrontB();
                UpB();
                Back();
            }
            else if ((up[0][2] == 'o' && right[0][2] == 'b' && back[0][0] == 'y') || (up[0][2] == 'o' && right[0][2] == 'y' && back[0][0] == 'b') ||
                (up[0][2] == 'b' && right[0][2] == 'o' && back[0][0] == 'y') || (up[0][2] == 'b' && right[0][2] == 'y' && back[0][0] == 'o') ||
                (up[0][2] == 'y' && right[0][2] == 'b' && back[0][0] == 'o') || (up[0][2] == 'y' && right[0][2] == 'o' && back[0][0] == 'b')) {
                Up();
                Back();
                UpB();
                FrontB();
                Up();
                BackB();
                UpB();
                Front();
            }
            else if ((up[0][0] == 'o' && back[0][2] == 'y' && left[0][0] == 'g') || (up[0][0] == 'o' && back[0][2] == 'g' && left[0][0] == 'y') ||
                (up[0][0] == 'g' && back[0][2] == 'y' && left[0][0] == 'o') || (up[0][0] == 'g' && back[0][2] == 'o' && left[0][0] == 'y') ||
                (up[0][0] == 'y' && back[0][2] == 'o' && left[0][0] == 'g') || (up[0][0] == 'y' && back[0][2] == 'g' && left[0][0] == 'o')) {
                Up();
                Left();
                UpB();
                RightB();
                Up();
                LeftB();
                UpB();
                Right();
            }
            else {
                Up();
                Right();
                UpB();
                LeftB();
                Up();
                RightB();
                UpB();
                Left();
            }
        }   //Правильно поставлены углы

        for (int i = 0; i < 5; i++) {
            if (up[0][0] != 'o')
                while (up[0][0] != 'o') {
                    Back();
                    Down();
                    BackB();
                    DownB();
                }
            Up();
        } // Собрана оранжевая грань

        while (!assembly_check()) {
            Up();
        }// доворачиваем последнюю сторону и кубик собран

    }
    //кубик собран

    void solve() {
        read();

        first();
        out << endl << endl << "First layer is done" ;
        show();
        second();
        out << endl << endl <<  "Second layer is done" << endl;
        third();
        out << endl << endl << "Third layer is done" ;
        show();

    }
    
  };  
    int main() {
        
        Cube Rub;
        Rub.read();
        if (Rub.check_cube())
            Rub.solve();
        else out << "Your cube is bad";
        return 0;
    }
 
