#include <stdio.h>
#include <stdlib.h>
#define ROWS 3
#define COLS 3
// 희소 행렬 덧셈 함수

// 장점: 행렬의 연산들을 간단하게 구현할 수 있다
// 단점: 대부분의 항들이 0인 희소 행렬의 경우 많은 메모리 공간 낭비

// C = A + B
void sparse_matrix_add1(int (*A)[COLS], int B[][COLS], int C[ROWS][COLS]) // 2차원 배열을 함수 인자로 전달하는 방법
{
    for(int r = 0; r < ROWS; r++)
        for(int c = 0; c < COLS; c++)
            C[r][c] = A[r][c] + B[r][c];
}

int main()
{
    int array1[ROWS][COLS] = {
        {2, 3, 0},
        {8, 9, 1},
        {7, 0, 5}
    };
    int array2[ROWS][COLS] = {
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0}
    };
    int array3[ROWS][COLS];

    sparse_matrix_add1(array1, array2, array3);

    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
            printf("%d ", array3[r][c]);
        printf("\n");
    }
    return 0;
}

