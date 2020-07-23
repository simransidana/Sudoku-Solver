#include <iostream>
#include <cmath>
using namespace std;
void inputMat(int mat[][100], int m, int n) {
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            cin >> mat[r][c];
        }
    }
}
void outputMat(int mat[][100], int m, int n) {
    cout << "\n-----MAT Begins----\n";
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            cout << mat[r][c] << " ";
        }
        cout << endl;
    }
    cout << "-----MAT Ends------\n";
}

bool canPlace(int board[][100], int N, int r, int c, int num){
    for(int x = 0; x < N; ++x){
        if (board[x][c] == num || board[r][x] == num) return false;
    }

    int rootN = sqrt(N);
    int subMatBeginRow = r - r % rootN;
    int subMatBeginCol = c - c % rootN;
    for(int i = subMatBeginRow; i < subMatBeginRow + rootN; ++i){
        for(int j = subMatBeginCol; j < subMatBeginCol + rootN; ++j){
            if (board[i][j] == num) return false;
        }
    }
    return true;
}

bool solveSudoku(int board[][100], int N, int r, int c) {
    // if r is out of bound
    if (r >= N){
        return true;
    }

    // if c is out of bound
    if (c >= N){
        return solveSudoku(board, N, r + 1, 0);
    }

    // if fixed cell
    if (board[r][c] != 0){
        return solveSudoku(board, N, r, c + 1);
    }

    // if empty cell
    for (int num = 1; num <= N; ++num) {
        if (canPlace(board, N, r, c, num)) {
            board[r][c] = num;
            bool isSuccessful = solveSudoku(board, N, r, c+ 1);
            if (isSuccessful){
                return true;
            }
            board[r][c] = 0;    // reset/vacate the cell
        }
    }
    return false;
}

int main() {
    int board[100][100];
    int N;
    cin >> N;
    inputMat(board, N, N);
    bool success = solveSudoku(board, N, 0, 0);
    if (success) {
        outputMat(board, N, N);
    }
    else {
        cout << "I can't solve it. Neither you can :HaHa:";
    }
}