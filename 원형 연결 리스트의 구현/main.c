// ���� ���� ����Ʈ�� ��������Ͱ� ������ ��带 ����Ű�Բ� �����ϸ� ����Ʈ��
// ó���̳� �������� ��带 �����ϴ� ������ �ܼ� ���� ����Ʈ�� ���Ͽ� ����
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;


// phead : ����Ʈ�� ��� �������� ������
// p     : ������
// node  : ���Ե� ���
void insert_first(ListNode **phead, ListNode *node) // ����Ʈ�� ó���� ����
{
    if(*phead == NULL) // �� ����Ʈ�� �����ϱ�
    {
        *phead = node;
        node->link = node;
    }
    else
    {
        node->link = (*phead)->link;
        (*phead)->link = node;
    }
}

// phead : ����Ʈ�� ��� �������� ������
// p     :
void insert_last(ListNode **phead, ListNode *node) // ����Ʈ�� ���� ����
{
    if(*phead == NULL) // �� ����Ʈ�� �����ϱ�
    {
        *phead = node;
        node->link = node;
    }
    else
    {
        node->link = (*phead)->link;
        (*phead)->link = node;
        *phead = node;
    }
}


int main()
{
    return 0;
}

