/*******************************************************************
*  File        : quick_union.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2018-12-24 09:11:53(+0000)
*  Modified    : 2018-12-24 09:12:06(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : Quick-Union version of UnionFind
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int N = 0;          // vertex num
int *ids = NULL;    // vertex array

void UnionFind(int n){
    int i=0;
    ids=(int *)malloc(sizeof(int)*n);
    if(ids == NULL){
        printf("memory allocation is failed.");
        exit(-1);
    }
    for(i=0; i < n; i++){
        ids[i] = i;
    }
}

void Union(int a, int b){
    int i = Find(a);
    int j = Find(b);
    if (i != j){      // unconnected branches
        ids[j] = i;   // parent id
    }
}
/*
// One-Pass
int Find(int a){
    // recursive lookup root
    if( ids[a] != a){
        // find root and update id back
        ids[a] = Find(ids[a]);
    }
    return ids[a];
}
// One-Pass-Variant
int Find(int a){
    // recursive lookup root
    while( ids[a] != a){
        ids[a] = ids[ids[a]];  // half the path
        a = ids[a];
    }
    return a;
}
// Two-Pass
int Find(int a){
    int current = a, parent;
    // recursive lookup root
    while( ids[current] != current){
        current = ids[current];
    }
    // current is root
    // update all node
    while( ids[a] != a){
        parent = ids[a];
        ids[a] = current;
        a = parent;
    }
    return current;
}
*/


int IsConnected(int a, int b){
    return (Find(a) == Find(b));
}

int Count(){
    int c = 0, i = 0;
    for (i = 0; i < N; i++){
        if(ids[i] == i){
            c += 1;
        }
    }
    return c;
}

void display(){
    int i = 0;
    for(i = 0; i< N; i++){
        printf("%d ", ids[i]);
    }
}

int main(){
    int i=0, m, a, b;
    scanf("%d %d", &N, &m);
    UnionFind(N);
    for(i=0; i<m; i++){
        scanf("%d,%d", &a, &b);
        Union(a,b);
        display();               // ids
        printf("%d\n", Count()); // branch number
    }
}

