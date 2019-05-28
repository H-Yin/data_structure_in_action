/*******************************************************************
*  File        : binary_insertion_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-06 12:38:32(+0000)
*  Modified    : 2019-01-06 12:49:20(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : binary insertion sort
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int binary_insertion_sort(int *a, int n){
    int temp;
    int i = 0, j = 0;
    int low, high, mid;
    for(i = 1; i < n ;i++){
        // binary search
        temp = a[i]; // search key
        low = 0, high = i-1;
        while(low <= high){
            mid = (low + high) / 2;
            if(temp < a[mid]){  // keep stable
                high = mid -1;
            }else{
                low = mid + 1;
            }
        }
        // move to next
        for(j = i; j > high+1; j--){
            a[j] = a[j-1];
        }
        a[high+1] = temp;
    }
}

int main(){
    int i = 0;
    int a[10] = {4, 6, 3, 8, 9, 3, 5, 2, 7, 0};
    binary_insertion_sort(a, 10);

    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
