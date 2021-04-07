#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100
// ADT 리스트 추상 데이터 타입

typedef int element;

typedef struct
{
    int list[MAX_LIST_SIZE];  // 배열 정의
    int length;               // 현재 배열에 저장된 항목들의 개수
} ArrayListType;

void init(ArrayListType *L) // 리스트 초기화
{
    L->length = 0;
}

int is_empty(ArrayListType *L) // 리스트가 비어있으면 1 반환
{
    return L->length == 0;
}
int is_full(ArrayListType *L)  // 리스트가 가득 차 있으면 1 반환
{
    return L->length == MAX_LIST_SIZE;
}

// position: 삽입하고자하는 위치
// item: 삽입하고자하는 자료
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
// position: 삭제하고자 하는 위치
// return 값: 삭제되는 자료
element delete(ArrayListType *L, int position)
{
    element item;
    if(position < 0 || position >= L->length)
//        error("위치 오류");
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
