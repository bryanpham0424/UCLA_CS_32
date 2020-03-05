#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int main() {
    string maze[10] = {
                "XXXXXXXXXX",
                "X...X..X.X",
                "X.XXX....X",
                "X.X.XXXX.X",
                "XXX......X",
                "X...X.XX.X",
                "X.X.X..X.X",
                "X.XXXX.X.X",
                "X..X...X.X",
                "XXXXXXXXXX"
    };

    if (pathExists(maze, 10, 10, 4, 3, 1, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;

}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;
    Coord a(sr, sc);
    coordStack.push(a);

    while (!(coordStack.empty())) {
        
        Coord val = coordStack.top();
        coordStack.pop();
        if (val.r() == er && val.c() == ec) {
            return true;
        }
        if (maze[val.r()][val.c() + 1] == '.') {
            coordStack.push(Coord(val.r(),val.c()+1));
            maze[val.r()][val.c() + 1] = 'X';
        }
        if (maze[val.r() + 1][val.c()] == '.') {
            coordStack.push(Coord(val.r()+1, val.c()));
            maze[val.r() + 1][val.c()] = 'X';
        }
        if (maze[val.r()][val.c() - 1] == '.') {
            coordStack.push(Coord(val.r(), val.c()-1));
            maze[val.r()][val.c() - 1] = 'X';
        }
        if (maze[val.r() - 1][val.c()] == '.') {
            coordStack.push(Coord(val.r()-1, val.c()));
            maze[val.r() - 1][val.c()] = 'X';
        }
    }
    return false;
}
