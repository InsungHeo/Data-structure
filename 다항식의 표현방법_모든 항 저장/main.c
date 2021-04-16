#include <stdio.h>
#define Max(a, b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

// 모든 항을 저장하는 다항식 선언문
typedef struct
{
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;

// 두 다항식을 더하는 함수
Polynomial poly_add1(Polynomial A, Polynomial B)
{
    // 결과 다항식 선언
    Polynomial C;
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    // 결과 다항식의 차수는 A, B 중 차수가 큰 것을 따른다.
    C.degree = Max(A.degree, B.degree);


    while(Apos <= A.degree && Bpos <= B.degree)
    {
        // A, B의 높은 차수부터 고려하여 C의 높은 차수의 계수 결정
        if(degree_a > degree_b)
        {
            C.coef[Cpos++] = A.coef[Apos++];
            degree_a--;
        }
        else if(degree_a == degree_b)
        {
            C.coef[Cpos++] = A.coef[Apos++] + B.coef[Bpos++];
            degree_a--;
            degree_b--;
        }
        else
        {
            C.coef[Cpos++] = B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

int main()
{
    Polynomial a = {5, {10, 0, 0, 0, 3, 6}}; //10x^5 + 6x + 3
    Polynomial b = {4, {1, 0, 5, 0, 7}};     //x^4 + 5x^2 + 7
    Polynomial c;
    c = poly_add1(a, b);
    for(int i = 0; i < c.degree + 1; i++)
        printf("%.1fx^%d + ", c.coef[i], c.degree - i);
    return 0;

}
