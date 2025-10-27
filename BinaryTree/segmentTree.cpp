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

void update(Node* node, int idx, int val){
    if(!node || idx<node->start || idx>node->end){
        return;
    }
    if(node->start == node->end){
        node->sum = val;
        return;
    }
    int mid = (node->start + node->end)/2;
    if(idx <= mid){
        update(node->left, idx, val);
    }
    else{
        update(node->right, idx, val);
    }

    node->sum = node->left->sum + node->right->sum;
    
}

void display(Node* node, string indent = "    ", bool isLeft = true) {
    if (!node) return;

    // Print right child first (for better visual tree structure)
    display(node->right, indent + (isLeft ? "│   " : "    "), false);

    // Print current node
    cout << indent;
    if (isLeft)
        cout << "└── ";
    else
        cout << "┌── ";

    cout << "[" << node->start << "," << node->end << "]"
         << " sum=" << node->sum << endl;

    // Print left child
    display(node->left, indent + (isLeft ? "    " : "│   "), true);
}



int main(){
    vector<int> arr = {3,8, 7, 6, -2, -8, 4, 9};
    Node* root = buildTree(arr, 0, arr.size()-1);

    cout<< "Sum from idx 2 to 6 is : "<<query(root, 2,6)<<endl;

    update(root, 3, 14); // arr[3] = 14

    cout<< "Sum from idx 2 to 6 is after updating : "<<query(root, 2,6)<<endl;

    display(root, "        ");

    return 0;
}