#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode
{
    element data;
    struct DlistNode *llink; //  left link
    struct DlistNode *rlink; // right link
} DlistNode;
// 노드 new_node를 노드 before의 오른쪽에 삽입한다.
void dinsert_node(DlistNode *before, DlistNode *new_node)
{
    new_node->llink = before;
    new_node->rlink = before->rlink;
    before->rlink->llink = new_node;
    before->rlink = new_node;
}

// 노드 removed를 삭재한다.
void dremove_node(DlistNode *phead_node, DlistNode *removed)
{
    if(removed == phead_node)
        return *phead_node; //이게 맞나
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}
int main()
{
    printf("이중 연결 리스트의 삽입, 삭제\n");
    return 0;
}
