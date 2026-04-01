#include <iostream>

using namespace std;


const int N = 8;

void init_board(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '.';
        }
    }
}

void print_board(char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool valid(int cur_col, int cur_row, char board[N][N]) {
    for (int i = cur_col; i >= 0; i--) {
        if (board[cur_row][i] == 'Q') {
            return false;
        }
    }
    for (int i = cur_row, j = cur_col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }
    for (int i = cur_row, j = cur_col; i < N && j >= 0; i++, j--) {
        if (board[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

void solve(int cur_col, char board[N][N]) {
    if (cur_col == N) {
        cout << "Solution FOUND!" << endl;
        print_board(board);
        return;
    }

    for (int row = 0; row < N; row++) {
        if (valid(cur_col, row, board)) {
            board[row][cur_col] = 'Q';
            solve(cur_col + 1, board);
            board[row][cur_col] = '.';
        }
    }
}


int main() {
    char board[N][N];
    init_board(board);
    //print_board(board);
    solve(0, board);
    return 0;
}