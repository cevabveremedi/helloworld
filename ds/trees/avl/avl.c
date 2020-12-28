#include<stdio.h>
#include<stdlib.h>

typedef struct tree
{
    int val;
    struct tree* left, *right;
}tNode;

#define MAX 999999
#define MIN -999999

tNode* newNode(int data);
void inorderDisplay(tNode* root);
int height(tNode* root);
int checkBalanced(tNode* root);
int isBST(tNode* root, int min, int max);
tNode* createNormal(tNode* root, int data);
tNode* createAvl(tNode* root, int data);
tNode* balance(tNode* root);
tNode* rightRotate(tNode* root);
tNode* leftRotate(tNode* root);
void burnTree(tNode* root);

int main(void)
{
    tNode* normalRoot = NULL;
    tNode* avlRoot = NULL;
    for(int i = 1; i<= 24; i++)
    {
        normalRoot = createNormal(normalRoot, i);
        avlRoot = createAvl(avlRoot, i);
    }
    printf("NORMAL:\n");
    printf("isBST: %d  isBalanced: %d\n", isBST(normalRoot, MIN, MAX), checkBalanced(normalRoot));
    inorderDisplay(normalRoot);
    printf("\nAVL:\n");
    printf("isBST: %d  isBalanced: %d\n", isBST(avlRoot, MIN, MAX), checkBalanced(avlRoot));
    inorderDisplay(avlRoot); printf("\n");
    burnTree(avlRoot);
    burnTree(normalRoot);
}

tNode* newNode(int data)
{
    tNode* temp = malloc(sizeof(tNode)*1);
    temp->left = temp->right = NULL;
    temp->val = data;
    return temp;
}

void inorderDisplay(tNode* root)
{
    if(!root) return;
    inorderDisplay(root->left);
    printf("%d, ", root->val);
    inorderDisplay(root->right);
}

int height(tNode* root)
{
    if(root == NULL) return 0;
    int L = height(root->left);
    int R = height(root->right);
    return (L > R) ? L+1 : R+1;
}

int checkBalanced(tNode* root)
{
    if(root == NULL) return 1;

    int L = height(root->left);
    int R = height(root->right);
    
    if(abs(L - R) <= 1)
    {
        if(checkBalanced(root->left) && checkBalanced(root->right))
        {
            return 1;
        }
    }
    return 0;
}

int isBST(tNode* root, int min, int max)
{
    if(!root) return 1;
    if(root->val < min || root->val > max)
    {
        return 0;
    }
    int L = isBST(root->left, min, root->val);
    if(L != 1) return 0;
    return isBST(root->right, root->val, max);
}

tNode* createNormal(tNode* root, int data)
{
    if(!root)
    {
        root = newNode(data);
        return root;
    }

    tNode* curr, *ret;
    curr = ret = root;

    while(root)
    {
        curr = root;
        if(data < root->val)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }

    if(curr->val < data)
    {
        curr->right = newNode(data);
    }
    else
    {
        curr->left = newNode(data);
    }
    return ret;
}

tNode* createAvl(tNode* root, int data)
{
    root = createNormal(root, data);
    while(!checkBalanced(root))
    {
        root = balance(root);
    }
    return root;
}

tNode* balance(tNode* root)
{
    if(checkBalanced(root))
    {
        return root;
    }
    if(!checkBalanced(root->left))
    {
        root->left =  balance(root->left);
    }
    if(!checkBalanced(root->right))
    {
        root->right = balance(root->right);
    }
    int L = height(root->left);
    int R = height(root->right);
    if(L > R)
    {
        root = rightRotate(root);
    }
    else
    {
        root = leftRotate(root);
    }
    return root;
}

tNode* rightRotate(tNode* root)
{
    if(!root->left) return root;
    if(!root->left->left)
    {
        root->left = leftRotate(root->left);
    }
    tNode* kid = root->left;
    root->left = kid->right;
    kid->right = root;
    return kid;
}

tNode* leftRotate(tNode* root)
{
    if(!root->right) return root;
    if(!root->right->right)
    {
        root->right = rightRotate(root->right);
    }
    tNode* kid = root->right;
    root->right = kid->left;
    kid->left = root;
    return kid;
}

void burnTree(tNode* root)
{
    if(!root) return;
    burnTree(root->left);
    burnTree(root->right);
    free(root);
}