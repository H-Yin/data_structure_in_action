/*******************************************************************
*  File        : bubble_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-06 12:38:32(+0000)
*  Modified    : 2019-01-06 12:49:20(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : bubble sort
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int bubble_sort(int *a, int n){
    int temp;
    int i = 0, j = 0;
    for(i = 0; i < n ;i++){
        for(j = 1; j < n-i; j++){
            if(a[j-1] > a[j]){
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
            }
        }
    }
}

int bubble_sort_flag(int *a, int n){
    int temp, flag = 1; // stop flag 
    int i = 0, j = 0;
    for(i = 0; i < n ;i++){
        for(flag = 1, j = 1; j < n-i; j++){
            if(a[j-1] > a[j]){
                temp = a[j-1];
                a[j-1] = a[j];
                a[j] = temp;
                flag = 0;
            }
        }
        if(flag){
            break;
        }
    }
}

int main(){
    int i = 0;
    int a[10] = {4, 6, 3, 8, 9, 3, 5, 2, 7, 0};
    bubble_sort_flag(a, 10);

    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
