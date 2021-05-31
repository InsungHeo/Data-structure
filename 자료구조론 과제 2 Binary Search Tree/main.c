#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>
#define max(x, y) ((x >= y) ? (x):(y))

////////////////////////////////////////////////////////////////////////////////////
// TreeNode 자료형 선언.
// int index가 있다는 점에서 교재와 다름. 노드의 index는 각 노드를 레벨 순으로 매긴 순서를 나타냄.
typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right;
    int index;
} TreeNode;

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리가 key값을 가지는지 존재 여부를 확인하는 함수.
// does_exist를 선언하여 key의 존재를 나타냄.
// preorder 순으로 탐색하여 key 값을 발견할 때마다 does_exist++
// does_exist가 0이면 Not Exist, 0이 아니면 Exist.
int does_exist = 0;
void search(TreeNode *root, int key)
{
    // 이진 트리가 비어있지 않은 경우.
    if(root != NULL)
    {
        if(root->key == key)
            does_exist += 1;

        search(root->left, key);
        search(root->right, key);
    }
}

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리의 노드 index 값과 key 값을 연결해주는 함수.
// preorder 순으로 index와 key를 연결해줌.
void con_index_key(TreeNode *root, int arr[])
{
    if(root)
    {
        arr[root->index - 1] = root->key;
        con_index_key(root->left, arr);
        con_index_key(root->right, arr);
    }
}

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리에 원소를 삽입하는 함수.
// 이진 트리에 원소를 삽입하기 위해서는 먼저 탐색을 수행하는 것이 필요.
// 탐색에 실패한 위치를 새로운 node의 위치로 선정.
// key가 이미 이진 트리에 있으면 left child에 삽입.
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t; // p는 부모노드, t는 현재 노드.
    TreeNode *n;     // n은 새로운 노드.
    t = *root;
    p = NULL;

    // p가 단말노드가 될때까지 실행.
    while(t != NULL)
    {
        p = t;
        if(key == t->key)
        {
            t = p->left;
            break;
        }
        else if(key < p->key)
            t = p->left;
        else
            t = p->right;
    }

    // 새로 추가될 node에 동적 메모리 할당.
    n = (TreeNode *)malloc(sizeof(TreeNode));
    if(n == NULL)
        perror("메모리 할당 에러");

    // 새로운 node의 key, left, right 초기화.
    n->key = key;
    n->left = n->right = NULL;

    // 부모 노드가 존재할 경우.
    if(p != NULL)
    {
        if(key == p->key)
        {
            n->left = p->left;
            p->left = n;
            give_index(p, p->index);
        }
        else if(key < p->key)
        {
            p->left = n;
            n->index = p->index * 2;
        }
        else
        {
            p->right = n;
            n->index = p->index * 2 + 1;
        }
    }
    // 부모 노드가 존재하지 않을 경우.
    else
    {
        *root = n;
        n->index = 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리에서 원소를 삭제하는 함수.
// 다음 세 가지 case를 고려함.
// CASE 1. 삭제하려는 노드가 단말 노드일 경우.
// CASE 2. 삭제하려는 노드가 왼쪽이나 오른쪽 서브 트리 중 하나만 가지고 있는 경우.
// CASE 3. 삭제하려는 노드가 두 개의 서브 트리 모두 가지고 있는 경우.
void delete_node(TreeNode **root, int key)
{
    // key를 갖는 노드 t를 탐색, p는 t의 부모노드
    TreeNode *p, **child, *t, *tt, *pp;
    p = NULL;
    pp = NULL;
    t = *root;

    // key를 갖는 노드 t를 탐색한다.
    while(t != NULL && t->key != key)
    {
        p = t;
        t = (key < t->key) ? t->left : t->right;
    }

    // 탐색이 종료된 시점에 t가 NULL이면 트리 안에 key가 없음.
    if(t == NULL)
    {
        does_exist = 'n';
        return;
    }


    // CASE 1. 단말노드인 경우.
    if((t->left == NULL) && (t->right == NULL))
    {
        if(p != NULL)
        {
            // 부모노드의 자식필드를 NULL로 만든다.
            if(p->left == t)
                p->left = NULL;

            else
                p->right = NULL;
        }
        else
            *root = NULL;
    }

    // CASE 2. 하나의 자식만 가지는 경우.
    else if((t->left) == NULL || (t->right == NULL))
    {
        child = (t->left != NULL) ? t->left : t->right;
        if(p != NULL)
        {
            if(p->left == t)
            {
                p->left = child;
                give_index(child, t->index);
            }
            else
            {
                p->right = child;
                give_index(child, t->index);
            }
        }
        else
        {
            *root = child;
            give_index(child, 1);
        }

    }

    // CASE 3. 두 개의 자식을 가지는 경우.
    else
    {
        tt = t;
        p = t;
        t = t->right;
        while(t->left != NULL)
        {
            p = t;
            t = t->left;
        }
        delete_node(root, t->key);
        tt->key = t->key;
    }

}

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리의 노드에 index를 부여하는 함수.
// 입력 받은 node의 자식 노드에게도 index 값을 부여.
// left child는 parent index의 2배, rigth child는 parent index의 2배 더하기 1.
void give_index(TreeNode *node, int index)
{
    TreeNode *t; // p는 부모노드, t는 현재 노드.
    node->index = index; // 입력 받은 node에 입력 받은 index 부여.
    t = node;
    if(t->left != NULL)
        give_index(t->left, 2*index);
    if(t->right != NULL)
        give_index(t->right, 2*index + 1);
}

////////////////////////////////////////////////////////////////////////////////////
// 이진 트리의 높이를 return하는 함수.
// 서브 트리에 대하여 순환호출하여 이 중 최댓값을 이용해 높이 계산.
int get_height(TreeNode *root)
{
    int height = 0;
    if(root)
        height = 1 + max(get_height(root->left), get_height(root->right));
    return height;
}

int main()
{
    // 이진 트리의 root 선언 및 초기화.
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root = NULL;

    // input, output 파일 열기.
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // 파일 열기 실패 시 exit.
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "파일 열기 실패\n");
        exit(1);
    }

    int cnt = 0; // 입력 받은 node의 개수 체크.
    char x[64]; // file_input에서 'i', 'd', 's'를 입력 받아 저장하는 배열.
    int  y[64]; // file_input에서 node의 key 값을 입력 받아 저장하는 배열.

    // file_input을 전부 읽을 때까지 반복.
    while(1)
    {
        // key의 존재 여부를 체크하는 does_exist를 0으로 초기화.
        does_exist = 0;

        // file_input 읽어오기.
        fscanf(file_input, "%c%d", &x[cnt], &y[cnt]);

        // 입력이 'i', 'd', 's' 중 무엇인가에 따라 다른 코드 실행.
        switch(x[cnt])
        {
            case 'i':
                insert_node(&root, y[cnt]);
                break;

            case 'd':
                delete_node(&root, y[cnt]);
                break;

            case 's':
                search(root, y[cnt]);
                if(does_exist != 0)
                    does_exist = 'y';
                else
                    does_exist = 'n';
                break;

            default :
                fprintf(file_output, "%d줄의 입력 형식이 잘못되었습니다.\n", ++cnt);
                fgetc(file_input);
                continue;
        }
        fprintf(file_output, "%c%d : ", x[cnt++], y[cnt]);

        // 'i', 'd', 's' 중 's'나 'd'가 입력이 된 경우.
        if(does_exist == 'y')
            fprintf(file_output, "Exist\n");
        else if(does_exist == 'n')
            fprintf(file_output, "Not Exist\n");

        // 'i', 'd', 's' 중 'i'나 'd'가 입력이 된 경우.
        else
        {
            // node의 index 값을 저장하는 배열에 동적 메모리를 할당 및 0으로 초기화.
            int *arr = (int *)malloc(sizeof(int) * pow(2, get_height(root)));
            for(int i = 0; i < pow(2, get_height(root)) - 1; i++)
                arr[i] = 0;

            // 이진 트리의 모든 node의 index와 key 연결.
            con_index_key(root, arr);

            // file_output에 형식에 맞게 출력.
            for(int i = 0; i < pow(2, get_height(root)) - 1; i++)
            {
                fprintf(file_output, "%d", arr[i]);
                if(i != pow(2, get_height(root)) - 2)
                    fprintf(file_output, ", ");
            }
            fprintf(file_output, "\n");

            // arr에 동적으로 할당된 메모리 해제.
            free(arr);
        }

        // file_input에 있는 '\n'을 지우고, file_input을 전부 읽었을 때 종료.
        if(fgetc(file_input) == EOF)
            break;
    }
    // input, output 파일 닫기.
    fclose(file_input);
    fclose(file_output);

    return 0;
}
