/* Edit Distance
 * Date   : 2018-09-19
 * Author : H.Yin
 * Email  : csustyinhao@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ABS(a) ((a)>=0 ? (a):-(a))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int HammingDistance(const char *A, const char* B){
    int res = 0;
    while(*A && *B){
        if(*A++ != *B++){
            res += 1;
        }
    }
    return res;
}

int LeeDistance(const char *A, const char* B, int q){
    int res = 0, abs;
    while(*A && *B){
        abs = ABS(*A - *B);
        res += MIN(abs, q-abs);
        A++; // 不能放到 ABS 中
        B++;
    }
    return res;
}

int LCSDistance(const char *A, const char* B){
    int res = 0;
    int **d=NULL, i = 0, j=0;
    int lenA = strlen(A), lenB = strlen(B);
    if(lenA == 0 || lenB == 0) return 0;

    // 建立二维数组并初初始化
    d = (int**)malloc((lenA+1)*sizeof(int*));
    if(d == NULL){
        return -1;
    }
    
    for(i=0; i<=lenA; i++){
        d[i] = (int*)malloc((lenB+1)*sizeof(int));
        for(j=0; j<=lenB; j++){
            if(i == 0 || j ==0){
                d[i][j] = 0;
            }else if (A[i] == B[j]){
                d[i][j] = d[i-1][j-1] + 1;
            }else{
                d[i][j] = MAX(d[i-1][j], d[i][j-1]);
            }
        }
    }
    return lenA + lenB - 2*d[lenA][lenB];
}

double JaroDistance(const char *A, const char* B){
    int i = 0, j=0, c=0, t=0, mw=0;
    int m = strlen(A), n = strlen(B);
    mw = MAX(m, n) / 2 -1;
    
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            // 统计 c 
            if(A[i] == B[j] && ABS(i-j) <= mw){
                c += 1;
            }
            // 统计 t
            if(i>0 && j>0 && A[i-1]==B[j] && A[j] == B[j-1]){
                t += 1;
            }
        }
    }
    if(c == 0){
        return 0.0;
    }
    
    return 1-1.0 / 3 * (c *1.0/m + c*1.0/n + (c-t)*1.0/c);
}

double JaroWinklerDistance(const char *A, const char* B, double p){
    int i = 0, j=0, c=0, t=0, l=0, mw=0;
    int m = strlen(A), n = strlen(B);
    double sj = 0.0;
    mw = MAX(m, n) / 2 -1;
    p = p > 0.25? 0.25: p;
    // 统计 l
    for(i=0; i<MIN(m, n); i++){
        if(A[i] == B[i]){
            l += 1;
        }
    }
    
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            // 统计 c 
            if(A[i] == B[j] && ABS(i-j) <= mw){
                c += 1;
            }
            // 统计 t
            if(i>0 && j>0 && A[i-1]==B[j] && A[j] == B[j-1]){
                t += 1;
            }
        }
    }
    
    if(c != 0){
        sj = 1.0 / 3 * (c *1.0/m + c*1.0/n + (c-t)*1.0/c);
    }
    
    return 1- (sj + l*p*(1-sj));
}

int LevDistance_Recursive(const char *A, int lenA, const char* B, int lenB){
    int cost;
    if(lenA == 0) return lenB;
    if(lenB == 0) return lenA;

    cost = (A[lenA-1] == B[lenB-1]) ? 0: 1;
    
    return MIN(MIN(LevDistance_Recursive(A, lenA-1, B, lenB),
                LevDistance_Recursive(A, lenA, B, lenB-1)
                )+1,
            LevDistance_Recursive(A, lenA-1, B, lenB-1)+cost);
}

int LevDistance_dp1(const char *A, const char* B){
    int **d=NULL, i = 0, j=0;
    int cost = 0;
    int lenA = strlen(A), lenB = strlen(B);
    if(lenA == 0) return lenB;
    if(lenB == 0) return lenA;
    // 建立二维数组并初初始化
    d = (int**)malloc((lenA+1)*sizeof(int*));
    if(d == NULL){
        return -1;
    }
    d[0] = (int*)malloc((lenB+1)*sizeof(int));
    // 初始化上边界
    for(j=0; j<=lenB; j++) d[0][j] = j;
    
    // 初始化左边界
    for(i=1; i<=lenA; i++){
        d[i] = (int*)malloc((lenB+1)*sizeof(int));
        d[i][0] = i;
    }

    for(i=1; i<=lenA; i++){
        for(j=1; j<=lenB; j++){
            cost = (A[i-1] == B[j-1]) ? 0 : 1;
            d[i][j] = MIN(MIN(d[i-1][j], d[i][j-1])+1, d[i-1][j-1]+cost);
        }
    }
    return d[lenA][lenB];
}

int LevDistance_dp2(const char *A, const char* B){
    int *v0=NULL, *v1=NULL, *temp; // 上一行与当前行
    int i = 0, j=0, cost = 0;
    
    int lenA = strlen(A), lenB = strlen(B);
    // 提前返回
    if(lenA == 0) return lenB;
    if(lenB == 0) return lenA;
    
    // 建立两个数组并初初始化
    v0 = (int*)malloc((lenB+1)*sizeof(int));
    v1 = (int*)malloc((lenB+1)*sizeof(int));
    if(v0 == NULL || v1 == NULL){
        return -1;
    }
    
    // 初始化上边界
    for(j=0; j<=lenB; j++) v0[j] = j;
    
    for(i=1; i<=lenA; i++){
        v1[0] = i;
        for(j=1; j<=lenB; j++){
            cost = (A[i-1] == B[j-1]) ? 0 : 1;
            v1[j] = MIN(MIN(v0[j], v1[j-1])+1, v0[j-1]+cost);
        }
        // 交换上下层
        temp = v1; v1 = v0; v0 = temp;
    }
    return v0[lenB];
}

int DamDistance_Restricted (const char *A, const char* B){
    int **d=NULL, i = 0, j=0;
    int cost = 0;
    int lenA = strlen(A), lenB = strlen(B);
    if(lenA == 0) return lenB;
    if(lenB == 0) return lenA;
    // 建立二维数组并初初始化
    d = (int**)malloc((lenA+1)*sizeof(int*));
    if(d == NULL){
        return -1;
    }
    d[0] = (int*)malloc((lenB+1)*sizeof(int));
    // 初始化左边界
    for(i=1; i<=lenA; i++){
        d[i] = (int*)malloc((lenB+1)*sizeof(int));
        d[i][0] = i;
    }
    // 初始化上边界
    for(j=0; j<=lenB; j++) d[0][j] = j;
    
    for(i=1; i<=lenA; i++){
        for(j=1; j<=lenB; j++){
            cost = (A[i-1] == B[j-1]) ? 0 : 1;
            d[i][j] = MIN(MIN(d[i-1][j], d[i][j-1])+1, d[i-1][j-1]+cost);
            // 交换的情况
            if(i>1 && j>1 && A[i-2]==B[j-1] && A[j-1] == B[j-2]){
                d[i][j] = MIN(d[i][j], d[i-2][j-2]+1);
            }
        }
    }
    return d[lenA][lenB];
}

int DamDistance_Unrestricted (const char *A, const char* B){
    int **d=NULL, **q, i = 0, j=0, l, k;
    int cost = 0;
    int lenA = strlen(A), lenB = strlen(B) , lenS;
    int da[128] = {}, db = 0;
    
    if(lenA == 0) return lenB;
    if(lenB == 0) return lenA;
    
    memset(da, 0, 128*sizeof(int));
    
    lenS = lenA + lenB;
    // 建立二维数组并初初始化
    d = (int**)malloc((lenA+2)*sizeof(int*));
    if(d == NULL){
        return -1;
    }
    // 初始化左边界
    for(i=0; i<=lenA+1; i++){
        d[i] = (int*)malloc((lenB+2)*sizeof(int));
        d[i][0] = lenS;
        d[i][1] = i;
    }
    // 初始化上边界
    for(j=0; j<=lenB+1; j++){
        d[0][j] = lenS;
        d[1][j] = j;
    }
    q = &(d[1]);
    for(i=1; i<=lenA; i++){
        db = 0;
        for(j=1; j<=lenB; j++){
            k = da[B[j-1]];
            l = db;
            if(A[i-1] == B[j-1]){
                cost = 0;
                db = j;
            }else{
                cost = 1;
            }
            
            q[i][j] = MIN(q[i-1][j], q[i][j-1])+1;
            q[i][j] = MIN(q[i][j], q[i-1][j-1]+cost);
            q[i][j] = MIN(q[i][j], q[k-1][l-1]+(i-k-1)+1+(j-l-1)); // TODO:????
        }
        da[A[i-1]] = i;
    }
    return q[lenA][lenB];
}

int main(){
    char *A = "ab";
    char *B = "dc";
    // printf("%d\n", HammingDistance("10001", "10010"));
    // printf("%d\n", LeeDistance("10001", "10010", 2));
    //printf("%d\n", LCSDistance("ABCBDAB", "BDCABA"));
    // printf("%f\n",JaroDistance("DIXON", "DICKSONS"));
    // printf("%f\n",JaroWinklerDistance("DIXON", "DICKSONS", 0.1));
    
    //printf("%d\n", LevDistance_Recursive("1011101", 7, "1001011", 7));
    // printf("%d\n", LevDistance_dp1("ab", "ba"));
    // printf("%d\n", LevDistance_dp2("ab", "ba"));
    
    printf("%d\n", DamDistance_Restricted("cadb", "abcd"));
    printf("%d\n", DamDistance_Unrestricted("cadb", "abcd"));
}