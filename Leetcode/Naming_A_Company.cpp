/*
    leetcode:
        https://leetcode.com/problems/naming-a-company/description/
    Youtube:
        https://youtu.be/NrHpgTScOcY
*/


class Solution {
public:
    long long distinctNames(vector<string>& ideas) {

        unordered_map<char, unordered_set<string>> hsh;
        long long ans = 0;

        // Create group whose starting char is same. (i.e Total 26 key possible)
        for (auto s : ideas)
            hsh[s[0]].insert(s.substr(1));


        for (auto item : hsh) { // O(26)
            for (auto i : hsh) { // O(26)

                // If we encounter same key then skip that.
                if (i.first == item.first)
                    continue;


                int intersection = 0;
                // We are comparing one group with another.
                // And finding the intersection of the groups.
                for (auto s : i.second) { // O(n) (considering all groups)
                    // If we found the string in other group then increment intersection.
                    if (item.second.find(s) != item.second.end())
                        intersection++;
                }


                // Remove the common elements from both the groups.
                int distinct1 = (item.second.size() - intersection);
                int distinct2 =  (i.second.size() - intersection);

                // Then calculate the total combination of both group without having
                // same elements. After that add that to the answer.
                ans += (distinct1 * 1LL * distinct2);
            }
        } // TC--> O(n * 26^2)  SC--> O(26)


        return ans;


    }
};