class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        int maxlen = 1;
        vector<int> DP(n, 1); // For storing the length of LIS.
        vector<int> cnt(n, 1); // For storing the number of LIS

        // Straight Forward LIS with some shuttle changes.
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < i; j++) {

                // If we found greater length than current length.
                if (nums[j] < nums[i] && DP[j] + 1 > DP[i]) {
                    // For length
                    DP[i] = DP[j] + 1;

                    // Just Inherit
                    cnt[i] = cnt[j];
                }

                // If we found LIS with same length then add that to the current count.
                else if (nums[j] < nums[i] && DP[j] + 1 == DP[i])
                    cnt[i] += cnt[j];
            }

            // Storing maxlen of LIS globally.
            maxlen = max(maxlen, DP[i]);
        }

        int total = 0;
        // Add up all LIS.
        for (int i = 0; i < n; i++) {
            if (DP[i] == maxlen)
                total += cnt[i];
        }

        return total;
    }
};