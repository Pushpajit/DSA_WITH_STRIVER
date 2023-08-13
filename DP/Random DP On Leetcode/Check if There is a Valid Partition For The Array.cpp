// LINK: https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/description/

class Solution {
    bool memo(vector<int>& nums, int ind, vector<int> &DP){
        int n = nums.size();

        // We found all valid partitions. Because we reached till n.
        // If we didn't partition the array properly, we couldn't come this far.
        if(ind == n)
            return true;
        
        // Check in DP.
        if(DP[ind] != -1) return DP[ind];
        
        // Initialize it with false.
        bool ans = false;
        
        // Check for 2 size sub array
        // 1st check if it contains exactly two same element or not. 
        if(ind + 1 < n && nums[ind] == nums[ind + 1]){
            // Then check for remaing (i + 2)th index to (n-1)th index.
            ans |= memo(nums, ind + 2, DP);

            // 2nd check for 3 size sub array if all elements are same or not.
            // Then check for remaing (i + 3)th index to (n-1)th index.
            if(ind + 2 < n && nums[ind] == nums[ind + 2])
                ans |= memo(nums, ind + 3, DP);
        }

        // Check for 3 size sub array if the above conditions are false (i.e condition 3)
        if(ind + 2 < n && nums[ind] + 1 == nums[ind + 1] && nums[ind+1] + 1 == nums[ind + 2])     {
            // Then check for remaing (i + 3)th index to (n-1)th index.
            ans |= memo(nums, ind + 3, DP);
        }

        // If any of the above 3 calls we got a true value in return then it means we can partition the array.
        // Memoization
        return DP[ind] = ans;
    }


    bool tabulation(vector<int>& nums){
        int n = nums.size();
        vector<int> DP(n + 1);

        DP[n] = true;

        // Paste the recurrence.
        for(int ind = n - 1; ind >= 0; ind--){
            // Initialize it with false.
            bool ans = false;
            
            // Check for 2 size sub array
            // 1st check if it contains exactly two same element or not. 
            if(ind + 1 < n && nums[ind] == nums[ind + 1]){
                // Then check for remaing (i + 2)th index to (n-1)th index.
                ans |= DP[ind + 2];

                // 2nd check for 3 size sub array if all elements are same or not.
                // Then check for remaing (i + 3)th index to (n-1)th index.
                if(ind + 2 < n && nums[ind] == nums[ind + 2])
                    ans |= DP[ind + 3];
            }

            // Check for 3 size sub array if the above conditions are false (i.e condition 3)
            if(ind + 2 < n && nums[ind] + 1 == nums[ind + 1] && nums[ind+1] + 1 == nums[ind + 2])     {
                // Then check for remaing (i + 3)th index to (n-1)th index.
                ans |= DP[ind + 3];
            }

            // If any of the above 3 calls we got a true value in return then it means we can partition the array.
            // Memoization
            DP[ind] = ans;
        }

        return DP[0];
    } // TC--> O(n)  SC--> O(n)


public:
    bool validPartition(vector<int>& nums) {
        // If size is 2 then just check 0th and 1th element is same or not.
        if(nums.size() == 2)
            return nums[0] == nums[1];

        // vector<int> DP(nums.size(), -1);

        // return memo(nums, 0, DP);

        return tabulation(nums);
    }
};