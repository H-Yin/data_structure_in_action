#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_tp(char *t, char*p, int i, int j, int len1, int len2){
    printf("i=%d, j=%d\n", i, j);
    for(int s=0; s<len1; s++){
        if (s == i){
            printf("|%c| ", t[s]);
        }else{
            printf("%c ", t[s]);
        };
    }
    printf("\n");
    for(int s=0; (j < 0 && s<i) || (j>=0 && s<i-j);s++){
        printf("  ");
    }
    for(int s=0; s<len2; s++){
        if (s == j){
            printf("|%c| ", p[s]);
        }else{
            printf("%c ", p[s]);
        };
    }
    printf("\n");
}

int* get_next(char *p, int len){
    int i=0, j=-1, t=0, temp;
    int * next = (int *)malloc(sizeof(int) * len);
    next[0] = -1;
    /*
    while(i < len-1){
        if (j ==-1 || p[i] == p[j]){
            i++;
            j++;
            
            if (p[i] == p[j]){
                next[i] = next[j];
            }else{
                next[i] = j;
            }
        }
        else{
            j = next[j];
        }
        //print_tp(p, p, i, j, len, len);
        //for(int t=0; t<len;t++){
        //    printf("%d ", next[t]);
        //}
        //printf("\n");
    }
    */
    while(i < len-1){
        while (j > -1 && p[i] != p[j]){
            j = next[j];
            print_tp(p, p, i, j, len, len);
        }
        i += 1;
        j += 1;
        if (p[i] == p[j]){
            next[i] = next[j];
        }else{
            next[i] = j;
        }
        print_tp(p, p, i, j, len, len);
        for(int t=0; t<len;t++){
            printf("%d ", next[t]);
        }
        printf("\n");
    }
    
    return next;
}

int kmp(char * t, char * p){
    int i=0, j=0;
    printf("%d, %d\n", strlen(t), strlen(p));
    int *next = get_next(p, strlen(p));
    while((i < strlen(t)) && (j < 0 || j < strlen(p))){
        if(j == -1 || t[i] == p[j]){
            i++;
            j++;
        }else{
            j = next[j];
        }
        
        print_tp(t, p, i, j, strlen(t), strlen(p));
        for(int t=0; t<strlen(p);t++){
            printf("%d ", next[t]);
        }
        printf("\n");
        
    }
    free(next);
    if(j>0 && j == strlen(p))
        return i-j;
    else
        return -1;
}

int main(){
    char t[] = "babcbabcabcaabcabcabcacabc";
    char p[] = "ababc";
    int si = kmp(t, p);
    printf("%d", si);
    return 0;
}
