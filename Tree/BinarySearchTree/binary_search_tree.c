/*******************************************************************
*  File        : binary_search_tree.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-09 13:34:19(+0000)
*  Modified    : 2019-01-09 13:36:33(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : Binary Search Tree
*******************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct _node{
    int key;                // key word
    struct _node *left;     // left child
    struct _node *right;    // right child
}*Node;

typedef struct _tree{
    Node root;      // tree's root;
    int nums;       // the number of tree's node
}*BST;

#define NODE_SIZE sizeof(struct _node)
#define BST_SIZE sizeof(struct _tree)

BST bst_create(){
    BST bst = (BST)malloc(BST_SIZE);
    if(bst == NULL){
        printf("memory allocation faild.");
        exit(-1);
    }
    bst -> root = NULL;
    bst -> nums = 0;
}

int bst_search(Node root, int key){
    if(root == NULL){
        return -1;
    }
    if(root->key == key){
        return 0;
    }else if(key < root->key){
        return bst_search(root->left, key);
    }else{
        return bst_search(root->right, key);
    }
}

Node _bst_search_parent(Node root, int key){
    if (root == NULL || root->key == key){
        return NULL;
    }
    if(root->left->key == key || root->right->key == key){
        return root;
    }
    if(key < root->key){
        return _bst_search_parent(root->left, key);
    }else{
        return _bst_search_parent(root->right, key);
    }
}

int bst_insert(BST bst, int key){
    Node node, cur = bst->root;
    node = (Node)malloc(NODE_SIZE);
    node -> key = key;
    node -> left = NULL;
    node -> right = NULL;
    
    if(cur == NULL){
        bst->root = node;
    }else{
        while(1){
            if(key == cur->key){
                printf("Key %d already exists.", key);
                return -1;
            }else if(key < cur->key ){
                if(cur->left == NULL){
                    cur->left = node;
                    break;
                }else{
                    cur = cur->left;
                }
            }else{
                if(cur->right == NULL){
                    cur->right = node;
                    break;
                }else{
                    cur = cur->right;
                }
            }    
        }
    }
    return 0;
}

int bst_delete(BST root, int key){
    return 0;
}

int bst_verify(BST root, int key){
    return 0;
}
int bst_print(Node root){
    if(root != NULL){
        if(root->left != NULL){
            printf("%d -> %d(left)", root->key, root->left->key);
            bst_print(root->left);
        }
        if(root->right != NULL){
            printf("%d -> %d(right), ", root->key, root->right->key);
            bst_print(root->right);
        }
    }
    return 0;
}

int main(){
    
    BST tree = bst_create();
    bst_insert(tree, 4);bst_print(tree->root); printf("\n");
    bst_insert(tree, 1);bst_print(tree->root); printf("\n");
    bst_insert(tree, 2);bst_print(tree->root); printf("\n");
    bst_insert(tree, 3);bst_print(tree->root); printf("\n");
    bst_insert(tree, 5);bst_print(tree->root); printf("\n");
    bst_insert(tree, 0);bst_print(tree->root); printf("\n");
    
    return 0;
}
