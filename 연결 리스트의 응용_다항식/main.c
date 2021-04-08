#include <stdio.h>
#include <stdlib.h>
typedef struct ListNode
{
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListHeader
{
    int length;
    ListNode *head;
    ListNode *tail;
} ListHeader;


// �ʱ�ȭ �Լ�
void init(ListHeader *plist)
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

void insert_node_last(ListHeader *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if(temp == NULL) // safe coding
       // error("�޸� �Ҵ� ����");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    printf("%d\n\n", temp->coef);
    system("pause");

    if(plist->tail == NULL)
        plist->head = plist->tail = temp;
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    plist->length++;
}

void poly_add(ListHeader *plist1, ListHeader *plist2, ListHeader *plist3)
{
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;
    int sum;
    while(a && b) // a�� b�� NULL�� �ƴ� ��
    {
        if(a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if(sum != 0)
                insert_node_last(plist3, sum, a->coef);
            a = plist1->head->link; // a = a->link
            b = plist2->head->link; // b = b->link
        }
        else if(a->expon > b->expon)
        {
            insert_node_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insert_node_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }
    // a�� b �߿� NULL�� ������ ��
    for(;a != NULL; a = a->link)
        insert_node_last(plist3, a->coef, a->expon);
    for(;b != NULL; b = b->link)
        insert_node_last(plist3, b->coef, b->expon);
}

void poly_print(ListHeader *plist)
{
    ListNode *p = plist->head;
    for(; p != NULL; p = p->link)
        printf("%d x^%d\n", p->coef, p->expon);
}

int main()
{
    ListHeader list1, list2, list3;

    init(&list1);
    init(&list2);
    init(&list3);

    insert_node_last(&list1,  1, 12);
    insert_node_last(&list1,  2,  8);
    insert_node_last(&list1,  1,  0);

    insert_node_last(&list2,  8, 12);
    insert_node_last(&list2, -3, 10);
    insert_node_last(&list2, 10,  6);

    poly_add(&list1, &list2, &list3);
    poly_print(&list3);
    return 0;
}

// ��ü �� �ȵǴ°���...
// insert_node_last()�� �����ε�...
// temp == NULL error ó��?? �� ����� �ȵƳ�?
// temp->coef = coef;    temp->expon = expon; �� �� ���� ������ �ٲٴµ� �� ����� �̻�������?
// �� expon�� ����� �Ǵµ� coef�� ����� �ȵ��� ���� ����� expon�̶� coef�� �ٸ��� ���µ�
// coef�� �� ���޵Ǿ��µ�, temp->coef�� �� �̻�����
// �� insert_node_last()�ڵ尡 6�� �ִµ�, system("pause")�� 11�� ��Ÿ����...
