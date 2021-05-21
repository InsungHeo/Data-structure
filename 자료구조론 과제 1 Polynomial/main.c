#include <stdio.h>
#include <stdlib.h>
#include <error.h>

typedef struct ListNode // 한 노드에 대한 정보를 담은 구조체
{
    int coef;
    int expon;
    struct ListNode *link;
} ListNode;

typedef struct ListHeader // 한 리스트의 길이 및 시작점과 끝점에 대한 정보를 담은 구조체
{
    int length;
    ListNode *head;
    ListNode *tail;
} ListHeader;

void init(ListHeader *plist) // 초기화 함수
{
    plist->length = 0;
    plist->head = plist->tail = NULL;
}

void insert_node_last(ListHeader *plist, int coef, int expon) // list의 뒷부분에 새로운 노드를 추가
{
    ListNode *temp = (ListNode *)malloc(sizeof(ListNode));
    // safe coding
    if(temp == NULL)
        perror("메모리 할당 에러");
    temp->coef = coef;
    temp->expon = expon;
    temp->link = NULL;

    // 빈 리스트인 경우
    if(plist->tail == NULL)
        plist->head = plist->tail = temp;
    // 비어있지 않은 리스트인 경우
    else
    {
        plist->tail->link = temp;
        plist->tail = temp;
    }
    // 리스트의 길이 1 증가
    plist->length++;
}

ListHeader poly_add(ListHeader *plist1, ListHeader *plist2) // list 2개를 ListHeader 포인터로 입력받아 ListHeader 형 list return
{
    // return할 리스트 선언 및 초기화
    ListHeader listsum;
    init(&listsum);

    // 입력된 리스트에서 체크하는 위치를 확인하기 위한 a, b 선언
    ListNode *a = plist1->head;
    ListNode *b = plist2->head;

    int sum;
    while(a && b) // a와 b가 NULL이 아닐 때
    {
        // 두 다항식의 비교하는 항의 차수가 같은 경우
        if(a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if(sum != 0)
                insert_node_last(&listsum, sum, a->expon);
            a = a->link;
            b = b->link;
        }

        // 두 다항식의 비교하는 항의 차수가 첫 번째 다항식이 더 큰 경우
        else if(a->expon > b->expon)
        {
            insert_node_last(&listsum, a->coef, a->expon);
            a = a->link;
        }

        // 두 다항식의 비교하는 항의 차수가 첫 번째 다항식이 더 작 경우
        else
        {
            insert_node_last(&listsum, b->coef, b->expon);
            b = b->link;
        }
    }
    // a나 b 중에 NULL이 생겼을 때
    // 즉, 두 다항식 중 하나의 스캔이 끝났을 때
    for(;a != NULL; a = a->link)
        insert_node_last(&listsum, a->coef, a->expon);
    for(;b != NULL; b = b->link)
        insert_node_last(&listsum, b->coef, b->expon);
    return listsum;
}

ListHeader poly_mult(ListHeader *plist1, ListHeader *plist2) // list 2개를 ListHeader 포인터로 입력받아 ListHeader 형 list return
{
    // 두 다항식의 곱을 구하기 위한 도구로 활용되는 세 개의 list 선언 및 초기화
    ListHeader lista, listb, listc;
    init(&lista);
    init(&listb);
    init(&listc);

    // 입력된 리스트에서 체크하는 위치를 확인하기 위한 x, y 선언
    ListNode *x = plist1->head;
    ListNode *y = plist2->head;

    // cnt를 통해 return할 리스트를 결정
    int cnt = 0;

    while(x) // x가 NULL이 아닐 때, list[0]이 모든 항을 훑을 때까지 반복
    {
        while(y) // y가 NULL이 아닐 때, list[1]이 모든 항을 훑을 때까지 반복
        {
            // list[0] 다항식의 한 항과 list[1] 다항식 전체의 곱을 담은 lista
            insert_node_last(&lista, (x->coef)*(y->coef), (x->expon) + (y->expon));
            y = y->link;
        }

        if(cnt%2 == 0)
        {
            // lista와 listb를 더한 것을 listc라 하고 listb 초기화
            listc = poly_add(&lista, &listb);
            init(&listb);
        }
        else
        {
            // lista와 listc를 더한 것을 listb라 하고 listc 초기화
            listb = poly_add(&lista, &listc);
            init(&listc);
        }

        cnt++;
        init(&lista);
        x = x->link;
        y = plist2->head;
    }
    // cnt가 짝수이면 listb 리턴, 홀수이면 listc 리턴
    if(cnt%2 == 0)
        return listb;
    return listc;
}

void poly_print_file(ListHeader *plist, FILE * file) // list의 처음부터 끝까지 훑으면서 파일에 출력
{
    ListNode *p = plist->head;
    for(; p != NULL; p = p->link)
        fprintf(file, "%d %d\n", p->coef, p->expon);
}

int main()
{
    // 초기 선언
    ListHeader list[2], listsum, listmult;
    int coef, expon, ch;

    // input, output 파일 열기
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // list 초기화
    init(list);
    init(list + 1);
    init(&listsum); // 덧셈
    init(&listmult); // 곱셈

    // 파일 열기 실패 시
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "파일 열기 실패\n");
        exit(1);
    }

    // list[0], list[1] 생성 과정
    // '\n'이 두 번 나올 때까지 list[0] 입럭
    while(ch = fgetc(file_input) != '\n' && ch != EOF)
    {
        fseek(file_input, -1, SEEK_CUR);
        fscanf(file_input, "%d %d", &coef, &expon);
        ch = fgetc(file_input); // 공백 지우기 enter
        insert_node_last(list, coef, expon); // list[0]에 coef, expon 대입
    }
    // EOF가 나올 때까지 list[1] 입력
    while(ch = fgetc(file_input) != EOF)
    {
        fseek(file_input, -1, SEEK_CUR);
        fscanf(file_input, "%d %d", &coef, &expon);
        ch = fgetc(file_input); // 공백 지우기 enter
        insert_node_last(list + 1, coef, expon); // list[1]에 coef, expon 대입
    }

    // input 파일 닫아주기
    fclose(file_input);

    // list[0], list[1] 더하고 파일에 출력
    fprintf(file_output, "Addition\n");
    listsum = poly_add(list, list + 1);
    poly_print_file(&listsum, file_output);

    // list[0], list[1] 곱하고 파일에 출력
    fprintf(file_output, "Multiplication\n");
    listmult = poly_mult(list, list + 1);
    poly_print_file(&listmult, file_output);

    // output 파일 닫아주기
    fclose(file_output);

    return 0;
}
