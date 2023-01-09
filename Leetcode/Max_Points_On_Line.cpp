/*
    Problem Link:- https://leetcode.com/problems/max-points-on-a-line/
*/
// Approach:- Using two point form of a line
class Solution {
private:
    // isLie method which takes two fixed points point1 and point2 and constructs a straight line from it
    // and a variable point 3 which we must check if it lies on the same line as point1 and point2
    // if the point3 satisfies the equation of the line made from point1 and point2 then it lies on the line and we return true else we return false
    bool isLie(vector<int> &point1, vector<int> &point2, vector<int> &point3) {
        int xCord = point3[0], yCord = point3[1];
        int xCord1 = point1[0], yCord1 = point1[1];
        int xCord2 = point2[0], yCord2 = point2[1];

        int val = (yCord - yCord1) * (xCord2 - xCord1) - (yCord2 - yCord1) * (xCord - xCord1);
        return val == 0;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        // if there are less than or equal to 2 points then return the number of points as it is
        if (n <= 2)
            return n;
        // counter for maximum points on a line
        int maxPoints = 0;
        // do a quadratic scan of the points array
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                // in each scan pick two points and make a line out of the two points and check for the remaining points if they lie on this line if it does then increment the counter
                // intially set the counter to 2 as we already picked two points that lie on a line
                int cnt = 2;
                // do a linear scan of the the points array to check which points lie on the line using isLie method
                for (int k = 0; k < n; k++) {
                    // we must not check for those points which we picked earlier to make the line as it is already counted
                    if (k != i && k != j) {
                        // if the point lies on the line than increment the counter
                        if (isLie(points[i], points[j], points[k]))
                            cnt++;
                    }
                }
                // after each iteration check for the maximum points and update it accordingly
                maxPoints = max(maxPoints, cnt);
            }
        }
        // return the maximum number of points
        return maxPoints;
    }
};