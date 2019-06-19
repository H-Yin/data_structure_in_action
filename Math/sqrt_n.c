/*******************************************************************
*  File        : sqrt_n.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-06-17 17:06:49(+0800)
*  Modified    : 2019-06-19 19:54:24(+0800)
*  GitHub      : https://github.com/H-Yin/data_structure_in_action.git
*  Description : implement sqrt(n) without math.h
*******************************************************************/

#include<stdio.h>
#include<math.h>

double sqrt_bisection(double n){
    double low = 0, high= (1 + n) / 2.0, mid, x;
    int i = 0;
    if(n < 0){
        return -1;
    }
    /*TODO : fix bug when 1e-10   */
    while(high - low >= 1e-6){
        mid = (low + high) / 2.0;
        x = mid * mid;
        if(x == n){
            return mid;
        }else if (x < n){
            low = mid;
        }else{
            high = mid;
        }
        i++;
    }
    mid = (low + high) / 2.0;
    return mid;
}

double sqrt_newton(double n){
    int i=0;
    double xj = 0, xi = (1 + n) / 2.0;
    if(n < 0) return -1;
    if(n == 0) return 0;
    while(1){
        xj = (xi + n / xi) / 2.0;
        if(xi - xj < 1e-6){
            break;
        }
        xi = xj;
        i++;
    }
    return xj;
}

int main(){
    double i = 31e10, a, b, c;
    for(i; i<=31e10; i+=1){
        /* a = sqrt(i); */
        b = sqrt_bisection(i);
        printf("%.10lf\n", b);
        /* c = sqrt_newton(i); */
        /* if(a != b) */
            /* printf("1:%.10f\t%.10lf\n", a, b); */
        /* if(a != c) */
            /* printf("2:%.10f\t%.10lf\n", a, c); */
    }
    return 0;
}
