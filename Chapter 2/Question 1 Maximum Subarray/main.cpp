// Maximum Sub-array Sum Algorithm
// Using Divide & Conquer Method
// Data Input Assume To Be An Integer Array

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int i;
        int j;
        int targeti;
        int targetj;
        int size = nums.size();
        int sum = (-999999);
        int temp = 0;

        for (i = 0; i < size; i++) {
            temp = temp + nums[i];

            if (temp > sum) {
                sum = temp;
                targeti = i;
            }
        }

        temp = 0;
        sum = (-999999);

        for (i = size - 1; i >= 0; i--) {
            temp = temp + nums[i];

            if (temp > sum) {
                sum = temp;
                targetj = i;
            }
        }

        if (targeti >= targetj) {
            int result = 0;

            for (j = targetj; j <= targeti; j++) {
                result = result + nums[j];
            }

            return result;
        }

        temp = 0;
        int targetii;
        sum = (-999999);

        for (j = targeti; j >= 0; j--) {
            temp += nums[j];

            if (temp > sum) {
                sum = temp;
                targetii = j;
            }
        }

        int result1 = 0;

        for (j = targetii; j <= targeti; j++) {
            result1 = result1 + nums[j];
        }

        temp = 0;
        int targetjj;
        sum = (-999999);

        for (j = targetj; j < size; j++) {
            temp = temp + nums[j];

            if (temp > sum) {
                sum = temp;
                targetjj = j;
            }
        }

        int result2 = 0;

        for (j = targetj; j <= targetjj; j++) {
            result2 = result2 + nums[j];
        }

        vector<int> nums1(nums.begin() + targeti, nums.begin() + targetj);

        int result3 = maxSubArray(nums1);

        return max(max(result1, result2), result3);
    }
};

int main() {
    vector<int> integerArray;
    int number;
    int answer;
    Solution s;

    // Test Case: -2, 1, -3, 4, -1, 2, 1, -5, 4, 0
    // Result: 6

    while (cin >> number && number != 0) {
        integerArray.push_back(number);
    }

    /*
    for(int i = 0; i < integerArray.size(); i++) {
        cout << integerArray[i] << endl;
    }
    */

    answer = s.maxSubArray(integerArray);

    cout << answer;
}