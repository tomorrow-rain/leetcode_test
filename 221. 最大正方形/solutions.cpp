#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，dp
class Solution {
public:
    /**
        dp[i][j]表示以第i行第j列为右下角所能构成的最大正方形边长, 则递推式为: 
        dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1]);
    **/
   
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int c = 0;
        vector<vector<int>> dp(m, vector<int>(n));

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
               if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    c = max(c, dp[i][j]);
                }
            }
        }
        return c*c;
    }
};