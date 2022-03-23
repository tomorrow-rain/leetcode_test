#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//解法1，暴力
//前序遍历，找到p和q之前的节点的父节点，计入到map中，然后依次找到两个节点的全部父节点，放入两个vector中
//将元素多的vecotr放入到set中，从头遍历元素少的vector，在set中查找，找到的第一个节点，就是所求

class Solution {
public:
    unordered_map<TreeNode*,TreeNode*> pre;
    void preOrder(TreeNode* root, TreeNode* p, TreeNode* q){
        if(!root){
            return;
        }
        if(pre.find(p)!=pre.end() && pre.find(q)!=pre.end()){
            return;
        }
        if(root->left){
            pre[root->left] = root;
            preOrder(root->left,p,q);
        }
         if(root->right){
            pre[root->right] = root;
            preOrder(root->right,p,q);
        }
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pre[root] = nullptr;
        preOrder(root,p,q);
        vector<TreeNode*> vp,vq;
        TreeNode* tmp;
        tmp = p;
        while(tmp){
            vp.push_back(tmp);
            tmp = pre[tmp];
        }
        tmp = q;
        while(tmp){
            vq.push_back(tmp);
            tmp = pre[tmp];
        }

        if(vp.size()>=vq.size()){
            unordered_set<TreeNode*> s(vp.begin(),vp.end());
            for(int i=0;i<=vq.size();i++){
                if(s.count(vq[i])){
                    return vq[i];
                }
            }
            return nullptr;
        }
        else{
            unordered_set<TreeNode*> s(vq.begin(),vq.end());
            for(int i=0;i<=vp.size();i++){
                if(s.count(vp[i])){
                    return vp[i];
                }
            }
            return nullptr;
        }
    }
};


// 解法2 类似于解法1，优化

class Solution {
public:
    // 因为节点数值都不相同，可以用val代指节点
    unordered_map<int, TreeNode*> fa;
    unordered_map<int, bool> vis;

    void dfs(TreeNode* root){
        if(!root){
            return;
        }
        if(root->left){
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if(root->right){
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        fa[root->val] = nullptr;
        dfs(root);
        // 走一遍p的所有父节点，vis记录
        while(p){
            vis[p->val] = true;
            p = fa[p->val];
        }
        // 走q的父节点，如果被vis过，就返回
        while(q){
            if(vis[q->val]){
                return q;
            }
            q = fa[q->val];
        }
        return nullptr;
    }
};


//解法3 LCA经典解法
// 递归
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || p==root || q==root){
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left,p,q);
        TreeNode* right = lowestCommonAncestor(root->right,p,q);
        // 在两边
        if(left && right){
            return root;
        }
        // 都在左边
        if(left){
            return left;
        }
        // 都在右边
        return right;
    }
};
