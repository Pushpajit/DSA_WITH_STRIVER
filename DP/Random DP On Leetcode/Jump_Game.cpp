//leetcode: https://leetcode.com/problems/jump-game/description/

class Solution {

public:
    bool canJump(vector<int>& nums)
    {
        int max_jump_index = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            // Update the maximum distance we can jump.
            max_jump_index = max(nums[i] + i, max_jump_index);

            // If the current max_jump_index is < (ind + 1) it means we are stuck and can not
            // go to the last index so break the loop. Because we don't have extra calory
            // to jump further.
            if (max_jump_index < i + 1)
                break;
        }

        // If we have enough calory to jump further >= nums.size() - 1 then return true
        // else return false.
        return max_jump_index >= nums.size() - 1;
    }
};