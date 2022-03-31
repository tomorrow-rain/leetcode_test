#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，dp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if(len<=1){
            return 0;
        }
        //dp[i]:前i天的最大收益
        //前i天的最大收益 = max{前i-1天的最大收益，第i天的价格-前i-1天中的最小价格}
        int dp[len];
        dp[0] = 0;
        int min_price = prices[0];
        for(int i=1;i<len;i++){
            dp[i] = max(dp[i-1],prices[i]-min_price);
            min_price = min(min_price,prices[i]);
        }
        return dp[len-1];
    }
};