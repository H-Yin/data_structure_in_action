#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* get_next(char *p, int len){
    int i=0, j=-1, t=0, temp;
    int *next = (int *)malloc(sizeof(int) * len);
    next[0] = -1;
    /*
    while(i < len-1){
        if (j ==-1 || p[i] == p[j]){
            i++;
            j++;
            if(p[i] == p[j]){
                next[i] == next[j];
            }
            else{
                next[i] = j;
            }
        }
        else{
            j = next[j];
        }
    }
    */
    while(i < len-1){
        while (j > -1 && p[i] != p[j]){
            j = next[j];
        }
        i += 1;
        j += 1;
        if (p[i] == p[j]){
            next[i] = next[j];
        }
        else{
            next[i] = j;
        }
    }
    for(int i=0; i<len;i++){
        printf("%d ", next[i]);
    }
    printf("\n");
    
    return next;
}

int kmp(char * t, char * p){
    int i=0, j=0;
    int *next = get_next(p, strlen(p));
    while((i < strlen(t)) && (j < 0 || j < strlen(p))){
        if(j == -1 || t[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
    }
    free(next);
    if(j>0 && j == strlen(p))
        return i-j;
    else
        return -1;
}

int main(){
    char t[] = "bababcabcaabcabcabcacabc";
    char p[] = "ababc";
    int index = kmp(t, p);
    printf("%d\n", index);
    return 0;
}
