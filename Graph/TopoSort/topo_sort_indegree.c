/*******************************************************************
*  File        : topo_sort_kahn.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-04 03:10:33(+0000)
*  Modified    : 2019-01-04 03:10:41(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : topolkogical sort based Kahn Algorithm(indegree)
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// topolkogical sort for DAG presented by Adjacent Matrix
int *topo_sort_kahn_matrix(int ** M, int n){
    int i = 0, j=0;
    int *seq = (int *)malloc(sizeof(int) * n);        // topolkogical order
    int *indegree = (int *)malloc(sizeof(int) * n); // vertex's indegree
    int *S = (int *)malloc(sizeof(int) * n);        // 0-indegree unvisted vertex set
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size
    int p = -1;                                     // stack S's top
    
    // calculate indegree
    for(j =0 ; j < n ; j++){
        indegree[j] = 0;
        for(i =0 ; i< n ; i++){
            indegree[j] += M[i][j];
        }
    }
    // start with 0-indegree vertex
    for(i =0 ; i< n ; i++){
        if(indegree[i] == 0){
            p += 1;
            S[p] = i;
        }
        mark[i] = 0;
    }
    while(p >= 0){
        int v = S[p];
        p -= 1;
        if(mark[v] == 1){   // circle
            break;
        }
        count++;
        seq[count] = v;
        mark[v] = 1;
        for(j =0 ; j < n ; j++){
            // update adjacent vertex
            if(M[v][j] == 1){
                indegree[j] --;
                if(indegree[j] == 0){
                    p += 1;
                    S[p] = j;
                }
            }
        }
    }
    
    free(indegree);
    free(S);
    free(mark);
    // circle judging 
    if (count < n - 1 ){
        return NULL;
    }
    return seq;
}

typedef struct node{ // 邻接表
    int data;
    struct node *next;
}Node;

// topolkogical sort for DAG presented by Adjacent Table
int *topo_sort_kahn_table(Node * T, int n){
    int i = 0, j=0;
    int *seq = (int *)malloc(sizeof(int) * n);      // topolkogical order
    int *indegree = (int *)malloc(sizeof(int) * n); // vertex's indegree
    int *S = (int *)malloc(sizeof(int) * n);        // 0-indegree unvisted vertex set
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size
    int p = -1;                                     // stack S's top
    Node *temp = NULL;
    memset(indegree, 0 , sizeof(int) * n);
    // calculate indegree
    for(i =0 ; i< n ; i++){
        temp = T[i].next;
        while(temp != NULL){
            indegree[temp->data] += 1;
            temp = temp->next;
        }
    }
    // start with 0-indegree vertex
    for(i =0 ; i< n ; i++){
        if(indegree[i] == 0){
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
        mark[v] = 1;
        count++;
        seq[count] = v;
        temp = T[v].next;    // update ajacent vertex
        while(temp != NULL){  
            indegree[temp->data] --;
            if(indegree[temp->data] == 0){
                p += 1;
                S[p] = temp->data;
            }
            temp = temp->next;
        }
    }
    
    free(indegree);
    free(S);
    free(mark);
    // circle judging 
    if (count < n - 1 ){
        return NULL;
    }
    return seq;
}


int main(){
    int i = 0, vin, vout;
    int n, m;
    int *seq;       // topo-order
    
#define MATRIX 1

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
    seq = topo_sort_kahn_matrix(M, n);
    
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
    // build adjacent Table
    for(i = 0; i < m; i++){
        scanf("%d %d", &vout, &vin);
        temp = (Node *)malloc(sizeof(Node));
        temp->data = vin;
        temp->next = T[vout].next;
        T[vout].next = temp;
    }
    // Kahn Alogrithm
    seq = topo_sort_kahn_table(T, n);
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