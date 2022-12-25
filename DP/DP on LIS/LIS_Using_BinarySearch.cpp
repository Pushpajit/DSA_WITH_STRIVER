/*
Very simple intuition.

1> We are just maintaining a LIS vector which is 1st initialized with v[0].

2> Then traverse from 1 to n - 1

3> If the v[ind] > LIS.back() then just push the current element into LIS.

4> Else find the current element's lower_bound position in LIS and replace it with the existing element.

5> Then at last return the size of LIS, that will be the length of LIS.

*/


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> LIS;

        // Put the 1st element as the current LIS head
        LIS.push_back(nums[0]); // SC --> O(n)


        for (int ind = 1; ind < n; ind++) {
            // If current element is greater than the LIS last index then add it to LIS.
            if (nums[ind] > LIS.back()) {
                LIS.push_back(nums[ind]);
            }
            else {
                // Find the lower_bound(current ind) position.
                auto it = lower_bound(LIS.begin(), LIS.end(), nums[ind]);

                // Replace 'current' element with that element in the position of LIS vector.
                // Because lower_bound returns itterator so use * operator to go to that address and put current value.

                *it = nums[ind];
            }

        }// TC-> O(nlogn)

        // So we can find the size of LIS by replicate the LIS array
        //*NOTE: we can not achive the exact LIS sequence.

        return LIS.size();
    }
};