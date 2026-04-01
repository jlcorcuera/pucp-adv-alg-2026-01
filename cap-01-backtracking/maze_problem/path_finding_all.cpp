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

void solve(int x, int y, char maze[ROWS][COLS], bool visited[ROWS][COLS]) {
    if (maze[x][y] == 'E') {
        cout << "New Solution Found!" << endl;
        print_maze(maze);
        return;
    }
    char old_cell_value = maze[x][y];
    maze[x][y] = '.';
    visited[x][y] = true;

    for (int i = 0; i < 4; i++) {
        int new_x = x + directions[i][0];
        int new_y = y + directions[i][1];
        if (is_valid(new_x, new_y, maze, visited)) {
            solve(new_x, new_y, maze, visited);
        }
    }
    maze[x][y] = old_cell_value;
    visited[x][y] = false;
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

    solve(0, 0, maze, visited);
    // print_maze(maze);
    return 0;
}