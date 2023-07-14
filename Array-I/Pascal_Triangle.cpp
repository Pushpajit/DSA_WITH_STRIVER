class Solution {
    long long int nCr(int n, int r) {
        long long int res = 1;

        // Sortcut formula to calculate nCr
        for (int i = 0; i < r; i++) {

            res = res * (n - i);
            res = res / (i + 1);
        }

        return res;
    } // TC -> O(r)



    // Calculate the entire row using the formula prev * ((row - col) / col)
    vector<int> calculateEntireRow(int row) {
        vector<int> ans(row);
        ans[0] = 1;
        ans[row - 1] = 1;

        long long int prev = 1;

        // Calculate till the middle, cuz after that it's all mirror value.
        for (int col = 1; col < ceil((float) row / 2); col++) {
            prev = prev * (row - col);
            prev = prev / col;

            ans[col] = prev;
            ans[ans.size() - 1 - col] = prev;
        }

        return ans;

    } // O (n / 2)



public:
    // ALSO OPTIMAL (MY APPROCH)
    vector<vector<int>> generate(int n) {
        vector<vector<int>> pascal;
        pascal.push_back(vector<int>(1, 1));

        for (int i = 1; i < n; i++) {
            vector<int> v;
            //1st element is always 1
            v.push_back(1);

            //ith row contais ith elements.
            for (int j = 1; j < i; j++) {
                //Formula that showing in the animation.
                v.push_back(pascal[i - 1][j] + pascal[i - 1][j - 1]);
            }

            //last element is always 1
            v.push_back(1);

            //push the current row into pascal vector.
            pascal.push_back(v);
        }

        return pascal;

    } // TC -> O(n x n)



    // OPTIMAL APPROCH
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;

        for (int i = 1; i <= numRows; i++) {

            ans.push_back(calculateEntireRow(i));
        }

        return ans;

    } // TC -> O(n^2 / 2)
};