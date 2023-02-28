#include <bits/stdc++.h>
using namespace std;

class TreeNode{
    public:
    TreeNode*left;
    TreeNode*right;
    int val;
    TreeNode(int val){
        this->left = NULL;
        this->right = NULL;
        this->val = val;
    }
};

unordered_map<int,int>mp; // maps freq with corresponding keys

// Tree maker
TreeNode*make(vector<vector<int>>&matrix,vector<vector<int>>rootMatrix,int sz,vector<int>&keys,int i,int j){
    if(i>j || matrix[i][j] == -1){
        return NULL;
    }
    if(i == j){
        TreeNode*root = new TreeNode(mp[matrix[i][j]]);
        return root;
    }
    TreeNode*root = new TreeNode(keys[rootMatrix[i][j]]);
    root->left = make(matrix,rootMatrix,sz,keys,i,rootMatrix[i][j] - 1);
    root->right = make(matrix,rootMatrix,sz,keys,rootMatrix[i][j] + 1,j);
    return root;
}

void print_level_order_traversal(TreeNode*root){
    if(root->val == -1){
        return;
    }
    queue<TreeNode*>q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        TreeNode*f = q.front();
        q.pop();
        if(f == NULL){
            cout<<endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout<<f->val<<" ";
            if(f->left){
                q.push(f->left);
            }
            if(f->right){
                q.push(f->right);
            }
        }
    }
}

void print(vector<vector<int>>&matrix){
    int M = matrix.size();
    int N = matrix[0].size();
    for(int i = 0;i<M;i++){
        for(int j = 0;j<N;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int getCost(vector<vector<int>>&matrix,vector<vector<int>>&rootMatrix,int sz,int init,int starter, int ender,int currRootIndex,vector<int>&keys,vector<int>&freq){
    int sum = 0;
    for(int i = starter;i<=ender;i++){
        sum += freq[i];
    }
    int leftStart = starter;
    int leftEnd = currRootIndex - 1;
    int rightStart = currRootIndex + 1;
    int rightEnd = ender;
    if(currRootIndex == starter){
        leftEnd = -1;
        leftStart = -1;
    }
    if(currRootIndex == ender){
        rightEnd = -1;
        rightStart = -1;
    }
    int leftSum = 0;
    int rightSum = 0;
    if(leftStart != -1 && leftEnd != -1){
        sum += matrix[leftStart][leftEnd];
    }
    if(rightStart != -1 && rightEnd != -1){
        sum += matrix[rightStart][rightEnd];
    }
    return sum;
}
vector<vector<int>>finalMatrix(vector<vector<int>>&matrix,vector<vector<int>>&rootMatrix,int sz,vector<int>&keys,vector<int>&freq){
    int start = 0;
    for(int i = 0;i<sz;i++){
        matrix[i][i] = freq[i];
    }
    int init = 2;
    int starter = 0;
    int ender = 0;
    while(init<=sz){
        starter = 0;
        ender = init - 1;
        while(ender < sz){
            int mn = INT_MAX;
            unordered_map<int,int>mp;
            int final_root = -1;
            for(int i = starter;i<=ender;i++){
                int temp = mn;
                mn = min(mn,getCost(matrix,rootMatrix,sz,init,starter,ender,i,keys,freq));
                if(mn != temp){
                    final_root = i;
                }
            }
            matrix[starter][ender] = mn;
            rootMatrix[starter][ender] = final_root;
            starter++;
            ender++;
        }
        init++;
    }
    for(int i = 0;i<sz;i++){
        mp[freq[i]] = keys[i];
    }
    TreeNode*root = make(matrix,rootMatrix,sz,keys,0,sz - 1);
    cout<<"The generated matrix is : "<<endl;
    print(matrix);
    cout<<"The generated root matrix is : "<<endl;
    print(rootMatrix);
    cout<<"The generated tree is : "<<endl;
    print_level_order_traversal(root);
    return matrix;
}
int main(){
    vector<int>keys;
    vector<int>freq;
    int sz;
    cout<<"Enter the dimension of the matrix"<<endl;
    cin>>sz;
    for(int i = 0;i<sz;i++){
        cout<<"Enter the key number "<<i + 1<<endl;
        int tempKey;
        cin>>tempKey;
        keys.push_back(tempKey);
        cout<<"Enter the frequency of "<<tempKey<<endl;
        int tempFreq;
        cin>>tempFreq;
        freq.push_back(tempFreq);
    }
    vector<vector<int>>min_matrix(sz,vector<int>(sz,-1));
    vector<vector<int>>rootMatrix(sz,vector<int>(sz,-1));
    vector<vector<int>>result = finalMatrix(min_matrix,rootMatrix,sz,keys,freq);
    return 0;
}