class Solution {
    void permutation(vector<int>& nums, unordered_map<int, int> &hsh, vector<int> &pmt, vector<vector<int>> &ans) {
        // If pmt vector is filled then add it to answer.
        if (pmt.size() == nums.size()) {
            ans.push_back(pmt);
            return;
        }

        for (int i : nums) {
            if (hsh[i] == 0) {
                // Mark the current element as picked and push to the vector.
                hsh[i] = 1;
                pmt.push_back(i);

                // Recursion call.
                permutation(nums, hsh, pmt, ans);

                // Undo Changes Backtracking, unmark current element and popback.
                hsh[i] = 0;
                pmt.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        unordered_map<int, int> hsh;
        vector<int> pmt;
        vector<vector<int>> ans;

        permutation(nums, hsh, pmt, ans);

        return ans;
    }
};