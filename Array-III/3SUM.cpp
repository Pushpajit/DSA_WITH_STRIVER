// LEETCODE: https://leetcode.com/problems/3sum/description/
// YOUTUBE: https://youtu.be/DhFh8Kw7ymk




/*
Eqn is a[i] + a[j] + a[k] = 0
so we need to find a[k] = -(a[i] + a[j]) using hashmap.
*/

// Better Approch
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> st;

        for (int i = 0; i < nums.size(); i++) {
            unordered_map<int, int> hsh;

            for (int j = i + 1; j < nums.size(); j++) {
                // Need to find according to the equation.
                int x = -(nums[i] + nums[j]);

                // If x is present in the hash.
                if (hsh.count(x) > 0) {
                    // Make triplet and sort accending order.
                    vector<int> temp = {nums[i], nums[j], x};
                    sort(temp.begin(), temp.end());

                    // Insert into set for avoid same triplet.
                    st.insert(temp);
                }

                // Insert num[j] into hashmap.
                hsh[nums[j]] = true;
            }
        }

        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }
}; // TC --> O(n^2 log(no of triplets))  SC --> O(n + n)




// Optimal Approch
class Solution {
public:
//  Code with propper comments.
    vector<vector<int>> threeSum(vector<int>& nums) {
        // For avoiding duplicate triplets and to store accending ordder.
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        // Code it out and push it to Github.
        for (int i = 0; i < nums.size(); i++) {
            // Because we dont want duplicate elements in a triplet.
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            // Initializing 2 pointers
            int j = i + 1;
            int k = nums.size() - 1;

            while (j < k) {
                int x = (nums[i] + nums[j] + nums[k]);

                // As the array is sorted
                // If x < 0 so we need to increase j
                if (x < 0) {
                    j++;
                }
                // If x > 0 so we need to decraese k
                else if (x > 0) {
                    k--;
                }
                // It means we found a triplet which add up equals to 0
                else {
                    // Store them into answer.
                    vector<int> temp = {nums[i], nums[j], nums[k]};
                    ans.push_back(temp);

                    // Move the pointers.
                    j++;
                    k--;

                    // We dont want duplicate triplets.
                    // So we are moving the pointers where we found element which are
                    // not equal to it's previous(for nums[j]) and next(for nums[k]) element.
                    while (j <= k && nums[j] == nums[j - 1]) j++;
                    while (j <= k && nums[k] == nums[k + 1]) k--;
                }
            }
        }

        return ans;

    } // TC --> O(nlogn) + O(n^2)  SC --> O(no of unique triplets)
};
