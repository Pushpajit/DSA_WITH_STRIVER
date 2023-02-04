/*
    leetcode:
        https://leetcode.com/problems/asteroid-collision/

    TC: O(2N) (Remember each element either push into stack or pop from stack only 1 time)
    SC: O(N)

*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& v) {
        stack<int> st;

        // Push the 0th asteroid into stack.
        st.push(v[0]);

        for (int i = 1; i < v.size(); i++) { // v[i] == current asteroid
            // This flag will decide if the v[i] should go into the stack or not.
            // So it's really important.
            bool flag = true;


            // If the v[i] asteroid's
            // size is smaller than top() then v[i] asteroid will be destroid.
            if (!st.empty() && (st.top() > 0 && v[i] < 0) && abs(v[i]) < abs(st.top()))
                flag = false;


            // The collision only happend if top() is +ve and v[i] is -ve .
            // Keep destroying the astroids if the v[i] asteroid's size is >= top()
            while (!st.empty() && (st.top() > 0 && v[i] < 0) && (abs(v[i]) >= abs(st.top()))) {

                // If both asteroids have same size then destroy both and break the process.
                if (abs(v[i]) == abs(st.top())) {
                    st.pop();
                    flag = false;
                    break;
                }

                // Destory the top() asteroid because it's size is smaller than v[i]
                st.pop();


                // If there is a situation in destruction process that, If the v[i] asteroid's
                // size is smaller than top() then v[i] asteroid will be destroid and break
                // the process.
                if (!st.empty() && (st.top() > 0 && v[i] < 0) && abs(v[i]) < abs(st.top())) {
                    flag = false;
                    break;
                }

            }


            // If and only if flag is true then push the v[i] asteroid into stack.
            if (flag)
                st.push(v[i]);

        }


        // Constructing the answer.
        vector<int> ans(st.size());
        int i = st.size() - 1;

        // O(stack.size())
        while (!st.empty()) {
            ans[i--] = st.top();
            st.pop();
        }

        return ans;
    }
};