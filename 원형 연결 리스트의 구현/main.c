// 원형 연결 리스트는 헤드포인터가 마지막 노드를 가리키게끔 구성하면 리스트의
// 처음이나 마지막에 노드를 삽입하는 연산이 단순 연결 리스트에 비하여 용이
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;


// phead : 리스트의 헤드 포인터의 포인터
// p     : 선행노드
// node  : 삽입될 노드
void insert_first(ListNode **phead, ListNode *node) // 리스트의 처음에 삽입
{
    if(*phead == NULL) // 빈 리스트에 삽입하기
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

// phead : 리스트의 헤드 포인터의 포인터
// p     :
void insert_last(ListNode **phead, ListNode *node) // 리스트의 끝에 삽입
{
    if(*phead == NULL) // 빈 리스트에 삽입하기
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

