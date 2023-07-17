// PROBLEM SET: https://takeuforward.org/data-structure/kadanes-algorithm-maximum-subarray-sum-in-an-array/


class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = -1e9, curr = 0;
        int i = 0, j = 0;

        // Pavel Marvine approch.
        while (j < nums.size()) {
            curr += nums[j];

            // Check this first because if the array length is 1
            // (Also handle corner case)
            ans = max(ans, curr);

            while (curr <= 0 && i <= j) {
                curr -= nums[i];
                i++;
            }

            j++;
        }

        return ans;

    } // O(n)
};