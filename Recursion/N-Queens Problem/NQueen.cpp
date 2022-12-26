//It can be optimized, watch video last part.

class Solution {
    bool isSafe(vector<string> &board, int n, int r, int c) {
        /*
        Only Check these three directions ↖⬆↗
        🔯That is board[row - 1][col], board[row - 1][col - 1] and board[row - 1][col + 1]

        Reasons for that is very simple, just think about it.
        You have to check if your queen is safe or not, under all the rows of you current row
        do not contains any Queen yet so no need to check for [row + 1][col], [row + 1][col - 1], [row + 1][col + 1] and similarly [row][col - 1] (because one row contains 1 Queen)

        */


        int row = r, col = c;

        // For ⬆ direction.
        while (row >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
        }

        row = r;
        col = c;
        // For ↖ direction.
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        row = r;
        col = c;

        // For ↗ direction.
        while (row >= 0 && col < n) {
            if (board[row][col] == 'Q') return false;
            row--;
            col++;
        }

        // If the place is safe then return true.
        return true;

    }


    void placeQueen(vector<string> &board, int n, int row, vector<vector<string>> &ans) {
        // When row == n it means we are able to place all the queens in a specific order.
        // So add the current Queen's placement to the answer.
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {

            // Check if current position is safe or not.
            if (isSafe(board, n, row, col)) {
                // If safe then place the Queen.
                board[row][col] = 'Q';

                // Current row has one Queen placed so do recurcive all to next row (row + 1)
                placeQueen(board, n, row + 1, ans);
                Rcall++;

                // After doing all stuff roll back the changes (Backtracking).
                // Because we want to find all possible placements of N Queens .
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        Rcall = 0;
        string fill(n, '.');
        vector<string> board(n, fill);

        vector<vector<string>> ans;

        placeQueen(board, n, 0, ans);

        return ans;

    }
};