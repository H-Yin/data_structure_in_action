/*******************************************************************
*  File        : topo_sort_outdegree.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-04 03:10:33(+0000)
*  Modified    : 2019-01-04 03:10:41(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : topolkogical sort based outdegree array
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// topolkogical sort for DAG presented by Adjacent Matrix
int *topo_sort_outdegree_matrix(int ** M, int n){
    int i = 0, j=0, temp;
    int *seq = (int *)malloc(sizeof(int) * n);        // topolkogical order
    int *outdegree = (int *)malloc(sizeof(int) * n); // vertex's outdegree
    int *S = (int *)malloc(sizeof(int) * n);        // 0-outdegree unvisted vertex set
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size
    int p = -1;                                     // stack S's top
    
    // calculate outdegree
    for(i =0 ; i< n ; i++){
        outdegree[i] = 0;
        for(j =0 ; j < n ; j++){
            outdegree[i] += M[i][j];
        }
    }
    // start with 0-outdegree vertex
    for(i =0 ; i< n ; i++){
        if(outdegree[i] == 0){
            p += 1;
            S[p] = i;
        }
        mark[i] = 0;
    }
    while(p >= 0){
        int v = S[p];
        p -= 1;
        if(mark[v] == 1){
            break;
        }
        count++;
        seq[count] = v;

        mark[v] = 1;
        for(i =n-1 ; i >=0 ; i--){      // update ajacent vertex's outdegree
            if(M[i][v] == 1){
                outdegree[i] --;
                if(outdegree[i] == 0){
                    p += 1;
                    S[p] = i;
                }
            }
        }
    }
    
    free(outdegree);
    free(S);
    free(mark);
    // circle judging 
    if (count < n - 1 ){
        return NULL;
    }
    // reverse seq
    for(i=0; i < n / 2 ; i++){
        temp = seq[i];
        seq[i] = seq[n-i-1]; // a + b = n-1
        seq[n-i-1] = temp;
    }
    return seq;
}

typedef struct node{
    int data;
    struct node *next;
}Node;

// topolkogical sort for DAG presented by inverse Adjacent Table
int *topo_sort_outdegree_table(Node * T, int n){
    int i = 0, j=0, temp;
    int *seq = (int *)malloc(sizeof(int) * n);      // topolkogical order
    int *outdegree = (int *)malloc(sizeof(int) * n); // vertex's outdegree
    int *S = (int *)malloc(sizeof(int) * n);        // 0-outdegree unvisted vertex set
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size
    int p = -1;                                     // stack S's top
    Node *cur = NULL;
    memset(outdegree, 0 , sizeof(int) * n);
    // calculate outdegree
    for(i =0 ; i< n ; i++){
        cur = T[i].next;
        while(cur != NULL){
            outdegree[cur->data] += 1;
            cur = cur->next;
        }
    }
    // start with 0-outdegree vertex
    for(i =0 ; i< n ; i++){
        if(outdegree[i] == 0){
            p += 1;
            S[p] = i;
        }
        mark[i] = 0;
    }
    while(p >= 0){
        int v = S[p];
        if(mark[v] == 1){
            break;
        }
        count++;
        seq[count] = v;
        p -= 1;
        mark[v] = 1;
        cur = T[v].next;
        while(cur != NULL){
            outdegree[cur->data] --;
            if(outdegree[cur->data] == 0){
                p += 1;
                S[p] = cur->data;
            }
            cur = cur->next;
        }
    }
    
    free(outdegree);
    free(S);
    free(mark);
    // circle judging 
    if (count < n - 1 ){
        return NULL;
    }
    
    // reverse seq
    for(i=0; i < n / 2 ; i++){
        temp = seq[i];
        seq[i] = seq[n-i-1]; // a + b = n-1
        seq[n-i-1] = temp;
    }
    
    return seq;
}


int main(){
    int i = 0, vin, vout;
    int n, m;
    int *seq;       // topo-order
    
#define MATRIX 0

#if MATRIX
    int **M;
    // input
    scanf("%d %d", &n, &m);
    M = (int **)malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++){
        M[i] = (int *)malloc(sizeof(int) * n);
        memset(M[i], 0, sizeof(int) * n);
    }
    // build adjacent matrix 
    for(i = 0; i < m; i++){
        scanf("%d %d", &vout, &vin);
        M[vout][vin] = 1;
    }
    // Kahn Alogrithm 
    seq = topo_sort_outdegree_matrix(M, n);
    
    // Free M
    for(i = 0; i < n; i++){
        free(M[i]);
    }
    free(M);
#else
    Node *T, *temp;
    // input
    scanf("%d %d", &n, &m);
    T = (Node *)malloc(sizeof(Node) * n);
    for(i = 0; i < n; i++){
        T[i].next = NULL;
    }
    // build inverse adjacent Table
    for(i = 0; i < m; i++){
        scanf("%d %d", &vout, &vin);
        temp = (Node *)malloc(sizeof(Node));
        temp->data = vout;
        temp->next = T[vin].next;
        T[vin].next = temp; 
    }
    // Kahn Alogrithm
    seq = topo_sort_outdegree_table(T, n);
    // free T
    for(i =0 ; i< n ; i++){
        while(T[i].next != NULL){
            temp = T[i].next;
            T[i].next = temp->next;
            free(temp);
        }
    }
    free(T);
#endif
    if(seq == NULL){
        printf("there is a cycle in DAG.\n");
    }else{
        printf("\n");
        for(i = 0; i < n; i++){
            printf("%d ", seq[i]);
        }
        printf("\n");
    }
    free(seq);
    
    return 0;
}