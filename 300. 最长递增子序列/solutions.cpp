#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<math.h>
#include<limits.h>
#include<stack>
using namespace std;

//解法1
//dfs，超时
class Solution {
public:
    stack<int> tmp;
    int res=1;
    void dfs(vector<int>& nums,int cur){
        int size = tmp.size()-1;
        //更新res（注意位置）
        res = max(res,size);
        if(cur>nums.size()-1){
            return;
        }
        if((size+nums.size()-cur)<=res){
            return;
        }
        for(int i=cur;i<nums.size();i++){
            if(nums[i]>tmp.top()){
                tmp.push(nums[i]);
                dfs(nums,i+1);
                tmp.pop();
            }
        }
    }
    int lengthOfLIS(vector<int>& nums) {
        tmp.push(INT_MIN);
        dfs(nums,0);
        return res;
    }
};


//解法2 dp
// 定义 dp[i] 为考虑前 i 个元素，以 i 个数字结尾的最长上升子序列的长度

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int res = 1;
        vector<int> dp(n,1);
        for(int i=1;i<n;i++){
             // 遍历i之前的元素j
             // 取dp[j] + 1的最大值
            for(int j=0;j<i;j++){
                if(nums[i]>nums[j]){
                    dp[i] = max(dp[i],dp[j]+1);
                }
            }
            //res取dp中的最大值,而不是dp[n-1]
            res = max(res,dp[i]);
        }
        return res;
    }
};


//解法3 贪心 + 二分查找

// O(nlogn)
// 数组 nums 的长度为 n，我们依次用数组中的元素去更新 d 数组，而更新 d 数组时需要进行 O(logn) 的二分搜索，所以总时间复杂度为 O(nlogn)

// 考虑一个简单的贪心，如果我们要使上升子序列尽可能的长，则我们需要让序列上升得尽可能慢，因此我们希望每次在上升子序列最后加上的那个数尽可能的小。
// 维护一个数组 d[i] ，表示长度为 i 的最长上升子序列的末尾元素的最小值，用 len 记录目前最长上升子序列的长度，起始时 len 为 1，d[1]=nums[0]。
// d[i]是关于i单调递增的，可以使用二分查找

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> d(n+1,0);
        int len = 1;
        d[1] = nums[0];
        //遍历
        for(int i=1;i<n;i++){
            // 如果当前数大于上一个长度对应的最末元素，直接追加，长度+1
             if(nums[i]>d[len]){
                 d[++len] = nums[i];
             }
            // 否则，说明当前数替换掉之前的某个d[i]
            // 由于d数组递增，可以直接用二分法查找替换位置
             else{
                 int left = 1;
                 int right = len;
                // 第一个比num[i]小的数的位置
                 int pos = 0;
                 while(left<=right){
                    // 这种写法，中间位置会取偏左的那个，所以左指针移动时，记录位置
                     int mid = (left+right)/2;
                     if(d[mid]<nums[i]){
                         pos = mid;
                         left = mid +1;
                     }
                     else{
                        right = mid-1;
                     }
                 }
                // 替换第一个比num[i]小的数的下一个位置
                 d[pos+1] = nums[i];
             }
        }
        return len;
    }
};

