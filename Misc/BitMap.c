#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_VAL 10
#define MASK 0x07

typedef struct BitMap{
    unsigned long long size;      // 大小
    unsigned long long capacity;  // 容量
    unsigned char *bits;          // 位数组
}BitMap;

// 初始化
BitMap* init(long long size){
    BitMap* bm = (BitMap*)malloc(sizeof(BitMap));
    unsigned long long newSize = (size / 8) + 1L;
    if(bm != NULL && newSize != 0L){
        bm->size = newSize;
        bm->capacity = 0L;
        bm->bits = (unsigned char *)malloc(newSize * sizeof(unsigned char));
        if(bm->bits != NULL){
            memset(bm->bits, 0, sizeof(bm->bits));
        }else{
            return NULL;
        }
    }
    return bm;
}
// 判断元素是否存在
int contains(BitMap* bm, unsigned long long N){
    return (bm->bits[N>>3] & (1 << (N & MASK))) > 0;
}

// 置 1
int set(BitMap* bm, unsigned long long N){
    if(contains(bm, N) == 1){
        return 0;
    }
    bm->bits[N>>3] |= 1 << (N & MASK);
    bm->capacity ++;
    return 1;
}

// 清零
int clr(BitMap* bm, unsigned long long N){
    if(contains(bm, N) == 1){
        bm->bits[N>>3] &= ~(1 << (N & MASK));
        bm->capacity --;
    }
    return 1;
}

// 释放
int destroy(BitMap *bm){
    free(bm->bits);
    free(bm);
    return 0;
}

int main(){
    long long max = 1L << 25, i=0L, op, key;
    BitMap* bm = init(max);
    if(bm == NULL){
        printf("init failed!");
    }
    srand(time(NULL));
    for(i=0; i< max; i++){
        set(bm, rand() % max);
    }
    printf("1) set; 2) clear; 3) contains; else) exit\n");
    while(1){
        scanf("%lld %lld", &op, &key);
        switch(op){
            case 1:
                if( set(bm, key) == 0){
                    
                    printf("%lld exists.\n", key);
                }else{
                    printf("Set key:%lld\n", key);
                }
                break;
            case 2:
                clr(bm, key);
                break;
            case 3:
                if(contains(bm, key)){
                    printf("%lld exists.\n", key);
                }else{
                    printf("%lld not exists.\n", key);
                }
                break;
            default:
                destroy(bm);
                return 0;
        }
    }
}