/*******************************************************************
*  File        : sqrt_n.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-06-17 17:06:49(+0800)
*  Modified    : 2019-06-18 15:58:18(+0800)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action.git
*  Description : implement sqrt(n) without math.h
*******************************************************************/

#include<stdio.h>
#include<math.h>

#define abs(x) ((x)>0?(x):-(x))

double sqrt_bisection(double n){
    double low = 0, high= 1 + n / 2.0, mid, x;
    if(n < 0){
        return -1;
    }
    while(high - low >= 1e-10){
        mid = (low + high) / 2.0;
        x = mid * mid;
        if(x == n){
            return mid;
        }else if (x < n){
            low = mid;
        }else{
            high = mid;
        }
    }
    mid = (low + high) / 2.0;
    return mid;
}

double sqrt_newton(double n){
    double xj = 0, xi = 1 + n / 2.0;
    if(n < 0) return -1;
    if(n == 0) return 0;
    while(1){
        xj = (xi + n / xi) / 2.0;
        if(abs(xj - xi) < 1e-10){
            break;
        }
        xi = xj;
    }
    return xj;
}

int main(){
    int i =0;
    for(i=0; i<=100; i++){
        printf("%.10f\n", sqrt_newton(i));
    }
    return 0;
}
