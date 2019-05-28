/*******************************************************************
*  File        : cocktail_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-06 12:38:32(+0000)
*  Modified    : 2019-01-06 12:49:20(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : cocktail sort
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int cocktail_sort(int *a, int n){
    int i = 0, left = 0, right = n;
    int temp, flag = 0;
    while(left < right){
        flag = 1;
        // move the max to unsorted area's end
        for(i = left + 1; i < right; i++){
            if(a[i-1] > a[i]){
                temp = a[i-1];
                a[i-1] = a[i];
                a[i] = temp;
                flag = 0;
            }
        }
        right -= 1; // update right bound
        // move the min to unsorted area's begain
        for(i = right-1 ; i > left; i--){
            if(a[i-1] > a[i]){
                temp = a[i-1];
                a[i-1] = a[i];
                a[i] = temp;
                flag = 0;
            }
        }
        left += 1; // update left bound
        
        if (flag){ // early stop flag
            break;
        }
    }
}
 

int main(){
    int i = 0;
    int a[10] = {4, 6, 1, 8, 9, 3, 5, 2, 7, 10};
    cocktail_sort(a, 10);

    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
