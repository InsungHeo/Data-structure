#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <math.h>
#define max(x, y) ((x >= y) ? (x):(y))

////////////////////////////////////////////////////////////////////////////////////
// TreeNode �ڷ��� ����.
// int index�� �ִٴ� ������ ����� �ٸ�. ����� index�� �� ��带 ���� ������ �ű� ������ ��Ÿ��.
typedef struct TreeNode
{
    int key;
    struct TreeNode *left, *right;
    int index;
} TreeNode;

////////////////////////////////////////////////////////////////////////////////////
// ���� Ʈ���� key���� �������� ���� ���θ� Ȯ���ϴ� �Լ�.
// does_exist�� �����Ͽ� key�� ���縦 ��Ÿ��.
// preorder ������ Ž���Ͽ� key ���� �߰��� ������ does_exist++
// does_exist�� 0�̸� Not Exist, 0�� �ƴϸ� Exist.
int does_exist = 0;
void search(TreeNode *root, int key)
{
    // ���� Ʈ���� ������� ���� ���.
    if(root != NULL)
    {
        if(root->key == key)
            does_exist += 1;

        search(root->left, key);
        search(root->right, key);
    }
}

////////////////////////////////////////////////////////////////////////////////////
// ���� Ʈ���� ��� index ���� key ���� �������ִ� �Լ�.
// preorder ������ index�� key�� ��������.
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
// ���� Ʈ���� ���Ҹ� �����ϴ� �Լ�.
// ���� Ʈ���� ���Ҹ� �����ϱ� ���ؼ��� ���� Ž���� �����ϴ� ���� �ʿ�.
// Ž���� ������ ��ġ�� ���ο� node�� ��ġ�� ����.
// key�� �̹� ���� Ʈ���� ������ left child�� ����.
void insert_node(TreeNode **root, int key)
{
    TreeNode *p, *t; // p�� �θ���, t�� ���� ���.
    TreeNode *n;     // n�� ���ο� ���.
    t = *root;
    p = NULL;

    // p�� �ܸ���尡 �ɶ����� ����.
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

    // ���� �߰��� node�� ���� �޸� �Ҵ�.
    n = (TreeNode *)malloc(sizeof(TreeNode));
    if(n == NULL)
        perror("�޸� �Ҵ� ����");

    // ���ο� node�� key, left, right �ʱ�ȭ.
    n->key = key;
    n->left = n->right = NULL;

    // �θ� ��尡 ������ ���.
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
    // �θ� ��尡 �������� ���� ���.
    else
    {
        *root = n;
        n->index = 1;
    }
}

////////////////////////////////////////////////////////////////////////////////////
// ���� Ʈ������ ���Ҹ� �����ϴ� �Լ�.
// ���� �� ���� case�� �����.
// CASE 1. �����Ϸ��� ��尡 �ܸ� ����� ���.
// CASE 2. �����Ϸ��� ��尡 �����̳� ������ ���� Ʈ�� �� �ϳ��� ������ �ִ� ���.
// CASE 3. �����Ϸ��� ��尡 �� ���� ���� Ʈ�� ��� ������ �ִ� ���.
void delete_node(TreeNode **root, int key)
{
    // key�� ���� ��� t�� Ž��, p�� t�� �θ���
    TreeNode *p, **child, *t, *tt, *pp;
    p = NULL;
    pp = NULL;
    t = *root;

    // key�� ���� ��� t�� Ž���Ѵ�.
    while(t != NULL && t->key != key)
    {
        p = t;
        t = (key < t->key) ? t->left : t->right;
    }

    // Ž���� ����� ������ t�� NULL�̸� Ʈ�� �ȿ� key�� ����.
    if(t == NULL)
    {
        does_exist = 'n';
        return;
    }


    // CASE 1. �ܸ������ ���.
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

    // CASE 2. �ϳ��� �ڽĸ� ������ ���.
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

    // CASE 3. �� ���� �ڽ��� ������ ���.
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
// ���� Ʈ���� ��忡 index�� �ο��ϴ� �Լ�.
// �Է� ���� node�� �ڽ� ��忡�Ե� index ���� �ο�.
// left child�� parent index�� 2��, rigth child�� parent index�� 2�� ���ϱ� 1.
void give_index(TreeNode *node, int index)
{
    TreeNode *t; // p�� �θ���, t�� ���� ���.
    node->index = index; // �Է� ���� node�� �Է� ���� index �ο�.
    t = node;
    if(t->left != NULL)
        give_index(t->left, 2*index);
    if(t->right != NULL)
        give_index(t->right, 2*index + 1);
}

////////////////////////////////////////////////////////////////////////////////////
// ���� Ʈ���� ���̸� return�ϴ� �Լ�.
// ���� Ʈ���� ���Ͽ� ��ȯȣ���Ͽ� �� �� �ִ��� �̿��� ���� ���.
int get_height(TreeNode *root)
{
    int height = 0;
    if(root)
        height = 1 + max(get_height(root->left), get_height(root->right));
    return height;
}

int main()
{
    // ���� Ʈ���� root ���� �� �ʱ�ȭ.
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root = NULL;

    // input, output ���� ����.
    FILE * file_input  = fopen( "input.txt", "r");
    FILE * file_output = fopen("output.txt", "w");

    // ���� ���� ���� �� exit.
    if(file_input == NULL || file_output == NULL)
    {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }

    int cnt = 0; // �Է� ���� node�� ���� üũ.
    char x[64]; // file_input���� 'i', 'd', 's'�� �Է� �޾� �����ϴ� �迭.
    int  y[64]; // file_input���� node�� key ���� �Է� �޾� �����ϴ� �迭.

    // file_input�� ���� ���� ������ �ݺ�.
    while(1)
    {
        // key�� ���� ���θ� üũ�ϴ� does_exist�� 0���� �ʱ�ȭ.
        does_exist = 0;

        // file_input �о����.
        fscanf(file_input, "%c%d", &x[cnt], &y[cnt]);

        // �Է��� 'i', 'd', 's' �� �����ΰ��� ���� �ٸ� �ڵ� ����.
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
                fprintf(file_output, "%d���� �Է� ������ �߸��Ǿ����ϴ�.\n", ++cnt);
                fgetc(file_input);
                continue;
        }
        fprintf(file_output, "%c%d : ", x[cnt++], y[cnt]);

        // 'i', 'd', 's' �� 's'�� 'd'�� �Է��� �� ���.
        if(does_exist == 'y')
            fprintf(file_output, "Exist\n");
        else if(does_exist == 'n')
            fprintf(file_output, "Not Exist\n");

        // 'i', 'd', 's' �� 'i'�� 'd'�� �Է��� �� ���.
        else
        {
            // node�� index ���� �����ϴ� �迭�� ���� �޸𸮸� �Ҵ� �� 0���� �ʱ�ȭ.
            int *arr = (int *)malloc(sizeof(int) * pow(2, get_height(root)));
            for(int i = 0; i < pow(2, get_height(root)) - 1; i++)
                arr[i] = 0;

            // ���� Ʈ���� ��� node�� index�� key ����.
            con_index_key(root, arr);

            // file_output�� ���Ŀ� �°� ���.
            for(int i = 0; i < pow(2, get_height(root)) - 1; i++)
            {
                fprintf(file_output, "%d", arr[i]);
                if(i != pow(2, get_height(root)) - 2)
                    fprintf(file_output, ", ");
            }
            fprintf(file_output, "\n");

            // arr�� �������� �Ҵ�� �޸� ����.
            free(arr);
        }

        // file_input�� �ִ� '\n'�� �����, file_input�� ���� �о��� �� ����.
        if(fgetc(file_input) == EOF)
            break;
    }
    // input, output ���� �ݱ�.
    fclose(file_input);
    fclose(file_output);

    return 0;
}
