/*
    leetcode:
        https://leetcode.com/problems/fruit-into-baskets/description/

    TC: O(2N)
    SC: O(2)

*/

class Solution {
public:
    int totalFruit(vector<int>& v) {
        int maxWindow = 0;
        unordered_map<int, int> hsh;
        int i = 0, j = 0;

        while (j < v.size()) {
            // Count the frequency of the elements accross the way.
            hsh[v[j]]++;

            // If the hsh size is <= 2 it's mean.
            if (hsh.size() <= 2)
                // update the window size.
                maxWindow = max(maxWindow, j - i + 1);
            else {
                // Until the hsh size is > 2
                // compress the window (i.e delete elements from ith position)
                while (hsh.size() > 2) {
                    // Reduce the frequency.
                    hsh[v[i]]--;

                    // Erase the key from hsh if frequency is 0
                    if (hsh[v[i]] == 0)
                        hsh.erase(v[i]);

                    i++;
                }
            }

            j++;
        }


        return maxWindow;

    }
};