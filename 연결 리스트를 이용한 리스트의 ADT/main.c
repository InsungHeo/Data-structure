#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode
{
    element data;
    struct ListNode *link;
} ListNode;

typedef struct
{
    ListNode *head;
    int length;
} ListType;


int is_empty(ListType *list)
{
    if(list->head == NULL)
        return 1;
    else
        return 0;
}

int get_length(ListType *list)
{
    return list->length;
}

// 리스트 안에서 pos 위치의 노드를 반환한다
ListNode *get_node_at(ListType *list, int pos)
{
    ListNode *tmp_node = list->head;
    if(pos < 0)
        return NULL;
    for(int i = 0; i < pos; i++)
        tmp_node = tmp_node->link;
    return tmp_node;
}

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

// 주어진 위치에 데이터를 삽입한다
void add(ListType *list, int position, element data)
{
    ListNode *p;
    if((position >= 0) && (position <= list->length))
    {
        ListNode *node = (ListNode*)malloc(sizeof(ListNode));
        if(node == NULL)
//            error("메모리 할당에러");
        node->data = data;
        p = get_node_at(list, position-1);
        insert_node(&(list->head), p, node);
        list->length++;
    }
}

// 리스트의 끝에 데이터를 삽입한다
void add_last(ListType *list, element data)
{
    add(list, get_length(list), data);
}

// 리스트의 처음에 데이터를 삽입한다
void add_first(ListType *list, element data)
{
    add(list, 0, data);
}

// phead       : 헤드 포인터에 대한 포인터
// p           : 삭제될 노드의 선행 노드를 가리키는 포인터, 이 노드 다음이 삭제된다.
// removed     : 삭제될 노드를 가리키는 포인터
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
    if(p == NULL) // 연결 리스트의 첫 번째 노드를 삭제
        *phead = (*phead)->link;
      //*phead = removed->link; 이렇게 해도 되겠지??
    else
        p->link = removed->link;
    free(removed);
}

// 주어진 위치의 데이터를 삭제한다
void delete(ListType *list, int pos)
{
    if(!is_empty(list) && (pos >= 0) && (pos < list->length))
    {
        ListNode *p = get_node_at(list, pos-1);
        ListNode *removed = get_node_at(list, pos);
        remove_node(&(list->head), p, removed);
        list->length--;
    }
}

// 위치 pos에 해당하는 데이터를 반환하는 연산
element get_entry(ListType *list, int pos)
{
    ListNode *p;
    if(pos >= list->length)
//        error("위치 오류");
    p = get_node_at(list, pos);
    return p->data;
}

void clear(ListType *list, int pos)
{
    for(int i = 0; i < list->length; i++)
        delete(list, i);
}

//버퍼의 내용을 출력한다
void display(ListType *list)
{
    ListNode *node = list->head;
    for(int i = 0; i < list->length; i++)
    {
        printf("%d", node->data);
        node = node->link;
    }
    printf("\n");
}

// 데이터 값이 s인 노드를 찾는다
int is_in_list(ListType *list, element item)
{
    ListNode *p;
    p = list->head;
    while(p != NULL)
    {
        if(p->data == item)
            break;
        p = p->link;
    }
    if(p == NULL)
        return 0;
    else
        return 1;
}

int main()
{
    printf("연결 리스트를 이용한 리스트의 ADT");
    return 0;
}


// Object-Oriented Programming
