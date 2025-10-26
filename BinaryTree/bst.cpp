#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val){
        data = val;
        left = right = nullptr;
    }
};

int height(Node* root){
    if(root == nullptr){
        return 0;
    }
    return root->height;
}

Node* insert(Node* root, int val){
    if(root == nullptr){
        return new Node(val);
    }
    if(val < root->data){
        root->left = insert(root->left, val);
    }
    else{
        root->right = insert(root->right, val);
    }
    root->height = 1 + max(height(root->left), height(root->right));
    return root;
}

void inorder(Node* root){
    if(root == nullptr){
        return;
    }
    inorder(root->left);
    cout<<root->data<<" ";
    inorder(root->right);
}



int main(){

    Node* root = nullptr;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 20);
    root = insert(root, 70);
    root = insert(root, 60);

    cout<<"BST Inorder traversal: ";
    inorder(root);
    cout<<"height: "<<height(root);
    cout<<endl;

    return 0;
}