// PROBLEM LINK : https://takeuforward.org/data-structure/set-matrix-zero/

class Solution {
public:
    // BRUTE FORCE
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int fill = 1e7 + 9; //fill with this

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    //Fill the current row
                    for (int x = 0; x < n; x++) {
                        //Fill all non-zero element with "fill"
                        if (matrix[x][j] != 0)
                            matrix[x][j] = fill;
                    }
                    //Fill the current column
                    for (int z = 0; z < m; z++) {
                        //Fill all non-zero element with "fill"
                        if (matrix[i][z] != 0)
                            matrix[i][z] = fill;
                    }
                }
            }
        }

        //Make all cell which contains "fill" to 0
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == fill)
                    matrix[i][j] = 0;
            }
        }
    }//TC-> O((n x m) x (n + m))  SC-> O(1)






    // BETTER APPROCH
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        // Create another hash array to store the info about which row/column is done.
        vector<int> row(n, 0);
        vector<int> col(m, 0);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    // The entire ith row will be zero.
                    row[i] = 1;
                    // The entire jth column will be zero.
                    col[j] = 1;
                }
            }
        }


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << row[i] << " " << col[j] << endl;
                // If the row or the column hash array contains 1 then cell is zero
                if (row[i] || col[j])
                    matrix[i][j] = 0;
            }
        }


    } //TC -> O(2(n x m))  SC -> O(n + m)





    // OPTIMAL APPROCH
    void setZeroes(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        int col1 = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (matrix[i][j] == 0) {
                    // Make the row(i) to zero.
                    matrix[i][0] = 0;

                    // Male the col(i) to zero.
                    if (j == 0) // If any cell in 0th column is 0
                        col1 = 0;
                    else
                        matrix[0][j] = 0;
                }
            }
        }

        // Make zero to all other cell except 0th row and 0th column.
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }
        }

        // Make 0th column to zero (make sure to start from index 1)
        for (int i = 1; i < m; i++) {
            if (matrix[0][i] == 0 || matrix[0][0] == 0)
                matrix[0][i] = 0;
        }

        // Make oth row to zero
        for (int i = 0; i < n; i++) {
            if (matrix[i][0] == 0 || col1 == 0)
                matrix[i][0] = 0;
        }


    }// TC -> O(n x m)  SC -> O(1)

};