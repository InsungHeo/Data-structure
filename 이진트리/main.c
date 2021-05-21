#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left, *right;
} TreeNode;
//              +
//      *               +
//  1       4       16      25
TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, NULL, NULL};
TreeNode n3 = {'*', &n1, &n2};
TreeNode n4 = {16, NULL, NULL};
TreeNode n5 = {25, NULL, NULL};
TreeNode n6 = {'+', &n4, &n5};
TreeNode n7 = {'+', &n3, &n6};
TreeNode *exp = &n7;


// 스택을 사용한 순회법
// 전위순회 preorder
// 중위순회 inorder
// 후위순회 postorder

// 큐를 사용한 순회법
// 레벨 순회 level_order
int evaluate(TreeNode *root)
{
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right == NULL)
        return root->data;
    int op1 = evaluate(root->left);
    int op2 = evaluate(root->right);
    switch(root->data)
    {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
    }
}


int main()
{
    printf("%d", evaluate(exp));

    return 0;
}
