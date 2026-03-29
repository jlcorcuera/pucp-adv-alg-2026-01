#include <iostream>

using namespace std;

const int ROWS = 10;
const int COLS = 10;

int directions [4][2] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};

void print_maze(char maze[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

bool is_valid(int r, int c, char maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    return (r >= 0 && r < ROWS && c >= 0 && c < COLS &&
            maze[r][c] != '#' && !visited[r][c]);
}

bool solve(int x, int y, char maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    if (maze[x][y] == 'E') {
        return true;
    }

    visited[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        if (is_valid(new_x, new_y, maze, visited)) {
            if (solve(new_x, new_y, maze, visited)) {
                // Without this condition, the start position would be marked as part of the path
                if (maze[x][y] != 'S') {
                    maze[x][y] = '.';
                }
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Legend:
    // 'S': Start
    // ' ': Path
    // '#': Wall
    // 'E': Exit

    char maze[ROWS][COLS] = {
        {'S', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', ' '},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' '},
        {'#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {' ', '#', ' ', '#', '#', '#', ' ', '#', ' ', '#'},
        {' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', 'E'}
    };

    bool visited[ROWS][COLS] = {false};
    cout << "Maze initial state" << endl;
    print_maze(maze);
    cout << "Solution" << endl;
    solve(0, 0, maze, visited);
    print_maze(maze);
    return 0;
}