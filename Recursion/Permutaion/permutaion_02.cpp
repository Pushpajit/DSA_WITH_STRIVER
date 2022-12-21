// OPTIMIZED VERSION.

class Solution {
    void permutation(vector<int> &nums, vector<vector<int>> &ans, int ptr) {
        // If ptr is exceeded (ptr == nums.size()) then add 'nums' to answer.
        if (ptr == nums.size()) {
            ans.push_back(nums);
            return;
        }

        // We consider each index as head and swap all elemets from [head to n - 1] with head itself,
        // then at last we are adding it to the answer.

        for (int i = ptr; i < nums.size(); i++) {
            // Try to swap all elements from [ptr to n - 1] with current elemtent.
            // (i.e nums[ptr])

            swap(nums[ptr], nums[i]);

            // Call for the next index.
            permutation(nums, ans, ptr + 1);

            // Revert the changes, Backtracking.
            swap(nums[ptr], nums[i]);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        unordered_map<int, int> hsh;
        vector<int> pmt;
        vector<vector<int>> ans;

        permutation(nums, ans, 0);

        return ans;
    }
};