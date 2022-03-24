#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<math.h>
#include<limits.h>
using namespace std;

//解法1
//dfs 超时
class Solution {
public:
    int ret = 100;
    int tmp = 0;
    void dfs(vector<int> &v,int cur,int target){
        if(target<0){
            return;
        }
        if(target==0){
            ret = min(tmp,ret);
            return;
        }
        for(int i=cur;i>=0;i--){
            target-=v[i];
            tmp++;
            dfs(v,i,target);
            target+=v[i];
            tmp--;
        }
    }
    int numSquares(int n) {
        int half = sqrt(n);
        if(half*half==n){
            return 1;
        }
        vector<int> v;
        for(int i=1;i<=half;i++){
            v.push_back(i*i);
        }
        dfs(v,half-1,n);
        return ret;
    }
};


//解法2(题解)
//dp

class Solution {
public:
    // dp[i] 表示数字i最少可以由几个完全平方数相加构成
    // 位置i只依赖 i-j*j 的位置，如 i-1、i-4、i-9 等等位置，才能满足完全平方分割的条件。
    // 因此dp[i]可以取的最小值即为 1 + min(dp[i-1],dp[i-4],dp[i-9]...)

    //完全背包问题：物品可以重复选，外层遍历背包大小、内层遍历物品
    
    int numSquares(int n) {
        vector<int> dp(n+1);
        for(int i=1;i<=n;i++){
            int minn = INT_MAX;
            for(int j=1;j*j<=i;j++){
                minn = min(minn,dp[i-j*j]);
            }
            dp[i] = minn+1;
        }
        return dp[n];
    }
};