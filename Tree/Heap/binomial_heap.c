/*******************************************************************
*  File        : binomial_heap.c
*  Author      : H.Yin
*  Email       : csustyinhao@gmail.com
*  Created     : 2019-01-07 16:19:52(+0000)
*  Modified    : 2019-01-07 16:21:49(+0000)
*  GitHub      : https://github.com/H-Yin/
*  Description : binomial heap
*******************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Node Definition
typedef struct _Node{
    int   key;              // 关键字
    int degree;             // 度数
    struct _Node *child;    // 左孩子节点
    struct _Node *parent;   // 父节点
    struct _Node *next;     // 兄弟节点
}*Node;

// Binomial Heap Definition
typedef struct _BinomialHeap{
    Node head;     // 头节点
    int size;       // 节点数量
}*BinomialHeap;

#define NODE_BYTES sizeof(struct _Node)
#define HEAP_BYTES sizeof(struct _BinomialHeap)

BinomialHeap binomial_heap_create();         // 创建二项堆
BinomialHeap binomial_heap_merge(BinomialHeap bh1, BinomialHeap bh2);  // 合并二项堆
int binomial_heap_destroy(BinomialHeap bh);  // 销毁二项堆
int binomial_heap_size(BinomialHeap bh);     // 获取二项堆的节点数
int binomial_heap_print_root(BinomialHeap bh);  // 输出所有二项树的根
// 节点操作
int binomial_heap_search(BinomialHeap bh, int key);   // 搜索指定关键字
int binomial_heap_insert(BinomialHeap bh, int key);   // 插入指定关键字
int binomial_heap_delete(BinomialHeap bh, int key);   // 删除指定关键字
int binomial_heap_update(BinomialHeap bh, int key, int data);  // 更新指定关键字
int binomial_heap_top(BinomialHeap bh);         // 获取堆的最小值
int binomial_heap_get(BinomialHeap bh);         // 获取并删除堆的最小值
int binomial_heap_degree(BinomialHeap bh, int key);  // 获取指定节点的度

BinomialHeap binomial_heap_create(){
    BinomialHeap bh;
    bh = (BinomialHeap)malloc(HEAP_BYTES);
    if( bh == NULL){
        printf("memory allocation failed!");
        exit(-1);
    }
    bh->head = (Node)malloc(NODE_BYTES);
    bh->head->next = NULL;
    bh->size = 0;
    return bh;
}

Node _binomial_heap_node_create(int data){
    Node node = (Node)malloc(NODE_BYTES);
    if( node == NULL){
        printf("memory allocation failed!");
        exit(-1);
    }
    
    node->child = NULL;
    node->next = NULL;
    node->parent = NULL;
    node->degree = 0;
    node->key = data;
    
    return node;
}

BinomialHeap binomial_heap_merge(BinomialHeap bh1, BinomialHeap bh2){
    assert(bh1 != NULL);
    assert(bh2 != NULL);
    printf("=======================\n");
    binomial_heap_print_root(bh1);
    binomial_heap_print_root(bh2);
    
    
    Node new_head = _binomial_heap_node_create(-1);
    Node tail = new_head;
    Node head1 = bh1->head->next, head2 = bh2->head->next;
    Node p = head1, q=head2, r = NULL;
    // merge root list
    while(head1 != NULL && head2 != NULL){
        p = head1, q=head2;
        if(p->degree == q->degree){
            head1 = head1->next;
            head2 = head2->next;
            if(p->key > q->key){
                tail->next = p;
                p->next = q;
                tail = q;
            }else{
                tail->next = q;
                q->next = p;
                tail = p;
            }
        }else if(p->degree < q->degree){
            head1 = head1->next;
            tail->next = p;
            tail = p;
        }else{
            head2 = head2->next;
            tail->next = q;
            tail = q;
        }
    }
    
    if(head1 == NULL && head2 != NULL){
        tail->next = head2;
    }
    
    if(head1 != NULL && head2 == NULL){
        tail->next = head1;
    }
    
    bh1->head->next = new_head->next;
    binomial_heap_print_root(bh1);
    printf("-----------------------\n");
    // Adjust Binomial tree
    tail = new_head;
    p = new_head -> next; //???
    q = p->next;
    while(p != NULL && q != NULL){
        if(p->degree == q->degree){
            printf("degree: %d:%d %d:%d\n", p->key, p->degree, q->key, q->degree);
            r = q->next;
            if(r == NULL || (r != NULL && r->degree != q->degree)){
                if(p->key < q->key){
                    printf("\t12312\n");
                    p->next =  q->next;
                    q->parent = p;
                    q->next = p->child;
                    p->child = q;
                    
                    q = p;
                }else{
                    printf("\tajsdha\n");
                    p->parent = q;
                    p->next = q->child;
                    q->child = p;
                }
                q->degree += 1;
            }
        }
        tail->next = q;
        tail = tail->next;
        p = q;
        q = q->next;
    }
    binomial_heap_print_root(bh1);
    printf("-----------------------\n");
    
    return bh1;
}

int binomial_heap_insert(BinomialHeap bh, int key){
    Node node = _binomial_heap_node_create(key);
    BinomialHeap new_bh = binomial_heap_create();
    new_bh->head->next = node;
    
    binomial_heap_merge(bh, new_bh);
    
    return 0;
}




int binomial_heap_size(BinomialHeap bh){
    return bh->size;
}

int binomial_heap_print_root(BinomialHeap bh){
    assert(bh != NULL);
    
    Node p = bh->head->next;
    while(p != NULL){
        printf("%d->", p->key);
        p = p->next;
    }
    printf("NULL\n");
    
    return 0;
}

int main(){
    BinomialHeap bh = binomial_heap_create();
    binomial_heap_insert(bh, 6);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 23);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 9);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 31);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 18);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 25);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 20);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 42);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 11);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 48);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 24);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 52);
    // binomial_heap_print_root(bh);
    binomial_heap_insert(bh, 13);
    // binomial_heap_print_root(bh);

    return 0;
}