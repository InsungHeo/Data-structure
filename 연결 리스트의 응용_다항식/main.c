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


// 초기화 함수
void init(ListHeader *plist)
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

void insert_node_last(ListHeader *plist, int coef, int expon)
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    if(temp == NULL) // safe coding
       // error("메모리 할당 에러");
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
    while(a && b) // a와 b가 NULL이 아닐 때
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
    // a나 b 중에 NULL이 생겼을 때
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

// 대체 왜 안되는거지...
// insert_node_last()의 문제인데...
// temp == NULL error 처리?? 가 제대로 안됐나?
// temp->coef = coef;    temp->expon = expon; 이 두 줄의 순서만 바꾸는데 왜 출력이 이상해지지?
// 왜 expon은 제대로 되는데 coef만 제대로 안되지 순서 빼고는 expon이랑 coef랑 다를게 없는데
// coef은 잘 전달되었는데, temp->coef는 왜 이상하지
// 왜 insert_node_last()코드가 6개 있는데, system("pause")가 11번 나타나지...
