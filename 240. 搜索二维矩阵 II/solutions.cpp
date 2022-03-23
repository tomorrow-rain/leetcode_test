#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

//解法1
//dfs 超时
class Solution {
public:
    bool subsearch(vector<vector<int>>& matrix,int x,int y,int target){
        if(x<0 || x>matrix.size()-1 || y<0 || y>matrix[0].size()-1 || matrix[x][y]>target){
            return false;
        }
        if(matrix[x][y]==target){
            return true;
        }
        else{
            return subsearch(matrix,x,y+1,target) || subsearch(matrix,x+1,y,target);
        }
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size()==0 || matrix[0].size()==0){
            return false;
        }
        return subsearch(matrix,0,0,target);
    }
};

//解法2
//暴力，超时
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m,n;
        if(matrix.size()==0 || matrix[0].size()==0){
            return false;
        }
        m = matrix.size();
        n = matrix[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==target){
                    return true;
                }
                if(matrix[i][j]>target){
                    break;
                }
            }
        }
        return false;
    }
};


//解法3 Z字形查找(看了题解)
// 第一行最后一列元素（右上角）是第一行最大元素、最后一列的最小元素
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m,n;
        if(matrix.size()==0 || matrix[0].size()==0){
            return false;
        }
        m = matrix.size();
        n = matrix[0].size();
        //从右上角开始
        int i=0,j=n-1;
        //结束条件
        while(i<m && j>=0){
            if(matrix[i][j]==target){
                return true;
            }
            //向前找
            else if(matrix[i][j]>target){
                j--;
            }
            //向下找
            else{
                i++;
            }
        }
        return false;
    }
};
