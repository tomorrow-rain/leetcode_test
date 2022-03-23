#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//解法1
//左右两次遍历，分别记录每个元素左右两边的乘积，再相乘就是结果
// O(n) 时间复杂度
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n),right(n);
        left[0] = 1;
        right[n-1] = 1;
        for(int i=1;i<n;i++){
            left[i] = left[i-1]*nums[i-1];
        }
        for(int i=n-2;i>=0;i--){
            right[i] = right[i+1]*nums[i+1];
            left[i] = left[i]*right[i];
        }
        return left;
    }
};

//解法2 优化空间
// O(1) 的额外空间复杂度
// 输出数组不被视为额外空间
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n);
        int right = 1;
        left[0] = 1;
        for(int i=1;i<n;i++){
            left[i] = left[i-1]*nums[i-1];
        }
        for(int i=n-2;i>=0;i--){
            right = right*nums[i+1];
            left[i] = left[i]*right;
        }
        return left;
    }
};

// 解法3 再优化时间
// 只遍历一次
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n,1);
        int right = 1;
        int left = 1;
        for(int i=0;i<n;i++){
            res[i]*= left;
            res[n-i-1]*= right;
            left*= nums[i];
            right*= nums[n-i-1];
        }
        return res;
    }
};


