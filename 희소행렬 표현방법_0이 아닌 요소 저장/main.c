#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLS 3
#define MAX_TERMS 10

typedef struct
{
    int row;
    int col;
    int value;
} element;

typedef struct
{
    element data[MAX_TERMS];
    int rows;
    int cols;
    int terms;
} SparseMatrix;

SparseMatrix sparse_matrix_add2(SparseMatrix a, SparseMatrix b)
{
    SparseMatrix c;
    int ca = 0, cb = 0, cc = 0; // 각 배열의 항목을 가리키는 인덱스

    // 배열 a와 배열 b의 크기가 같은지를 확인
    if(a.rows != b.rows || a.cols != b.cols)
    {
        fprintf(stderr, "희소행렬 크기 에러\n");
        exit(1);
    }

    c.rows = a.rows;
    c.cols = a.cols;
    c.terms = 0;

    while(ca < a.terms && cb < b.terms)
    {
        // 각 항목의 순차적인 번호를 계산한다.
        int inda = a.data[ca].row * a.cols + a.data[ca].col;
        int indb = b.data[cb].row * b.cols + b.data[cb].col;

        if(inda < indb)
            c.data[cc++] = a.data[ca++];

        else if(inda == indb)
        {
            if((a.data[ca].value + b.data[cb].value) != 0)
            {
                c.data[cc].row = a.data[ca].row;
                c.data[cc].col = a.data[ca].col;
                c.data[cc++].value = a.data[ca++].value + b.data[cb++].value;
            }
            else
                ca++; cb++;
        }

        else
            c.data[cc++] = b.data[cb++];
    }

    // 배열 a와 b에 남아 있는 항들을 배열 c로 옮긴다.
    for(;ca < a.terms;)
        c.data[cc++] = a.data[ca++];
    for(;cb < b.terms;)
        c.data[cc++] = b.data[cb++];

    c.terms = cc;

    return c;
}

int main()
{
    SparseMatrix m1 = {{{1, 1, 5}, {2, 2, 9}}, 3, 3, 2};
    SparseMatrix m2 = {{{0, 0, 5}, {2, 2, 9}}, 3, 3, 2};
    SparseMatrix m3;

    m3 = sparse_matrix_add2(m1, m2);

    int k = 0;

    // m3 출력
    for(int row = 0; row < ROWS; row++)
    {
        for(int col = 0; col < COLS; col++)
        {
            if(m3.data[k].col == col && m3.data[k].row == row)
                printf("%d ", m3.data[k++].value);
            else
                printf("0 ");
        }
        printf("\n");
    }
    return 0;
}
