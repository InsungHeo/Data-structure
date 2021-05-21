#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right;
} TreeNode;
//              5
//      3              7
//  1       4               9
TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, NULL, NULL};
TreeNode n3 = {3, &n1, &n2};
TreeNode n4 = {9, NULL, NULL};
TreeNode n5 = {7, NULL, &n4};
TreeNode n6 = {5, &n3, &n5};
TreeNode *exp = &n6;


// 스택을 사용한 순회법
// 전위순회 preorder
// 중위순회 inorder
// 후위순회 postorder

// 큐를 사용한 순회법
// 레벨 순회 level_order

//////////////////////////////////////////////search//////////////////////////////////////////////
// 순환적 방법
TreeNode *search1(TreeNode *node, int key)
{
    if(node == NULL)
        return NULL;
    if(key == node->key)
        return node;
    else if(key < node->key)
        return search1(node->left, key);
    else
        return search1(node->right, key);
}

// 반복적 방법
TreeNode *search2(TreeNode *node, int key)
{
    while(node != NULL)
    {
        if(key = node->key)
            return node;
        else if(key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return NULL;
}

//////////////////////////////////////////////insert//////////////////////////////////////////////
// 이진 탐색 트리에 원소를 삽입하기 위해서는 먼저 탐색을 수행하는 것이 필요
// 탐색에 실패한 위치가 바로 새로운 노드를 삽입하는 위치

// key를 이진 탐색 트리 root에 삽입한다.
// key가 이미 root안에 있으면 삽입되지 않는다.
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t; // p는 부모노드, t는 현재 노드
    TreeNode *n;     // n은 새로운 노드
    t = *root;
    p = NULL;
    while(t != NULL)
    {
        if(key == t->key)
            return;
        p = t;
        if(key < p->key)
            t = p->left;
        else
            t = p->right;
    }
    // key가 없으므로 삽입 가능
    n = (TreeNode *)malloc(sizeof(TreeNode));
    if(n == NULL)
        return;
    n->key = z;
    n->left = n->right = NULL;

    if(p != NULL)
    {
        if(key < p->key)
            p->left = n;
        else
            p->right = n;
    }
    else
        *root = n;
}

//////////////////////////////////////////////delete//////////////////////////////////////////////
// 세 가지 경우를 고려하여야 한다.
// CASE 1. 삭제하려는 노드가 단말 노드일 경우
// CASE 2. 삭제하려는 노드가 왼쪽이나 오른쪽 서브 트리 중 하나만 가지고 있는 경우
// CASE 3. 삭제하려는 노드가 두개의 서브 트리 모두 가지고 있는 경우
void delete_node(TreeNode **root, int key)
{
    // key를 갖는 노드 t를 탐색, p는 t의 부모노드
    TreeNode *p, *child, *t, *pp;
    p = NULL;
    t = *root;

    // key를 갖는 노드 t를 탐색한다.
    while(t != NULL && t->key != key)
    {
        p = t;
        t = (key < t->key) ? t->left : t->right;
    }

    // 탐색이 종료된 시점에 t가 NULL이면 트리 안에 key가 없음
    if(t == NULL)
    {
        printf("key is not int the tree");
        return;
    }

    // CASE 1. 단말노드인 경우
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

    // CASE 2. 하나의 자식만 가지는 경우
    else if((t->left) == NULL || (t->right == NULL))
    {
        child = (t->left != NULL) ? t-?left : t->right;
        if(p != NULL)
        {
            if(p->left == t)
                p->left = child;
            else
                p->right = child;
        }
        else
            *root = child;
    }

    // CASE 3. 두 개의 자식을 가지는 경우
    else
    {
        child = t->right;
        while(child->left != NULL)
        {
            pp = child;
            child = child->left;
        }

        t->key = child->key;
        if(child->right == NULL)
            p->left = NULL;
        else
            p->left = child->right;
    }
}


int main()
{
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    // input, output 파일 열기
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // 파일 열기 실패 시
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "파일 열기 실패\n");
        exit(1);
    }


    int cnt = 0;
    while(1)
    {
        cnt += 1;

        fscanf(file_input, "%c%d", &x, &y);
        switch(x)
        {
            case 'i':
                insert_node(&root, y);
                break;
            case 'd':
                delete_node(&root, y)
                break;
            case 's':


                break;
            default :
                printf("%d줄의 입력 형식이 잘못되었습니다.", cnt);
        }

        TreeNode n1 = {1, NULL, NULL};
        insert_node_last(list, coef, expon); // list[0]에 coef, expon 대입
    }

    fclose(file_input);

    return 0;
}



