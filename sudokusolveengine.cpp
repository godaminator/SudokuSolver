#include "sudokusolveengine.h"

#include <qDebug>


SudokuSolveEngine::SudokuSolveEngine()
{
    for(int i=0;i<9;i++){
        for(int j=0;j<10;j++){
     rows[i][j]=false;
     cols[i][j]=false;
     squares[i][j]=false;
        }
    }
}
int SudokuSolveEngine::conv(int i, int j) {
            return i/3*3+j/3;
        }

bool SudokuSolveEngine::isValid(int i, int j, int k){
      if (rows[i][k]) return false;
    if (cols[j][k]) return false;
     if (squares[conv(i,j)][k]) return false;
     return true;
        }

bool SudokuSolveEngine::solve(int i, int j) {
    qDebug()<<i<<j;
            if (j >= 9){
                i++;
                j = 0;
            }
            if (i >= 9) return true;
            if (board[i][j] != '.'){
                return solve(i, j+1);
                }
            for (int k=1; k<=9; k++){
                qDebug()<<i<<j<<k;
                if (isValid(i,j,k)) {
                    board[i][j] = k+'0';
                    rows[i][k] = true;
                    cols[j][k] = true;
                    squares[conv(i,j)][k] = true;

                    // recurse
                    if (solve(i,j+1)) return true;

                    // revert back
                    board[i][j] = '.';
                    rows[i][k] = false;
                    cols[j][k] = false;
                    squares[conv(i,j)][k] = false;
                }
            }

            return false;
        }

        void SudokuSolveEngine::solveSudoku(vector<vector<char>>& board,bool & ok) {

            ok=false;

            for (int i=0; i<9; i++){
                for (int j=0; j<9; j++){
                    if (board[i][j] != '.') {
                        int num = board[i][j] - '0';
                        if (!isValid(i,j,num)) return;
                        rows[i][num] = true;
                        cols[j][num] = true;
                        squares[conv(i,j)][num] = true;
                    }
                }
            }
            this->board = board;
            ok=solve(0, 0);
            board = this->board;
        }

