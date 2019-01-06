/*******************************************************************
*  File        : quick_union_height_based.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2018-12-24 09:11:53(+0000)
*  Modified    : 2018-12-24 14:17:22(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : Height-based Optimized Quick-Union
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int N = 0;          // vertex num
int *ids = NULL;    // vertex array
int *height = NULL; // vectex's tree height

void UnionFind(int n){
    int i=0;
    ids=(int *)malloc(sizeof(int)*n);
    height=(int *)malloc(sizeof(int)*n);
    if(ids == NULL || height == NULL){
        printf("memory allocation is failed.");
        exit(-1);
    }
    for(i=0; i < n; i++){
        ids[i] = i;
        height[i] = 1; // initialize height of every node
    }
}

void Union(int a, int b){
    int i = Find(a);
    int j = Find(b);
    if (i != j){      // unconnected branches
        if(height[i] > height[j]){
            ids[j] = i;
        }else if(height[i] < height[j]){
            ids[i] = j;
        }else{
            ids[j] = i;   // parent id
            height[j] += 1; // increase height
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

