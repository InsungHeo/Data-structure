#include <stdio.h>
#define Max(a, b) (((a)>(b))?(a):(b))
#define MAX_DEGREE 101

// ��� ���� �����ϴ� ���׽� ����
typedef struct
{
    int degree;
    float coef[MAX_DEGREE];
} Polynomial;

// �� ���׽��� ���ϴ� �Լ�
Polynomial poly_add1(Polynomial A, Polynomial B)
{
    // ��� ���׽� ����
    Polynomial C;
    int Apos = 0, Bpos = 0, Cpos = 0;
    int degree_a = A.degree;
    int degree_b = B.degree;

    // ��� ���׽��� ������ A, B �� ������ ū ���� ������.
    C.degree = Max(A.degree, B.degree);


    while(Apos <= A.degree && Bpos <= B.degree)
    {
        // A, B�� ���� �������� ����Ͽ� C�� ���� ������ ��� ����
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
