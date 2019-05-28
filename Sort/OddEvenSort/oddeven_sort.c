/*******************************************************************
*  File        : oddeven_sort.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-06 16:32:18(+0000)
*  Modified    : 2019-01-06 16:33:33(+0000)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action
*  Description : oddeven sort
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

int oddeven_sort(int *a, int n){
    int i = 0, temp, flag = 0;
    while(!flag){
        flag = 1;
        // Odd pairs: <1,2>, <3,4> ...
        for(i = 2; i < n; i += 2){
            if(a[i-1] > a[i]){
                temp = a[i-1];
                a[i-1] = a[i];
                a[i] = temp;
                flag = 0;
            }
        }
        // Even pairs: <0, 1>, <2, 3> ...
        for(i = 1; i < n; i += 2){
            if(a[i-1] > a[i]){
                temp = a[i-1];
                a[i-1] = a[i];
                a[i] = temp;
                flag = 0;
            }
        }
    }
}
 

int main(){
    int i = 0;
    int a[10] = {4, 0, 1, 8, 9, 3, 5, 2, 7, 11};
    oddeven_sort(a, 10);

    for(i = 0; i < 10; i++){
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}

