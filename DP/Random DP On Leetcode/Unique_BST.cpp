/*
    leetcode:
        https://leetcode.com/problems/unique-binary-search-trees/description/

*/


class Solution {
    int fun(int n, vector<int> &DP) {
        if (n == 0 || n == 1)
            return 1;

        if (DP[n] != -1)
            return DP[n];

        int total = 0;

        // Make every node from 1 to n to parent node.
        // And then solve for the other remaining nodes.
        for (int i = 1; i <= n; i++) {
            int leftSubTree = i - 1;
            int rightSubTree = n - i;

            // Total combination will be sum of all (leftsubtree * rightsubtree)
            total += fun(leftSubTree, DP) * fun(rightSubTree, DP);
        }

        return DP[n] = total;
    }



    int Tabulation(int N) {
        // Declearing 1D DP
        vector<int> DP(N + 1, 1);

        for (int n = 2; n <= N; n++) {
            int total = 0;

            // Just copy the recurrence
            for (int j = 1; j <= n; j++) {
                int leftSubTree = j - 1;
                int rightSubTree = n - j;

                // Total combination will be sum of all (leftsubtree * rightsubtree)
                total += DP[leftSubTree] * DP[rightSubTree];
            }
            // Store the current total into DP[n]
            DP[n] = total;
        }

        return DP[N];
    }

public:
    int numTrees(int n) {
        // vector<int> DP(n + 1, -1);
        // return fun(n, DP);

        return Tabulation(n);
    }
};