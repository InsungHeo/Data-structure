#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

// element ����ü ����.
typedef struct
{
    int key;
} element;

// HeadType ����ü ����.
typedef struct
{
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

// �� ���� element�� ��ȯ���ִ� �Լ�.
void swap(element *a, element *b)
{
    element temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

// �ʱ�ȭ �Լ�
void init(HeapType *h)
{
    h->heap_size = 0;
}

// ����Լ��� �̿��� ���� �Լ�.
void insert_min_heap(HeapType *h, element item, int i)
{
    // ��Ʈ ��忡 �������� �ʾ��� ���� item�� ũ�Ⱑ �θ� ��庸�� ũ�ų� ���� �� ����.
    if(i != 1 && item.key < h->heap[i/2].key)
    {
        h->heap[i] = h->heap[i/2];
        i /= 2;
        insert_min_heap(h, item, i);
    }
    h->heap[i] = item;
}

// ���� �Լ�
element delete_min_heap(HeapType *h)
{
    // return�� item�� ���� �� �ʱ�ȭ.
    element item = h->heap[1];
    // ��Ʈ ��忡 ������ ����� element�� �����Ѵ�.
    h->heap[1] = h->heap[h->heap_size--];
    // ���ĵ��� ���� heap�� �ٽ� �迭.
    recursive_min_heapify(h, 1);
    return item;
}

// ���ĵ��� ���� heap�� �Է� �޾� min heap�� ������ �����ϰ� �迭�� �����ϴ� �Լ�.
void recursive_min_heapify(HeapType *h, int parent) // ���
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
void sequential_min_heapify(HeapType *h, int parent) // �ݺ�
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
    // heap ���� �� �ʱ�ȭ.
    HeapType heap;
    init(&heap);

    element item, a[MAX_ELEMENT];

    int n = 0, cnt = 0, k = 0;
    char x[MAX_ELEMENT];
    element y[MAX_ELEMENT];

    // input, output ���� ����.
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // ���� ���� ���� �� exit.
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }

    // ù ���� �� �Է¹ޱ�.
    while(fgetc(file_input) != '\n')
    {
        // fgetc���� ���� ���� �ǵ����� ���� ���� ���� �������� ��ġ�� �������� �� ĭ �̵�.
        fseek(file_input, -1, SEEK_CUR);
        // initial data�� ���ʴ�� �Է¹޾� a[]�� ����.
        fscanf(file_input, "%d", &a[n++].key);
    }

    // initial data�� ���ĵ��� ���� heap���� ������ش�.
    heap.heap_size = n;
    for(int i = 1; i <= n; i++)
        heap.heap[i] = a[i - 1];

    // ���ĵ��� ���� heap�� �Է¹޾�, Min Heap�� ������ �����ϰ� �����ϴ� �Լ�.
    recursive_min_heapify(&heap, 1); // ���.
//    sequential_min_heapify(&heap, 1); // �ݺ�.

    // �� ��° �ٿ������� ������ �Է¹ޱ�.
    while(1)
    {
        // �� ���� ù ��° ���ڸ� �Է¹޴´�.
        x[cnt] = fgetc(file_input);

        // �Է��� 'i', 'd' �� �����ΰ��� ���� �ٸ� �ڵ� ����.
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
                fprintf(file_output, "%d���� �Է� ������ �߸��Ǿ����ϴ�.\n", cnt + 1);
                fgetc(file_input);
                continue;
        }
        cnt++;

        // heap�� level-order ���.
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

        // file_input�� �ִ� '\n'�� �����, file_input�� ���� �о��� �� ����.
        if(fgetc(file_input) == EOF)
            break;
    }


    // input, output ���� �ݾ��ֱ�
    fclose(file_input);
    fclose(file_output);

    return 0;
}
