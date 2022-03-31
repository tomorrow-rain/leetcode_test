#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，贪心
//每天的利润序列：(prices[i] - prices[i - 1]).....(prices[1] - prices[0])
//收集正利润的区间，就是股票买卖的区间，只需要关注最终利润，不需要记录区间。
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
        for(int i=1;i<prices.size();i++){
            res += max(0,prices[i]-prices[i-1]);
        }
        return res;
    }
};

//解法2 dp
//重点是计算差值，假设最开始持有现金为0，买入股票，现金-price，卖出股票，现金+price
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        vector<vector<int>> dp(len,vector<int>(2,0));
        //第i天持有股票后，最多现金
        dp[0][1] -= prices[0];
        //第i天未持有股票，最多现金（初始现金为0）
        dp[0][0] = 0;
        for(int i=1;i<len;i++){
            // max(第i-1天持有现金，第i天购买了股票后剩余现金)
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]-prices[i]);
            // max(第i-1天持有现金，第i天卖掉了股票后剩余现金)
            dp[i][0] = max(dp[i-1][0],dp[i-1][1]+prices[i]); 
        }
        //最后一天未持有股票，剩余最多现金
        return dp[len-1][0];
    }
};

