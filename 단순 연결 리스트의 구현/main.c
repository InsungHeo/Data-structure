#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

// phead       : 헤드 포인터에 대한 포인터
// p           : 삽입될 위치의 선행 노드를 가리키는 포인터, 이 노드 다음에 삽입된다.
// new_node    : 새로운 노드를 가리키는 포인터
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
    if(*phead == NULL) // 공백리스트의 경우
    {
        new_node->link = NULL;
        *phead = new_node;
    }
    else if(p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
    {
        new_node->link = *phead;
        *phead = new_node;
    }
    else //p 다음에 삽입
    {
        new_node->link = p->link;
        p->link = new_node;
    }
}

// phead       : 헤드 포인터에 대한 포인터
// p           : 삭제될 노드의 선행 노드를 가리키는 포인터, 이 노드 다음이 삭제된다.
// removed     : 삭제될 노드를 가리키는 포인터
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
    if(p == NULL) // 연결 리스트의 첫 번째 노드를 삭제
        *phead = (*phead)->link;
    else
        p->link = removed->link;
    free(removed);
}

// 방문 연산 코드
void display(ListNode *head) // 반복 버전
{
    ListNode *p = head;
    while(p != NULL)
    {
        printf("%d->", p->data);
        p = p->link;
    }
    printf("\n");
}
void display_recur(ListNode *head) // 순환 버전
{
    ListNode *p = head;
    if(p != NULL)
    {
        printf("%d->", p->data);
        display_recur(p->link);
    }
}

// 탐색 연산 : 특정한 데이터 값을 갖는 노드를 찾는 연산
ListNode *search(ListNode *head, int x)
{
    ListNode *p = head;
    while(p != NULL)
        if(p->data = x)
            return p; // 탐색 성공, node를 가리키는 포인터 반환
    return p; // 탐색 실패 시 NULL 반환
}

// 합병 연산 : 2개의 리스트를 합치는 연산
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

// 역순 연산 : 리스트의 노드들을 역순으로 만드는 연산
ListNode *reverse(ListNode *head)
{
    // 순회 포인터로 p, q, r을 사용
    ListNode *p, *q, *r;
    p = head; // p는 역순으로 만들 리스트
    q = NULL; // q는 역순으로 만들 노드
    while(p != NULL)
    {
        // r은 q, q는 p를 차례대로 따라간다.
        r = q;
        q = p;
        p = p->link;
        // q의 링크 방향을 바꾼다.
        q->link = r;
    }
    return q;
}
int main()
{
    // 헤드포인터(head pointer) : 연결 리스트의 맨 처음 노드를 가리키는 포인터
    // 노드의 생성 : 동적 메모리 생성 라이브러리 malloc 함수 이용
    ListNode *p1;
    p1 = (ListNode *)malloc(sizeof(ListNode));
    p1->data = 10;
    p1->link = NULL;

    // 두 번째 노드 생성과 첫 번쨰 노드와의 연결
    ListNode *p2;
    p2 = (ListNode *)malloc(sizeof(ListNode));
    p2->data = 20;
    p2->link = NULL;
    p1->link = p2;

    // 두 번째 노드 생성과 첫 번쨰 노드와의 연결
    ListNode *p3;
    p3 = (ListNode *)malloc(sizeof(ListNode));
    p3->data = 30;
    p3->link = NULL;
    p2->link = p3;

// 여기다가 연습 많이 해보자

    display_recur(p1);
    ListNode *q = reverse(p1);
    display_recur(q);
    return 0;
}
