/*
    leetcode:
        https://leetcode.com/problems/jump-game-ii/

*/


class Solution {
    int fun(vector<int> &nums, int ind, vector<int> &DP) {
        // If we are reached at the last index.
        if (ind >= nums.size() - 1)
            return 0;

        // If the answer is calculated then dont recalculate.
        if (DP[ind] != -1)
            return DP[ind];

        int minjump = 1e9;
        // Go from the ind + 1 to the maximum index jump.
        for (int i = ind + 1; i <= ind + nums[ind]; i++)
            // Find the minimum of them all to reach to the last index.
            minjump = min(minjump, fun(nums, i, DP) + 1);

        // Save the current minimum jump from ind to last index.
        return DP[ind] = minjump;

    } // TC: O(2^n), SC: O(2n)



    int Tabulation(vector<int>& nums) {
        int n = nums.size();

        vector<int> DP(n);

        // Just show the state.
        for (int ind = n - 2; ind >= 0; ind--) {

            // Just copy the recurrence.
            int minjump = 1e9;

            for (int i = ind + 1; i <= ind + nums[ind] && i < n; i++)
                minjump = min(minjump, DP[i] + 1);

            DP[ind] = minjump;
        }

        return DP[0];

    } // TC: O(n^2), SC: O(n)


public:
    int jump(vector<int>& nums) {
        // vector<int> DP(nums.size(), -1);

        // return fun(nums, 0, DP);

        return Tabulation(nums);
    }
};