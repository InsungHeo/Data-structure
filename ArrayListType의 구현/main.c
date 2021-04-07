#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100
// ADT ����Ʈ �߻� ������ Ÿ��

typedef int element;

typedef struct
{
    int list[MAX_LIST_SIZE];  // �迭 ����
    int length;               // ���� �迭�� ����� �׸���� ����
} ArrayListType;

void init(ArrayListType *L) // ����Ʈ �ʱ�ȭ
{
    L->length = 0;
}

int is_empty(ArrayListType *L) // ����Ʈ�� ��������� 1 ��ȯ
{
    return L->length == 0;
}
int is_full(ArrayListType *L)  // ����Ʈ�� ���� �� ������ 1 ��ȯ
{
    return L->length == MAX_LIST_SIZE;
}

// position: �����ϰ����ϴ� ��ġ
// item: �����ϰ����ϴ� �ڷ�
void add(ArrayListType *L, int position, element item)
{
    if(!is_full(L) && (position >= 0) && (position <= L->length))
    {
        for(int i = (L->length-1); i >= position; i--)
            L->list[i+1] = L->list[i];
        L->list[position] = item;
        L->length++;
    }
}
// position: �����ϰ��� �ϴ� ��ġ
// return ��: �����Ǵ� �ڷ�
element delete(ArrayListType *L, int position)
{
    element item;
    if(position < 0 || position >= L->length)
//        error("��ġ ����");
    item = L->list[position];
    for(int i = position; i < (L->length - 1); i++)
        L->list[i] = L->list[i+1];
    return item;
}


int main()
{
    int i, n;
    return 0;
}
