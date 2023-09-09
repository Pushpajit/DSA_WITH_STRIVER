// LEETCODE: https://leetcode.com/problems/majority-element/
// VIDEO: https://youtu.be/nP_ns3uSh80


class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int element = -1;
        int count = 0;

        // At the last a single element will left which signifies that is the majority element which appears more than n/2 times in the array.

        // Majority element will not gonna cancle out itself if it appears more than n/2 times and this is the technique in Moore's voting algorithm.

        for (int i : nums) {
            if (count == 0) {
                element = i;
                count = 1;
            }
            else if (i == element) {
                count++;
            }
            else {
                count--;
            }
        }

        return element;
    }
}; // TC --> O(n)  SC --> O(1)