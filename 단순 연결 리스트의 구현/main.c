#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

// phead       : ��� �����Ϳ� ���� ������
// p           : ���Ե� ��ġ�� ���� ��带 ����Ű�� ������, �� ��� ������ ���Եȴ�.
// new_node    : ���ο� ��带 ����Ű�� ������
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
    if(*phead == NULL) // ���鸮��Ʈ�� ���
    {
        new_node->link = NULL;
        *phead = new_node;
    }
    else if(p == NULL) // p�� NULL�̸� ù ��° ���� ����
    {
        new_node->link = *phead;
        *phead = new_node;
    }
    else //p ������ ����
    {
        new_node->link = p->link;
        p->link = new_node;
    }
}

// phead       : ��� �����Ϳ� ���� ������
// p           : ������ ����� ���� ��带 ����Ű�� ������, �� ��� ������ �����ȴ�.
// removed     : ������ ��带 ����Ű�� ������
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
    if(p == NULL) // ���� ����Ʈ�� ù ��° ��带 ����
        *phead = (*phead)->link;
      //*phead = removed->link; �̷��� �ص� �ǰ���??
    else
        p->link = removed->link;
    free(removed);
}


// �湮 ���� �ڵ�
void display(ListNode *head) // �ݺ� ����
{
    ListNode *p = head;
    while(p != NULL)
    {
        printf("%d->", p->data);
        p = p->link;
    }
    printf("\n");
}
void display_recur(ListNode *head) // ��ȯ ����
{
    ListNode *p = head;
    if(p != NULL)
    {
        printf("%d->", p->data);
        display_recur(p->link);
    }
}

// Ž�� ���� : Ư���� ������ ���� ���� ��带 ã�� ����
ListNode *search(ListNode *head, int x)
{
    ListNode *p = head;
    while(p != NULL)
        if(p->data = x)
            return p; // Ž�� ����, node�� ����Ű�� ������ ��ȯ
    return p; // Ž�� ���� �� NULL ��ȯ
}

// �պ� ���� : 2���� ����Ʈ�� ��ġ�� ����
ListNode *concat(ListNode *head1, ListNode *head2)
{
    ListNode *p;
    if(head1 == NULL)
        return head2;
    else if(head2 == NULL)
        return head1;
    else
    {
        p = head1;
        while(p->link != NULL)
            p = p->link;
        p->link = head2;
        return head1;
    }
}

// ���� ���� : ����Ʈ�� ������ �������� ����� ����
ListNode *reverse(ListNode *head)
{
    // ��ȸ �����ͷ� p, q, r�� ���
    ListNode *p, *q, *r;
    p = head; // p�� �������� ���� ����Ʈ
    q = NULL; // q�� �������� ���� ���
    while(p != NULL)
    {
        // r�� q, q�� p�� ���ʴ�� ���󰣴�.
        r = q;
        q = p;
        p = p->link;
        // q�� ��ũ ������ �ٲ۴�.
        q->link = r;
    }
    return q;
}
int main()
{
    // ���������(head pointer) : ���� ����Ʈ�� �� ó�� ��带 ����Ű�� ������
    // ����� ���� : ���� �޸� ���� ���̺귯�� malloc �Լ� �̿�
    ListNode *p1;
    p1 = (ListNode *)malloc(sizeof(ListNode));
    p1->data = 10;
    p1->link = NULL;

    // �� ��° ��� ������ ù ���� ������ ����
    ListNode *p2;
    p2 = (ListNode *)malloc(sizeof(ListNode));
    p2->data = 20;
    p2->link = NULL;
    p1->link = p2;

    // �� ��° ��� ������ ù ���� ������ ����
    ListNode *p3;
    p3 = (ListNode *)malloc(sizeof(ListNode));
    p3->data = 30;
    p3->link = NULL;
    p2->link = p3;

// ����ٰ� ���� ���� �غ���

    display_recur(p1);
    ListNode *q = reverse(p1);
    display_recur(q);
    return 0;
}
