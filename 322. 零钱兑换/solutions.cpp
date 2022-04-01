#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，dp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        int Max = amount + 1;
        //初始每种背包装物品amount + 1 个
        vector<int> dp(amount+1,Max);
        //容量为0时，物品个数为0
        dp[0] = 0;
        //外层循环背包
        for(int i=1;i<=amount;i++){
            //内层循环物品
            for(int j=0;j<n;j++){
                if(coins[j]<=i){
                    dp[i] = min(dp[i],dp[i-coins[j]]+1);
                }
            }
        }
        return dp[amount]>amount?-1:dp[amount];
    }
};

//解法2，dfs
//会超时
class Solution {
public:
    int c = 0;
    int a = 0;
    int res = 0;
    void dfs(vector<int>& coins,int amount,int cur){
        if(a==amount){
            res = min(res,c);
            return;
        }
        if(c>=res || cur<0){
            return;
        }
        for(int i=(amount-a)/coins[cur];i>=0 && i+c<res;i--){
            a += coins[cur]*i;
            c += i;
            dfs(coins,amount,cur-1);
            a -= coins[cur]*i;
            c -= i;
        }
    }
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        sort(coins.begin(),coins.end());
        res = amount+1;
        dfs(coins,amount,n-1);
        if(res==amount+1){
            return -1;
        }
        else{
            return res;
        }
    }
};

