/* Bit Count
 * Date   : 2018-09-19
 * Author : H.Yin
 * Email  : csustyinhao@gmail.com
*/

#include <stdio.h>
#include <sys/time.h>
/* 简单循环法 */
unsigned int bit_count_1(unsigned int n)
{
    unsigned int c = 0;
    while(n)
    {
        if(n & 1)
        {
            c++;
        }
        n = n >> 1; // 循环右移
    }
    return c;
}
/* 末位 1 取反法 */
unsigned int bit_count_2(unsigned int n)
{
    unsigned int c = 0;
    while(n)
    {
        n = n & (n - 1); // 末位 1 取反
        c++;
    }
    return c;
}

/* 查表法 */
unsigned int bit_count_3(unsigned int n)
{
    unsigned int bitTabel[] = {
        0, 1, 1, 2,
        1, 2, 2, 3,
        1, 2, 2, 3,
        2, 3, 3, 4
    }, c = 0;
    // 查表
    c = bitTabel[ n & 0x0000000f]
        + bitTabel[(n >> 4) & 0x0000000f]
        + bitTabel[(n >> 8) & 0x0000000f]
        + bitTabel[(n >> 12) & 0x0000000f]
        + bitTabel[(n >> 16) & 0x0000000f]
        + bitTabel[(n >> 20) & 0x0000000f]
        + bitTabel[(n >> 24) & 0x0000000f];
    
    return c;
}

/* 位标志法 */
#pragma  pack(push,1)
struct byte_t{
    unsigned bit_1:1;
    unsigned bit_2:1;
    unsigned bit_3:1;
    unsigned bit_4:1;
    unsigned bit_5:1;
    unsigned bit_6:1;
    unsigned bit_7:1;
    unsigned bit_8:1;
};
#pragma pack(pop)

unsigned int bit_count_4(unsigned int n)
{
    unsigned int c = 0, i = 0;
    struct byte_t *byte = (struct byte_t *)&n;
    for(i = 0; i < sizeof(unsigned); i++){
        c += byte->bit_1 
            + byte->bit_2 
            + byte->bit_3 
            + byte->bit_4 
            + byte->bit_5 
            + byte->bit_6 
            + byte->bit_7
            + byte->bit_8;
        byte++;
    }
    return c;
}

/* 并行计算法 */
unsigned int bit_count_5(unsigned int n)
{
    // 并行计算
    n = (n & 0x55555555) + (n >> 1 & 0x55555555);
    n = (n & 0x33333333) + (n >> 2 & 0x33333333);
    n = (n & 0x0f0f0f0f) + (n >> 4 & 0x0f0f0f0f);
    return n % 255;
}

/* 3-bits */
unsigned int bit_count_6(unsigned int n)
{
    unsigned int tmp = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
    return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}
/* 4-bits */
unsigned int bit_count_7(unsigned int n)
{
    unsigned int tmp = n - (n >> 1 & 0x77777777) - (n >> 2 & 0x33333333) - (n >> 3 & 0x11111111);
    return ((tmp + (tmp >> 4)) & 0x0f0f0f0f) % 255;
}

int main()
{
    int i = 0;
    struct timeval start, end;
    printf("%d\n",bit_count_5(0x1ff12ee2));
    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_1(i);
    }
    gettimeofday(&end, NULL);
    printf("1---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));

    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_2(i);
    }
    gettimeofday(&end, NULL);
    printf("2---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));
    
    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_3(i);
    }
    gettimeofday(&end, NULL);
    printf("3---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));
    
    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_4(i);
    }
    gettimeofday(&end, NULL);
    printf("4---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));
    
    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_5(i);
    }
    gettimeofday(&end, NULL);
    printf("5---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));
    
    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_6(i);
    }
    gettimeofday(&end, NULL);
    printf("6---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));

    gettimeofday(&start, NULL);
    for(i = 0; i < 10000000; i++){
        bit_count_7(i);
    }
    gettimeofday(&end, NULL);
    printf("7---Time: %ld us\n", end.tv_sec * 1000000 + end.tv_usec - (start.tv_sec * 1000000 + start.tv_usec));

    return 0;
}