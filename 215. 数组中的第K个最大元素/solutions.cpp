#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//解法1，api
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(),nums.end());
        return nums[nums.size()-k];
    }
};

//解法2，冒泡排序
//每次确定一个最大的，确定k个，就找到了
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        for(int i=0;i<k;i++){
            for(int j=0;j<nums.size()-1-i;j++){
                if(nums[j+1]<nums[j]){
                    swap(nums[j],nums[j+1]);
                }
            }
        }
        return nums[nums.size()-k];
    }
};

//解法3，快排，递增排序，每次确定一个数的位置
class Solution {
public:
    // 快速排序
    int quickSelect(vector<int>& nums,int left,int right,int k){
        int q = rand()%(right-left+1)+left;
        //采用左端点作为基准值，并且为了加快速度，每次用随机数更换左端点。
        swap(nums[q],nums[left]);
        int x = nums[left];
        int i = left,j = right;
        //递增排序
        while(i<j){
            while(i<j && nums[j]>=x){
                j--;
            }
            nums[i] = nums[j];
            while(i<j && nums[i]<=x){
                i++;
            }
            nums[j] = nums[i];
        }
        nums[i] = x;
        if(i==k){
            return x;
        }
        else if(i>k){
            return quickSelect(nums,left,i-1,k);
        }
        else{
            return quickSelect(nums,i+1,right,k);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums,0,nums.size()-1,nums.size()-k);
    }
};

//解法4，快排，递减排序
class Solution {
public:
    // 快速排序
    int quickSelect(vector<int>& nums,int left,int right,int k){
        int q = rand()%(right-left+1)+left;
        //采用左端点作为基准值，并且为了加快速度，每次用随机数更换左端点。
        swap(nums[q],nums[left]);
        int x = nums[left];
        int i = left,j = right;
        //递减排序
        while(i<j){
            while(i<j && nums[j]<=x){
                j--;
            }
            nums[i] = nums[j];
            while(i<j && nums[i]>=x){
                i++;
            }
            nums[j] = nums[i];
        }
        nums[i] = x;
        if(i==k-1){
            return x;
        }
        else if(i>k-1){
            return quickSelect(nums,left,i-1,k);
        }
        else{
            return quickSelect(nums,i+1,right,k);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums,0,nums.size()-1,k);
    }
};

//解法5，大根堆
class Solution {
public:
    // 建立一个大根堆，做 k-1 次删除操作后堆顶元素即为所求

    //调整第i个元素的位置
    void maxHeapify(vector<int>& nums,int size,int i){
        int left = i*2+1;
        int right =  i*2+2;
        int m = i;
        if(left<size && nums[left]>nums[m]){
            m = left;
        }
        if(right<size && nums[right]>nums[m]){
            m = right;
        }
        if(m!=i){
            //找到节点i和两个子节点中的最大值和i进行交换
            swap(nums[i],nums[m]);
            //递归修改之后的子节点
            maxHeapify(nums,size,m);
        }
    }
    //建立大根堆
    void buildMaxHeap(vector<int>& nums,int size){
        //从下到上进行构建
        for(int i=size/2;i>=0;i--){
            maxHeapify(nums,size,i);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        int size = nums.size();
        buildMaxHeap(nums,size);
        //删除k-1次堆顶元素nums[0]
        for(int i=nums.size()-1;i>=nums.size()-k+1;i--){
            swap(nums[0],nums[i]);
            size--;
            maxHeapify(nums,size,0);
        }
        return nums[0];
    }
};

//解法6，小根堆
class Solution {
public:
    // 建立一个小根堆k，堆顶元素即为所求

    //调整第i个元素的位置
    void minHeapify(vector<int>& nums,int size,int i){
        int left = i*2+1;
        int right =  i*2+2;
        int m = i;
        if(left<size && nums[left]<nums[m]){
            m = left;
        }
        if(right<size && nums[right]<nums[m]){
            m = right;
        }
        if(m!=i){
            //找到节点i和两个子节点中的最小值和i进行交换
            swap(nums[i],nums[m]);
            //递归修改之后的子节点
            minHeapify(nums,size,m);
        }
    }
    //建立size为k的小根堆
    void buildMinHeap(vector<int>& nums,int size){
        //从下到上进行构建
        for(int i=size/2;i>=0;i--){
            minHeapify(nums,size,i);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        int size = nums.size();
        buildMinHeap(nums,k);
        //将nums中剩余元素依次与堆顶元素比较，大于则替换
        for(int i=k;i<=size-1;i++){
            if(nums[i]>nums[0]){
                nums[0] = nums[i];
                minHeapify(nums,k,0);
            }
        }
        return nums[0];
    }
};