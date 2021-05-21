#include <stdio.h>
#include <stdlib.h>
#include <error.h>

typedef struct ListNode // �� ��忡 ���� ������ ���� ����ü
{
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListHeader // �� ����Ʈ�� ���� �� �������� ������ ���� ������ ���� ����ü
{
    int length;
    ListNode *head;
    ListNode *tail;
} ListHeader;

void init(ListHeader *plist) // �ʱ�ȭ �Լ�
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

void insert_node_last(ListHeader *plist, int coef, int expon) // list�� �޺κп� ���ο� ��带 �߰�
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    // safe coding
    if(temp == NULL)
        perror("�޸� �Ҵ� ����");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    // �� ����Ʈ�� ���
    if(plist->tail == NULL)
        plist->head = plist->tail = temp;
    // ������� ���� ����Ʈ�� ���
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    // ����Ʈ�� ���� 1 ����
    plist->length++;
}

ListHeader poly_add(ListHeader *plist1, ListHeader *plist2) // list 2���� ListHeader �����ͷ� �Է¹޾� ListHeader �� list return
{
    // return�� ����Ʈ ���� �� �ʱ�ȭ
    ListHeader listsum;
    init(&listsum);

    // �Էµ� ����Ʈ���� üũ�ϴ� ��ġ�� Ȯ���ϱ� ���� a, b ����
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;

    int sum;
    while(a && b) // a�� b�� NULL�� �ƴ� ��
    {
        // �� ���׽��� ���ϴ� ���� ������ ���� ���
        if(a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if(sum != 0)
                insert_node_last(&listsum, sum, a->expon);
            a = a->link;
            b = b->link;
        }

        // �� ���׽��� ���ϴ� ���� ������ ù ��° ���׽��� �� ū ���
        else if(a->expon > b->expon)
        {
            insert_node_last(&listsum, a->coef, a->expon);
            a = a->link;
        }

        // �� ���׽��� ���ϴ� ���� ������ ù ��° ���׽��� �� �� ���
        else
        {
            insert_node_last(&listsum, b->coef, b->expon);
            b = b->link;
        }
    }
    // a�� b �߿� NULL�� ������ ��
    // ��, �� ���׽� �� �ϳ��� ��ĵ�� ������ ��
    for(;a != NULL; a = a->link)
        insert_node_last(&listsum, a->coef, a->expon);
    for(;b != NULL; b = b->link)
        insert_node_last(&listsum, b->coef, b->expon);
    return listsum;
}

ListHeader poly_mult(ListHeader *plist1, ListHeader *plist2) // list 2���� ListHeader �����ͷ� �Է¹޾� ListHeader �� list return
{
    // �� ���׽��� ���� ���ϱ� ���� ������ Ȱ��Ǵ� �� ���� list ���� �� �ʱ�ȭ
    ListHeader lista, listb, listc;
    init(&lista);
    init(&listb);
    init(&listc);

    // �Էµ� ����Ʈ���� üũ�ϴ� ��ġ�� Ȯ���ϱ� ���� x, y ����
    ListNode *x = plist1->head;
    ListNode *y = plist2->head;

    // cnt�� ���� return�� ����Ʈ�� ����
    int cnt = 0;

    while(x) // x�� NULL�� �ƴ� ��, list[0]�� ��� ���� ���� ������ �ݺ�
    {
        while(y) // y�� NULL�� �ƴ� ��, list[1]�� ��� ���� ���� ������ �ݺ�
        {
            // list[0] ���׽��� �� �װ� list[1] ���׽� ��ü�� ���� ���� lista
            insert_node_last(&lista, (x->coef)*(y->coef), (x->expon) + (y->expon));
            y = y->link;
        }

        if(cnt%2 == 0)
        {
            // lista�� listb�� ���� ���� listc�� �ϰ� listb �ʱ�ȭ
            listc = poly_add(&lista, &listb);
            init(&listb);
        }
        else
        {
            // lista�� listc�� ���� ���� listb�� �ϰ� listc �ʱ�ȭ
            listb = poly_add(&lista, &listc);
            init(&listc);
        }

        cnt++;
        init(&lista);
        x = x->link;
        y = plist2->head;
    }
    // cnt�� ¦���̸� listb ����, Ȧ���̸� listc ����
    if(cnt%2 == 0)
        return listb;
    return listc;
}

void poly_print_file(ListHeader *plist, FILE * file) // list�� ó������ ������ �����鼭 ���Ͽ� ���
{
    ListNode *p = plist->head;
    for(; p != NULL; p = p->link)
        fprintf(file, "%d %d\n", p->coef, p->expon);
}

int main()
{
    // �ʱ� ����
    ListHeader list[2], listsum, listmult;
    int coef, expon, ch;

    // input, output ���� ����
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // list �ʱ�ȭ
    init(list);
    init(list + 1);
    init(&listsum); // ����
    init(&listmult); // ����

    // ���� ���� ���� ��
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }

    // list[0], list[1] ���� ����
    // '\n'�� �� �� ���� ������ list[0] �Է�
    while(ch = fgetc(file_input) != '\n' && ch != EOF)
    {
        fseek(file_input, -1, SEEK_CUR);
        fscanf(file_input, "%d %d", &coef, &expon);
        ch = fgetc(file_input); // ���� ����� enter
        insert_node_last(list, coef, expon); // list[0]�� coef, expon ����
    }
    // EOF�� ���� ������ list[1] �Է�
    while(ch = fgetc(file_input) != EOF)
    {
        fseek(file_input, -1, SEEK_CUR);
        fscanf(file_input, "%d %d", &coef, &expon);
        ch = fgetc(file_input); // ���� ����� enter
        insert_node_last(list + 1, coef, expon); // list[1]�� coef, expon ����
    }

    // input ���� �ݾ��ֱ�
    fclose(file_input);

    // list[0], list[1] ���ϰ� ���Ͽ� ���
    fprintf(file_output, "Addition\n");
    listsum = poly_add(list, list + 1);
    poly_print_file(&listsum, file_output);

    // list[0], list[1] ���ϰ� ���Ͽ� ���
    fprintf(file_output, "Multiplication\n");
    listmult = poly_mult(list, list + 1);
    poly_print_file(&listmult, file_output);

    // output ���� �ݾ��ֱ�
    fclose(file_output);

    return 0;
}
