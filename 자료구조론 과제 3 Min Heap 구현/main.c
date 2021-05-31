#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

// element 구조체 정의.
typedef struct
{
    int key;
} element;

// HeadType 구조체 정의.
typedef struct
{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// 두 개의 element를 교환해주는 함수.
void swap(element *a, element *b)
{
    element temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// 초기화 함수
void init(HeapType *h)
{
    h->heap_size = 0;
}

// 재귀함수를 이용한 삽입 함수.
void insert_min_heap(HeapType *h, element item, int i)
{
    // 루트 노드에 도착하지 않았을 때나 item의 크기가 부모 노드보다 크거나 같을 때 실행.
    if(i != 1 && item.key < h->heap[i/2].key)
    {
        h->heap[i] = h->heap[i/2];
        i /= 2;
        insert_min_heap(h, item, i);
    }
    h->heap[i] = item;
}

// 삭제 함수
element delete_min_heap(HeapType *h)
{
    // return할 item을 선언 및 초기화.
    element item = h->heap[1];
    // 루트 노드에 마지막 노드의 element를 대입한다.
    h->heap[1] = h->heap[h->heap_size--];
    // 정렬되지 않은 heap를 다시 배열.
    recursive_min_heapify(h, 1);
    return item;
}

// 정렬되지 않은 heap를 입력 받아 min heap의 성질을 만족하게 배열을 정렬하는 함수.
void recursive_min_heapify(HeapType *h, int parent) // 재귀
{
    int child = 2*parent;
    element temp;

    if(child > h->heap_size)
        return;
    if(child == h->heap_size)
    {
        if(h->heap[parent].key > h->heap[child].key)
            swap(&h->heap[parent], &h->heap[child]);
        return;
    }
    if(h->heap[child].key > h->heap[child + 1].key && h->heap[child + 1].key < h->heap[parent].key)
        swap(&h->heap[parent], &h->heap[++child]);
    else if(h->heap[child + 1].key >= h->heap[child].key && h->heap[child].key < h->heap[parent].key)
        swap(&h->heap[parent], &h->heap[child]);
    recursive_min_heapify(h, child);
}
void sequential_min_heapify(HeapType *h, int parent) // 반복
{
    int child = 2*parent;
    while(child < h->heap_size)
    {
        if(child == h->heap_size)
        {
            if(h->heap[parent].key > h->heap[child].key)
                swap(&h->heap[parent], &h->heap[child]);
            break;
        }
        if(h->heap[child].key > h->heap[child + 1].key && h->heap[child + 1].key < h->heap[parent].key)
            swap(&h->heap[parent], &h->heap[++child]);
        else if(h->heap[child + 1].key >= h->heap[child].key && h->heap[child].key < h->heap[parent].key)
            swap(&h->heap[parent], &h->heap[child]);
        else
            break;
        parent = child;
    }
}


int main()
{
    // heap 선언 및 초기화.
    HeapType heap;
    init(&heap);

    element item, a[MAX_ELEMENT];

    int n = 0, cnt = 0, k = 0;
    char x[MAX_ELEMENT];
    element y[MAX_ELEMENT];

    // input, output 파일 열기.
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // 파일 열기 실패 시 exit.
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "파일 열기 실패\n");
        exit(1);
    }

    // 첫 번쨰 줄 입력받기.
    while(fgetc(file_input) != '\n')
    {
        // fgetc에서 읽은 것을 되돌리기 위해 현재 파일 포인터의 위치를 왼쪽으로 한 칸 이동.
        fseek(file_input, -1, SEEK_CUR);
        // initial data를 차례대로 입력받아 a[]에 저장.
        fscanf(file_input, "%d", &a[n++].key);
    }

    // initial data를 정렬되지 않은 heap으로 만들어준다.
    heap.heap_size = n;
    for(int i = 1; i <= n; i++)
        heap.heap[i] = a[i - 1];

    // 정렬되지 않은 heap를 입력받아, Min Heap의 성질을 만족하게 정렬하는 함수.
    recursive_min_heapify(&heap, 1); // 재귀.
//    sequential_min_heapify(&heap, 1); // 반복.

    // 두 번째 줄에서부터 끝까지 입력받기.
    while(1)
    {
        // 각 줄의 첫 번째 문자를 입력받는다.
        x[cnt] = fgetc(file_input);

        // 입력이 'i', 'd' 중 무엇인가에 따라 다른 코드 실행.
        switch(x[cnt])
        {
            case 'i':
                fscanf(file_input, "%d", &y[cnt].key);
                heap.heap_size++;
                insert_min_heap(&heap, y[cnt], heap.heap_size);
                fprintf(file_output, "%c%d : ", x[cnt], y[cnt]);
                break;

            case 'd':
                y[cnt] = delete_min_heap(&heap);
                fprintf(file_output, "%c : %d / ", x[cnt], y[cnt]);
                break;

            default :
                fprintf(file_output, "%d줄의 입력 형식이 잘못되었습니다.\n", cnt + 1);
                fgetc(file_input);
                continue;
        }
        cnt++;

        // heap을 level-order 출력.
        for(int i = 1; i < heap.heap_size + 1; i++)
        {
            fprintf(file_output, "%d", heap.heap[i].key);
            if(i != heap.heap_size)
                fprintf(file_output, ", ");
        }
        int k = 0;
        while(pow(2, k) - heap.heap_size - 1 < 0)
            k++;
        for(int i = 0; i < pow(2, k) - heap.heap_size - 1; i++)
        {
            if(i != pow(2, k) - heap.heap_size - 1)
                fprintf(file_output, ", ");
            fprintf(file_output, "0");
        }
        fprintf(file_output, "\n");

        // file_input에 있는 '\n'을 지우고, file_input을 전부 읽었을 때 종료.
        if(fgetc(file_input) == EOF)
            break;
    }


    // input, output 파일 닫아주기
    fclose(file_input);
    fclose(file_output);

    return 0;
}
