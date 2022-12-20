#include <bits/stdc++.h>
using namespace std;

class Solution {
    bool check(vector<vector<char>>& board, int i, int j, char num) {

        for (int k = 0; k < 9; k++) {
            // For the current column and current row
            // if any cell contains 'num' then return false.
            if (board[i][k] == num || board[k][j] == num)
                return false;

            // Check for current 3x3 matrix.
            if (board[3 * (i / 3) + k / 3][3 * (j / 3) + k % 3] == num)
                return false;
        }

        // Then it is valid.
        return true;
    }


    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {

                if (board[i][j] == '.') { // Find next empty cell.

                    for (char k = '1'; k <= '9'; k++) {
                        // If the current 'num' is valid from current cell
                        if (check(board, i, j, k)) {
                            board[i][j] = k; // Change the current cell with that 'num'

                            if (solve(board)) // If the board returns false then it's a valid number so return true.
                                return true;
                            else
                                board[i][j] = '.'; // Else undo the changes, backtracking
                        }
                    }

                    return false; // If no 'num' is valid for current cell then return false.
                }
            }
        }

        return true; // If all cells are filled then it means we filled with valid num, so return true.
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
};