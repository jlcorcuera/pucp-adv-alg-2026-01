#include <iostream>

using namespace std;

const int N = 5;
const int M = 5;
const int C = 3;

int delta_rc[8][2] = {
    {1, 0},
    {1, -1},
    {0, -1},
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1}
};

int delta_cut[4][2] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

void copy_matrix(int source[N][M], int target[N][M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            target[i][j] = source[i][j];
        }
}

void print(int matrix[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << ((matrix[i][j] != 0) ? to_string(matrix[i][j]) : " ") << " ";
        }
        cout << endl;
    }
}

bool is_valid(int row, int col, int matrix[N][M]) {
    return (row >= 0 && row < N && col >= 0 && col < M && matrix[row][col] == 0);
}

void solve(int row, int col, int matrix[N][M], int result[N][M], int num_cuts, int &max_num_cuts) {
    for (int d = 0; d < 4; d++) {
        bool can_i_cut = true;
        for (int i = 0; i < C; i++) {
            if (!is_valid(row + delta_cut[d][0] * i, col + delta_cut[d][1] * i, matrix)) {
                can_i_cut = false;
                break;
            }
        }

        if (can_i_cut) {

            int last_row = row + delta_cut[d][0] * (C - 1);
            int last_col = col + delta_cut[d][1] * (C - 1);

            for (int i = 0; i < C; i++) {
                matrix[row + delta_cut[d][0] * i][col + delta_cut[d][1] * i] = num_cuts;
            }

            if (num_cuts > max_num_cuts) {
                max_num_cuts = num_cuts;
                copy_matrix(matrix, result);
            }

            for (int s = 0; s < 8; s++) {
                int next_row = last_row + delta_rc[s][0];
                int next_col = last_col + delta_rc[s][1];
                solve(next_row, next_col, matrix, result, num_cuts + 1, max_num_cuts);
            }

            for (int i = 0; i < C; i++) {
                matrix[row + delta_cut[d][0] * i][col + delta_cut[d][1] * i] = 0;
            }
        }
    }
}


int main() {
    int matrix[N][M] = {0};
    int result[N][M] = {0};
    int max_num_cuts = 0;
    solve(0, 0, matrix, result, 1, max_num_cuts);
    cout << "max_num_cuts: " << max_num_cuts << endl;
    cout << "Final result" << endl;
    print(result);
    return 0;
}