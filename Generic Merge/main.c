#include <stdio.h>
#include <stdlib.h>

// ���ĵ� �迭 a�� b�� ���̴� ���� m, n
// �迭 c�� �迭 a�� b�� �����ϸ鼭 ��ģ ��
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

    if(i < m)
        while(i < m)
        {
            c[k] = a[i];
            i++;
            k++;
        }
    else
        while(j < n)
        {
            c[k] = b[j];
            j++;
            k++;
        }

}

int main()
{
    return 0;
}
