/* Hash Tree
 * Date   : 2018-09-16
 * Author : H.Yin
 * Email  : csustyinhao@gmail.com
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 质数序列
const int PNS[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

typedef struct Data{
    long long key;    // 关键字
    void * val;       // 其他信息
}NodeData;

// 树的节点
typedef struct Node{
    int flag;         // 占位标记：0-> 未占用；1-> 占用中；-1-> 根节点
    int d;            // 树深，每一层对应一个质数。根节点为0;
    NodeData *data;   // 记录
    struct Node **childs; // 子节点数组 *用二维数组便于遍历与内存回收！
}TreeNode;

typedef struct Tree{
    TreeNode *root; // 树根
    //double ASL;   // 统计信息;
    //int count;
}HashTree;

TreeNode **createChilds(d){
    int i=0;
    TreeNode **childs = (TreeNode **)malloc(PNS[d] * sizeof(TreeNode*));
    if(childs == NULL){
        return NULL;
    }
    for(i =0; i < PNS[d]; i++){
        childs[i] = (TreeNode *)malloc(sizeof(TreeNode));
        if(childs[i] == NULL){
            return NULL;
        }
        childs[i]->flag = 0;
        childs[i]->d = d+1;
        childs[i]->data = NULL;
        childs[i]->childs = NULL;
    }
    return childs;
}

// 初始化 Hash 树
HashTree * init(){
    HashTree * ht = (HashTree *)malloc(sizeof(HashTree));
    if(ht == NULL){
        return NULL;
    }
    // 初始化根节点
    TreeNode * node = (TreeNode *)malloc(sizeof(TreeNode));
    if(node == NULL){
        return NULL;
    }
    node->flag = -1;
    node->d = 0;
    node->data = NULL;
    node->childs = createChilds(0);
    
    ht->root = node;
    return ht;
}

// 获取指定记录信息
TreeNode *get(HashTree *ht, NodeData *data){
    TreeNode *p = ht->root, *q;
    int k = data->key % PNS[p->d];
    q = p->childs[k];
    while(p != NULL){
        // printf("--%d: %d %d\n", PNS[p->d], k, q->flag);
        if(q->flag == 1 && q->data->key == data->key){
            return q;
        }else{
            p = q;
            k = data->key % PNS[p->d];
            // 找到叶子节点则停止；
            if(p->childs == NULL){
                return NULL;
            }else{
                q = p->childs[k];
            }
        }
    }
    return NULL;
}
// 插入指定记录
int insert(HashTree *ht, NodeData *data){
    TreeNode *p = ht->root, *q;
    int k, d = 0;
    k = data->key % PNS[p->d];
    q = p->childs[k];
    while(q != NULL){
        // printf("--%d: %d %d\n", PNS[p->d], k, q->flag);
        if(q->flag == 1){
            p = q;
            k = data->key % PNS[p->d];
            q = p->childs[k];
        }else{
            break;
        }
    }
    // 插入数据
    q->data = data;
    q->flag = 1;
    // 叶子节点添加子节点
    if(q->childs == NULL){
        q->childs = createChilds(q->d);
    }
    return 0;
}

// 删除指定记录
int del(HashTree *ht, NodeData *data){
    TreeNode *node = get(ht,data);
    if(node != NULL){
        node->flag = 0;
        node->data = NULL;
        return 0;
    }
    return -1;
}

// 递归删除空间
int destroy(TreeNode *p){
    int i = 0;
    if(p == NULL){
        return 0;
    }else{
        if(p->childs != NULL){
            for(i = 0; i < PNS[p->d]; i++){
                destroy(p->childs[i]);
            }
            free(p->childs);
        }
        free(p);
        p = NULL;
    }
    return 0;
}

int main(){
    /* test */
    int op, key;
    NodeData *data = NULL;
    TreeNode *x ;
    HashTree *ht = init();
    if(ht == NULL){
        return -1;
    }
    printf("1) Get; 2) Insert; 3) Delete; else) exit\n");
    while(1){
        scanf("%d %d", &op, &key);
        data = (NodeData *)malloc(sizeof(NodeData));
        data->key = key;
        switch(op){
            case 1:
                x = get(ht, data);
                if( x == NULL){
                    printf("%d not exist.\n", key);
                }else{
                    printf("Depth:%d\tFlag:%d\tkey:%lld\n", x->d, x->flag, x->data->key);
                }
                break;
            case 2:
                insert(ht, data);
                break;
            case 3:
                del(ht, data);
                break;
            default:
                destroy(ht->root);
                return 0;
        }
    }
    return 0;
}