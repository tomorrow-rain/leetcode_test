#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<math.h>
#include<limits.h>
using namespace std;

//解法1
//额外空间O(n)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> s;
        for(int i=0;i<n;i++){
            if(s.count(nums[i])){
                return nums[i];
            }
            else{
                s.insert(nums[i]);
            }
        }
        return -1;
    }
};


//解法2(题解)
// 二分法
// 定义 cnt[i] 表示 nums 数组中小于等于 i 的数有多少个
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size();
        int left = 1;
        int right = n-1;
        int cnt=0,ans=-1;
        while(left<=right){
            int mid = (left+right)/2;
            cnt = 0;
            for(int i=0;i<n;i++){
                if(nums[i]<=mid){
                    cnt++;
                }
            }
            // 如果数组中 <=mid 的数 <=mid 个，说明重复的数字比mid大
            if(cnt<=mid){
                left = mid+1;
            }
            // 否则在左边
            else{
                right = mid-1;
                ans = mid;
            }
        }
        return ans;
    }
};


//解法3(题解)
// 快慢指针
// 快慢指针思想, fast 和 slow 是指针, nums[slow] 表示取指针对应的元素
// 注意 nums 数组中的数字都是在 1 到 n 之间的(在数组中进行游走不会越界),
// 因为有重复数字的出现, 所以这个游走必然是成环的, 环的入口就是重复的元素, 
// 即按照寻找链表环入口的思路来做

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};