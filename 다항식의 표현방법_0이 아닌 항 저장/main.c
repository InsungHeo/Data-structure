#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 101

// 다항식 표현 방법_0이 아닌 항 저장
// (계수, 차수) 형식
struct
{
    float coef;
    int expon;
} terms[MAX_TERMS] = {{8, 3}, {7, 1}, {1, 0}, {10, 3}, {3, 2}, {1, 0}};

int avail = 6;

char compare(int a, int b)
{
    if(a > b)
        return '>';
    else if(a == b)
        return '=';
    else
        return '<';
}

// 더해진 다항식을 terms[]에 이어붙이는 함수
void attach(float coef, int expon)
{
    if(avail > MAX_TERMS)
    {
        fprintf(stderr, "항의 개수가 너무 많음\n");
        // 오류 상황 탈출을 위한 exit(1);
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void poly_add2(int As, int Ae, int Bs, int Be, int *Cs, int *Ce)
{
    float tempcoef;
    *Cs = avail;
    while(As <= Ae && Bs <= Be)
        switch(compare(terms[As].expon, terms[Bs].expon))
        {
            case '>': // A의 차수 > B의 차수
                attach(terms[As].coef, terms[As].expon);
                As++;
                break;
            case '<': // A의 차수 < B의 차수
                attach(terms[Bs].coef, terms[Bs].expon);
                Bs++;
                break;
            case '=': // A의 차수 = B의 차수
                tempcoef = terms[As].coef + terms[Bs].coef;
                if(tempcoef) // tempcoef가 0이 아닐 경우에만 if문 실행
                    attach(tempcoef, terms[As].expon);
                As++; Bs++;
                break;
        }

    // A의 나머지 항들을 이동함
    for(; As <= Ae; As++)
        attach(terms[As].coef, terms[As].expon);
    // B의 나머지 항들을 이동함
    for(; Bs <= Be; Bs++)
        attach(terms[Bs].coef, terms[Bs].expon);
    *Ce = avail - 1;
}

int main()
{
    int Cs, Ce;
    poly_add2(0, 2, 3, 5, &Cs, &Ce);
    for(int i = Cs; i < Ce + 1; i++)
        printf("%.1fx^%d  ", terms[i].coef, terms[i].expon);
    return 0;
}
