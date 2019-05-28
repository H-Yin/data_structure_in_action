/*******************************************************************
*  File        : shell_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-07 07:13:12(+0000)
*  Modified    : 2019-01-07 07:13:23(+0000)
*  GitHub      : https://github.com/H-Yin/
*  Description : shell sort
*******************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int *H = NULL;
int hsize=0;

int init_gaps(int *H, int *hsize, int n){
    int i = 0, k = 2;
    *hsize = (int)(log(n) / log(2));
    H = (int *)malloc(sizeof(int)* *hsize);
    for(i = 0; i < *hsize-1; i++){
        H[i] = n / k;
        k *= 2;
    }
    H[*hsize -1] = 1;
}

int insertion_sort(int *a, int n, int gap){
    int temp;
    int i = 0, j = 0;
    for(i = 0; i < n ;i++){
        // compare and exchange from the end
        for(j = i + gap; j < n && a[j-gap] > a[j]; j += gap){
            temp = a[j-gap];
            a[j-gap] = a[j];
            a[j] = temp;
        }
    }
}

int shell_sort(int *a, int n){
    int temp;
    int i = 0, j = 0;
    for(i = 1; i < n ;i++){
        // compare and exchange from the end
        for(j = i; j > 0 && a[j-1] > a[j]; j--){
            temp = a[j-1];
            a[j-1] = a[j];
            a[j] = temp;
        }
    }
}

int main(){
    int i = 0;
    int a[10] = {4, 6, 3, 8, 9, 3, 5, 2, 7, 0};
    insertion_sort(a, 10);

    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}


