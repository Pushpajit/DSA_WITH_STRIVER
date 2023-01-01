class Solution {
    int fun(vector<int>& nums, int i, int j, vector<vector<int>> &DP) {
        // We cannot cut a single subproblem further so return 0
        if (i > j)
            return 0;

        //Do not recalculate.
        if (DP[i][j] != -1)
            return DP[i][j];

        //For storing the maximum cost.
        int maxcost = INT_MIN;


        for (int k = i; k <= j; k++) {
            // Try to understand the formula.
            // We are trying from the last ballon left at the last and from there
            // we are traveling back in time at the begining.
            // Thus we are avoiding the subproblem dependencies.
            // And solve the subproblems without any issue.
            int curr_cost = (nums[i - 1] * nums[k] * nums[j + 1]) + fun(nums, i, k - 1, DP) + fun(nums, k + 1, j, DP);

            maxcost = max(maxcost, curr_cost);
        }


        //Memoization and return.
        return DP[i][j] = maxcost;
    }



    int Tabulation(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> DP(n, vector<int>(n));

        // Write down the changing parameters (i.e i and j) in Bottom-Up manner (reverse)
        for (int i = n - 2; i >= 1; i--) {
            for (int j = i; j <= n - 2; j++) {

                // Just copy the recurrence.
                int maxcost = INT_MIN;

                for (int k = i; k <= j; k++) {
                    int curr_cost = (nums[i - 1] * nums[k] * nums[j + 1]) + DP[i][k - 1] + DP[k + 1][j];

                    maxcost = max(maxcost, curr_cost);
                }

                // Store the cost for current i and j
                DP[i][j] = maxcost;

            }
        }

        // The answer will store here, (remember when we call recursion fun(nums, 1, N - 2))
        return DP[1][n - 2];
    }


public:
    int maxCoins(vector<int>& nums) {
        // The vector should contain [1, b-1, b-2, b-3, b-4, ..., 1]
        // For determining the cost of any individual subproblems.
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        // vector<vector<int>> DP(nums.size(), vector<int>(nums.size(), -1));
        // return fun(nums, 1, nums.size() - 2, DP);
        return Tabulation(nums);

    }
};