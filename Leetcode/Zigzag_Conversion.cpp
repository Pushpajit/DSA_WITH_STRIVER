/*
    leetcode:
        https://leetcode.com/problems/zigzag-conversion/description/

    TC: O(n)
    SC: O(n)

*/



class Solution {
public:
    string convert(string s, int numRows) {
        // It's simple, if there is a single row so return the string as it is.
        if (numRows == 1) return s;

        // Utilities
        vector<string> v(numRows);
        int i = 0, j = 0;
        int zigzag = false;
        // ...


        for (char c : s) {
            // If the head i is exhausted the last row then
            // toggle traversing direction to Diagonally.
            if (i >= numRows) {
                i--;
                zigzag = !zigzag;
            }


            // If the head i is exhausted the 1st row then
            // toggle traversing direction to Downward.
            if (i <= 0) {
                i++;
                zigzag = !zigzag;
            }


            // Go downwards.
            if (!zigzag) {
                v[i].push_back(c);
                i++;
            }
            // Else go Right Dialgonally.
            else {
                j++;
                i--;
                // Vizualise the patteren, fill the gap with empty char.
                while (v[i].size() < j)
                    v[i].push_back(' ');

                // Push the current char into v[i]'s last index.
                v[i].push_back(c);

            }
        }

        // Construct the answer.
        string ans = "";
        for (auto vec : v) {
            for (char c : vec) {
                if (c != ' ') ans += c;
            }
        }

        return ans;
    }
};