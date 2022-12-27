class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        int LDS = 0;
        int LastIndex = 0;

        vector<int> DP(n, 1); //DP array for storing LDS.
        vector<int> hsh(n); // Backtrack array.

        // Initialize the hash array with the index value as elements.
        for (int i = 0; i < n; i++) hsh[i] = i;

        // Sort the array in order to make it similar to LIS
        sort(nums.begin(), nums.end());

        // Straight forward LIS, shuttle change in if condition. Check for divisibility.
        for (int ind = 0; ind < n; ind++) {

            for (int i = 0; i < ind; i++) {
                // + 1 that's because we consider the length + current 'ind' which is
                // currently 1, You know what I mean.
                if (nums[ind] % nums[i] == 0 && DP[i] + 1 > DP[ind]) {

                    DP[ind] = DP[i] + 1; // Update DP[ind]
                    hsh[ind] = i; // A backtrack array for printting LDS
                }

            }

            // If current DP[ind] is > LDS(global) then update it
            // Here LDS and LastIndex is storing overall max length of LDS and
            // lastindex of the LDS, so we need to update it.
            if (DP[ind] > LDS) {

                LDS = DP[ind]; // Update LDS length
                LastIndex = ind; // Update LastIndex of LDS
            }
        }



        vector<int> ans;
        ans.push_back(nums[LastIndex]);

        //Backtracking..
        // If LastIndex == hsh[LastIndex] then it means this is the head of LDS.
        while (LastIndex != hsh[LastIndex]) {

            LastIndex = hsh[LastIndex];
            ans.push_back(nums[LastIndex]);

        }


        return ans;
    }
};