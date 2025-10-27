#include <bits/stdc++.h>
using namespace std;

struct Node {
    int start, end;
    int sum;
    Node *left, *right;


    Node(int s, int e){
        start = s;
        end = e;
        sum = 0;
        left = right = nullptr;
    }
};

Node* buildTree(const vector<int> &arr, int s, int e){
    // here we are building segment tree
    Node* node = new Node(s,e);
    if(s==e){
        node->sum = arr[s];
        return node;
    }
    int mid = (s+e)/2;
    node->left = buildTree(arr, s, mid);
    node->right = buildTree(arr, mid+1, e);
    node->sum = node->left->sum + node->right->sum;
    return node;
}

int query(Node* node, int l, int r){

    if(!node || l>node->end || r<node->start){
        // completely outside
        return 0;
    }

    else if(l<=node->start && r>=node->end){
        // completely inside
        return node->sum;
    }
    // partially inside and partially outside
    return query(node->left, l, r)+query(node->right, l, r);

}

int main(){
    vector<int> arr = {3,8, 7, 6, -2, -8, 4, 9};
    Node* root = buildTree(arr, 0, arr.size()-1);

    cout<< "Sum from idx 2 to 6 is : "<<query(root, 2,6)<<endl;

    return 0;
}