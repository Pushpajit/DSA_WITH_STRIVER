class Solution {

public:

// Prefix sum problem.
    vector<int> answerQueries(vector<int>& nums, vector<int>& q) {
        int n = nums.size();
        int m = q.size();
        vector<int> ans(m);

        //Sort the array
        sort(nums.begin(), nums.end());

        // Prefix sum, thus we are calculating the maximum numbers are need to make a
        // specific number, because the vector is sorted that's why we can easily achive
        // that.
        for (int i = 1; i < n; i++) nums[i] += nums[i - 1];

        //Find the upper_bound of each queries in prefix vector then substract the
        // postition from the nums.begin(), so we have the max number of elements
        // needed to add up equal to query[i] .
        for (int i = 0; i < m; i++) {
            ans[i] = upper_bound(nums.begin(), nums.end(), q[i]) - nums.begin();
        }

        // TC-> O(QlogN) + O(NlogN)
        // SC-> O(1)

        return ans;

    }
};