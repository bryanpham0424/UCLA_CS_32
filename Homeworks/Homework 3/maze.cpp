#include <string>


bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
   
    int currR = sr;
    int currC = sc;
    maze[currR][currC] = 'X';
    if (currR == er && currC == ec) {
        return true;
    }
    else{ 
        if (maze[currR][currC + 1] == '.') {
            pathExists(maze, nRows, nCols, currR, currC + 1, er, ec);
            return true;
        }
        if (maze[currR + 1][currC] == '.') {
            pathExists(maze, nRows, nCols, currR + 1 , currC, er, ec);
            return true;
        }
        if (maze[currR][currC - 1] == '.') {
            pathExists(maze, nRows, nCols, currR, currC - 1, er, ec);
            return true;
        }
        if (maze[currR - 1][currC] == '.') {
            pathExists(maze, nRows, nCols, currR - 1, currC, er, ec);
            return true;
        }
    }
    return false;
}