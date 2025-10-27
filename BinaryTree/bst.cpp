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

Node* leftRotate(Node* node){
    Node* newRoot = node->right;
    Node* temp = newRoot->left;

    newRoot->left = node;
    node->right = temp;

    node->height = 1 + max(height(node->left), height(node->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
    
}
Node* rightRotate(Node* node){
    Node* newRoot = node->left;
    Node* temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = 1 + max(height(node->left), height(node->right));
    newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

    return newRoot;
}

Node* rotate(Node* root){
    int balance = height(root->left)-height( root->right);

    if(balance>1){
        //Left Heavy (2 cases)
        if(height(root->left->left) - height(root->left->right) >=0){
            //Left-Left Case
            return rightRotate(root);
        }
        else{
            //Left-Right Case
            root->left = leftRotate(root->left);
            return rightRotate(root);

        }
    }
    else if(balance<-1){
        //Right Heavy
        if(height(root->right->right) - height(root->right->left) >=0){
            //Right-Right Case
            return leftRotate(root);
        }
        else{
            //Right-Left Case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
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
    return rotate(root);
    // return root;
}

bool isbalanced(Node* root){
    if (root == nullptr){
        return true;
    }
    return abs(height(root->left) - height(root->right)) <= 1 && isbalanced(root->left) && isbalanced(root->right);
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
    root = insert(root, 80);
    root = insert(root, 90);
    root = insert(root, 130);
    root = insert(root, 140);
    root = insert(root, 150);
    root = insert(root, 160);

    cout<<"BST Inorder traversal: ";
    inorder(root);
    cout<<"height: "<<height(root)<<endl;
    cout<<"is balanced: "<<(isbalanced(root) ? "true" : "false")<<endl;
    cout<<endl;

    return 0; 
}