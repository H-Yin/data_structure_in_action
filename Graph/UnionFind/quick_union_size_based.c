/*******************************************************************
*  File        : quick_union_size_based.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2018-12-24 09:11:53(+0000)
*  Modified    : 2018-12-24 14:17:46(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : Size-based Optimized Quick-Union
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int N = 0;          // vertex num
int *ids = NULL;    // vertex array
int *size = NULL;   // vectex's tree size

void UnionFind(int n){
    int i=0;
    ids=(int *)malloc(sizeof(int)*n);
    size=(int *)malloc(sizeof(int)*n);
    if(ids == NULL || size == NULL){
        printf("memory allocation is failed.");
        exit(-1);
    }
    for(i=0; i < n; i++){
        ids[i] = i;
        size[i] = 1; // initialize size of every node
    }
}

void Union(int a, int b){
    int i = Find(a);
    int j = Find(b);
    if (i != j){      // unconnected branches
        if(size[i] >= size[j]){
            ids[j] = i;
            size[i] += size[j]; // increase size
        }else{
            ids[i] = j;
            size[j] += size[i];
        }
    }
}

int Find(int a){
    // recursive lookup root
    while( ids[a] != a){
        a = ids[a];
    }
    return a;
}

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

