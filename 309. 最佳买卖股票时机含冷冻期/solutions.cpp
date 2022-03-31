#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，dp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len,vector<int>(3,0));
        dp[0][0] = -prices[0]; //dp[i][0] 第i天持有股票，最大收益
        dp[0][1] = 0; //dp[i][1] 第i天（卖出股票）未持有股票，在冷冻期（第i+1天不能买），最大收益
        dp[0][2] = 0; //dp[i][2] 第i天（没有买卖股票）未持有股票，没在冰冻期，最大收益
        for(int i=1;i<len;i++){
            //不买卖股票，或者买入第i天的股票
            dp[i][0] = max(dp[i-1][0],dp[i-1][2]-prices[i]);
            //卖掉股票
            dp[i][1] = dp[i-1][0]+prices[i];
            //第i-1天未持有股票
            dp[i][2] = max(dp[i-1][1],dp[i-1][2]);
        }
        //最终未持有股票
        return max(dp[len-1][1],dp[len-1][2]);
    }
};


