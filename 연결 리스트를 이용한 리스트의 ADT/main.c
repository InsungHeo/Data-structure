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

// ����Ʈ �ȿ��� pos ��ġ�� ��带 ��ȯ�Ѵ�
ListNode *get_node_at(ListType *list, int pos)
{
    ListNode *tmp_node = list->head;
    if(pos < 0)
        return NULL;
    for(int i = 0; i < pos; i++)
        tmp_node = tmp_node->link;
    return tmp_node;
}

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

// �־��� ��ġ�� �����͸� �����Ѵ�
void add(ListType *list, int position, element data)
{
    ListNode *p;
    if((position >= 0) && (position <= list->length))
    {
        ListNode *node = (ListNode*)malloc(sizeof(ListNode));
        if(node == NULL)
//            error("�޸� �Ҵ翡��");
        node->data = data;
        p = get_node_at(list, position-1);
        insert_node(&(list->head), p, node);
        list->length++;
    }
}

// ����Ʈ�� ���� �����͸� �����Ѵ�
void add_last(ListType *list, element data)
{
    add(list, get_length(list), data);
}

// ����Ʈ�� ó���� �����͸� �����Ѵ�
void add_first(ListType *list, element data)
{
    add(list, 0, data);
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

// �־��� ��ġ�� �����͸� �����Ѵ�
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

// ��ġ pos�� �ش��ϴ� �����͸� ��ȯ�ϴ� ����
element get_entry(ListType *list, int pos)
{
    ListNode *p;
    if(pos >= list->length)
//        error("��ġ ����");
    p = get_node_at(list, pos);
    return p->data;
}

void clear(ListType *list, int pos)
{
    for(int i = 0; i < list->length; i++)
        delete(list, i);
}

//������ ������ ����Ѵ�
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

// ������ ���� s�� ��带 ã�´�
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
    printf("���� ����Ʈ�� �̿��� ����Ʈ�� ADT");
    return 0;
}


// Object-Oriented Programming
