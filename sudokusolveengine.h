#ifndef SUDOKUSOLVEENGINE_H
#define SUDOKUSOLVEENGINE_H

#include <vector>
using namespace std;
class SudokuSolveEngine
{
public:
    SudokuSolveEngine();

    bool rows[9][10];
    bool cols[9][10];
    bool squares[9][10];
    vector<vector<char>> board;

    int conv(int i, int j);

    bool isValid(int i, int j, int k);

    bool solve(int i, int j) ;

    void solveSudoku(vector<vector<char>>& board,bool & ok) ;
};

#endif // SUDOKUSOLVEENGINE_H
