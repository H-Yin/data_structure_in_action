/*******************************************************************
*  File        : topo_sort_dfs_enhanced.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-04 03:10:33(+0000)
*  Modified    : 2019-01-04 12:23:28(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : Topological sort based Depth-First-Search Algorithm 
*                (including Circle Detection)
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// topolkogical sort for DAG presented by Adjacent Matrix
int dfs_matrix(int **M, int n, int *mark, int u, int *seq, int *count){
    int i=0, res=0;
    
    if (mark[u] == 1){ // visited permamently
        return 1;
    }
    if (mark[u] == -1){ // visited temporarily , not a DAG
        return -1;
    }
    mark[u] = -1;
    for(i=0; i < n; i++){
        if(M[u][i] == 1){
            res =  dfs_matrix(M, n, mark, i, seq, count); // have circle
            if (res == -1){
                return -1;
            }
        }
    }
    mark[u] = 1;
    // Add u to L
    (*count) ++;
    seq[*count] = u;
    
    return 0;
}


int *topo_sort_dfs_matrix(int ** M, int n){
    int i = 0, j = 0, res = 0, temp;
    int *seq = (int *)malloc(sizeof(int) * n);      // topolkogical order
    int *indegree = (int *)malloc(sizeof(int) * n); // vertex's indegree
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size
    
    memset(mark, 0 , sizeof(int) * n);
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
            res = dfs_matrix(M, n, mark, i, seq, &count);
            if(res == -1){
                break;
            }
        }
    }
    
    free(indegree);
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

// topolkogical sort for DAG presented by Adjacent Table
int dfs_table(Node *T, int *mark, int u, int *seq, int *count){
    int res = 0;
    Node *cur = NULL;
    if (mark[u] == 1){
        return 1;
    }
    if (mark[u] == -1){
        return -1;
    }
    mark[u] = -1;
    cur = T[u].next;
    while(cur != NULL){
        res = dfs_table(T, mark, cur->data, seq , count);
        if(res == -1){
            return -1;
        }
        cur = cur->next;
    }
    
    mark[u] = 1;
    (*count) ++;
    seq[*count] = u;
    
    return 0;
}

int *topo_sort_dfs_table(Node * T, int n){
    int i = 0, j=0, temp, res=0;
    Node *cur;
    int *seq = (int *)malloc(sizeof(int) * n);      // topolkogical order
    int *indegree = (int *)malloc(sizeof(int) * n); // vertex's indegree
    int *mark = (int *)malloc(sizeof(int) * n);     // visited flag
    int count = -1;                                 // seq's size

    memset(mark, 0, sizeof(int) * n);
    memset(indegree, 0, sizeof(int) * n);
    // calculate indegree
    for(i =0 ; i< n ; i++){
        cur = T[i].next;
        while(cur != NULL){
            indegree[cur->data] += 1;
            cur = cur->next;
        }
    }
    // start with 0-indegree vertex
    for(i =0 ; i< n ; i++){
        if(indegree[i] == 0){
            res = dfs_table(T, mark, i, seq , &count);
            if(res == -1){
                break;
            }
        }
    }
    
    free(indegree);
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
    // DFS Alogrithm 
    seq = topo_sort_dfs_matrix(M, n);
    
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
    // DFS Alogrithm
    seq = topo_sort_dfs_table(T, n);
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


