/*******************************************************************
*  File        : selection_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-06 11:07:48(+0000)
*  Modified    : 2019-01-06 12:47:59(+0000)
*  GitHub      : https://github.com/H-Yin/
*  Description : selection sort
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int selection_sort(int *a, int n){
    int min, temp;
    int i = 0, j = 0, min_i;
    for(i=0; i < n-1; i++){
        min = a[i];
        min_i = i;
        for(j = i+1;j < n; j++){
            if(min > a[j]){
                min_i = j;
                min = a[j];
            }
        }
        temp = a[i];
        a[i] = a[min_i];
        a[min_i] = temp;
    }
}

int main(){
    int i = 0;
    int a[10] = {4, 6, 3, 8, 9, 3, 5, 2, 7, 0};
    selection_sort(a, 10);
    
    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    
    return 0;
}
