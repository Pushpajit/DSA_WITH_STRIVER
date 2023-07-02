#include<bits/stdc++.h>
using namespace std;


// Time Complexity: O(N*log(high - low))
// Space Complexity: O(1)
// problem Link: https://practice.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1?utm_source=gfg&utm_medium=article&utm_campaign=bottom_sticky_on_article

class Solution
{
private:

    // Fucntion to count the number of students need to be allocated for a perticular maximum page threshold.
    int student_allocated(int A[], long long int page, int N) {
        // At least 1 student need to be allocated.
        int student = 1, page_allocated = 0;

        for (int i = 0; i < N; i++) {
            page_allocated += A[i];

            // If alloated page number than the given threshold value then we need to assign the rest pages to the next student.
            if (page_allocated > page) {
                student++;
                // Also have to reset the page_allocated with the current page number.
                page_allocated = A[i];
            }
        }

        // Return if the no of student need to be allocate.
        return student;
    }

public:
    //Function to find minimum number of pages.
    int findPages(int A[], int N, int M)
    {
        // It cant possible.
        if (M > N) return -1;

        long long int low = *max_element(A, A + N);
        long long int high = 0;

        // Sum of off element will be the maximum page can be allocate in worst case.
        for (int i = 0; i < N; i++) high += A[i];


        while (high - low >= 1) {
            long long int mid = low + (high - low) / 2;

            if (student_allocated(A, mid, N) > M)
                low = mid + 1;
            else
                high = mid;
        }

        return low;


    }
};

