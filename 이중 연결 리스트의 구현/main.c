#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode
{
    element data;
    struct DlistNode *llink; //  left link
    struct DlistNode *rlink; // right link
} DlistNode;
// ��� new_node�� ��� before�� �����ʿ� �����Ѵ�.
void dinsert_node(DlistNode *before, DlistNode *new_node)
{
    new_node->llink = before;
    new_node->rlink = before->rlink;
    before->rlink->llink = new_node;
    before->rlink = new_node;
}

// ��� removed�� �����Ѵ�.
void dremove_node(DlistNode *phead_node, DlistNode *removed)
{
    if(removed == phead_node)
        return *phead_node; //�̰� �³�
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    free(removed);
}
int main()
{
    printf("���� ���� ����Ʈ�� ����, ����\n");
    return 0;
}
