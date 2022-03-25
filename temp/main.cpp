#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<math.h>
#include<limits.h>
#include<stack>
using namespace std;


//300.

stack<int> tmp;
int res=1;

// void printStack(stack<int> s){
//     while(s.size()>1){
//         cout<< s.top()<<" ";
//         s.pop();
//     }
//     cout<<endl;
// }

void dfs(vector<int>& nums,int cur){
    int size = tmp.size()-1;
    res = max(res,size);
    if(cur>nums.size()-1){
        return;
    }
    // printStack(tmp);
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

int main(){
    // vector<int> nums = {1,3,6,7,9,4,10,5,6};
    vector<int> nums = {1,3,6,7,4};
    cout<<lengthOfLIS(nums)<<endl;
    return 0;
}