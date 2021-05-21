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


// ������ ����� ��ȸ��
// ������ȸ preorder
// ������ȸ inorder
// ������ȸ postorder

// ť�� ����� ��ȸ��
// ���� ��ȸ level_order

//////////////////////////////////////////////search//////////////////////////////////////////////
// ��ȯ�� ���
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

// �ݺ��� ���
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
// ���� Ž�� Ʈ���� ���Ҹ� �����ϱ� ���ؼ��� ���� Ž���� �����ϴ� ���� �ʿ�
// Ž���� ������ ��ġ�� �ٷ� ���ο� ��带 �����ϴ� ��ġ

// key�� ���� Ž�� Ʈ�� root�� �����Ѵ�.
// key�� �̹� root�ȿ� ������ ���Ե��� �ʴ´�.
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t; // p�� �θ���, t�� ���� ���
    TreeNode *n;     // n�� ���ο� ���
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
    // key�� �����Ƿ� ���� ����
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
// �� ���� ��츦 ����Ͽ��� �Ѵ�.
// CASE 1. �����Ϸ��� ��尡 �ܸ� ����� ���
// CASE 2. �����Ϸ��� ��尡 �����̳� ������ ���� Ʈ�� �� �ϳ��� ������ �ִ� ���
// CASE 3. �����Ϸ��� ��尡 �ΰ��� ���� Ʈ�� ��� ������ �ִ� ���
void delete_node(TreeNode **root, int key)
{
    // key�� ���� ��� t�� Ž��, p�� t�� �θ���
    TreeNode *p, *child, *t, *pp;
    p = NULL;
    t = *root;

    // key�� ���� ��� t�� Ž���Ѵ�.
    while(t != NULL && t->key != key)
    {
        p = t;
        t = (key < t->key) ? t->left : t->right;
    }

    // Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� key�� ����
    if(t == NULL)
    {
        printf("key is not int the tree");
        return;
    }

    // CASE 1. �ܸ������ ���
    if((t->left == NULL) && (t->right == NULL))
    {
        if(p != NULL)
        {
            // �θ����� �ڽ��ʵ带 NULL�� �����.
            if(p->left == t)
                p->left = NULL;
            else
                p->right = NULL;
        }
        else
            *root = NULL;
    }

    // CASE 2. �ϳ��� �ڽĸ� ������ ���
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

    // CASE 3. �� ���� �ڽ��� ������ ���
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
    // input, output ���� ����
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // ���� ���� ���� ��
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "���� ���� ����\n");
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
                printf("%d���� �Է� ������ �߸��Ǿ����ϴ�.", cnt);
        }

        TreeNode n1 = {1, NULL, NULL};
        insert_node_last(list, coef, expon); // list[0]�� coef, expon ����
    }

    fclose(file_input);

    return 0;
}



