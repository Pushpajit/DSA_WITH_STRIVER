class Solution {
    int fun(vector<int> &v, int i, int j, vector<vector<int>> &DP) {
        // We cannot cut a single length stick further so return 0
        if (i > j)
            return 0;

        //Do not recalculate.
        if (DP[i][j] != -1)
            return DP[i][j];

        //For storing the minimum cost.
        int mincost = INT_MAX;

        // Rest is samilar as MCM Problem with a shuttle change.
        for (int k = i; k <= j; k++) {
            // If we know the previous cut where the stick got seperated and the last cut,
            // then the difference between the 2 cuts is the cost(i.e length) of the stick.
            int curr_cost = (v[j + 1] - v[i - 1]) + fun(v, i, k - 1, DP) + fun(v, k + 1, j, DP);

            // Find minimum of all costs.
            mincost = min(mincost, curr_cost);
        }

        //Memoization and return.
        return DP[i][j] = mincost;
    }




    int Tabulation(vector<int> &v) {
        int n = v.size();
        vector<vector<int>> DP(n, vector<int>(n));

        // Write down the changing parameters (i.e i and j) in Bottom-Up manner (reverse)
        for (int i = n - 2; i >= 1; i--) {
            for (int j = i; j <= n - 2; j++) {

                // Just copy the recurrence.
                int mincost = INT_MAX;

                for (int k = i; k <= j; k++) {

                    int curr_cost = (v[j + 1] - v[i - 1]) + DP[i][k - 1] + DP[k + 1][j];

                    mincost = min(mincost, curr_cost);
                }

                // Store the cost for current i and j
                DP[i][j] = mincost;
            }
        }


        // The answer will store here, (remember when we call recursion fun(cuts, 1, N - 2))
        return DP[1][n - 2];
    }


public:
    int minCost(int n, vector<int>& cuts) {
        // Very important to sort the array before doing operation.
        // Cause if any smaller numbers are at the middle of a stream of large number.
        // Then both the separated part of the stick will be dependend with each other.
        sort(cuts.begin(), cuts.end());

        // The vector should contain [0, cut-1, cut-2, cut-3, cut-4, ..., n]
        // For determining the cost of the stick (i.e length of any individual stick)
        cuts.insert(cuts.begin(), 0);
        cuts.push_back(n);


        // 2D DP
        // vector<vector<int>> DP(cuts.size(), vector<int>(cuts.size(), -1));
        // return fun(cuts, 1, cuts.size() - 2, DP);

        return Tabulation(cuts);
    }
};