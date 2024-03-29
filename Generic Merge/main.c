#include <stdio.h>
#include <stdlib.h>

// 정렬된 배열 a와 b의 길이는 각각 m, n
// 배열 c는 배열 a와 b를 정렬하면서 합친 것
void merge(int *a, int m, int *b, int n, int *c)
{
    int i = 0, j = 0, k = 0;

    while(i < m && j < n)
    {
        if(a[i] < b[j])
        {
            c[k] = a[i];
            i++;
        }
        else if(a[i] > b[j])
        {
            c[k] = b[j];
            j++;
        }
        else
        {
            c[k] = a[i];
            c[k+1] = b[j];
            i++; j++; k++;
        }
        k++;
    }

    // 나머지 원소를 c에 이어붙인다.
    while(i < m)
    {
        c[k] = a[i];
        i++;
        k++;
    }
    while(j < n)
    {
        c[k] = b[j];
        j++;
        k++;
    }

}

int main()
{
    int a[4] = {0, 2, 25, 50};
    int b[3] = {1, 18, 100};
    int c[7] = {0,};
    merge(a, 4, b, 3, c);
    for(int i = 0; i < 7; i++)
        printf("%d ", c[i]);
    return 0;
}
