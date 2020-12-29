    #include<stdlib.h>
    #include<stdio.h>

    typedef struct TreeNode
    {
        int val;
        struct TreeNode *left, *right;
    }treeNode;

    int height(treeNode* root);
    void display(treeNode* root);
    treeNode* newNode(int data);
    treeNode* createTree(treeNode* root, int data);
    int isBST(treeNode* root, int min, int max);
    int isBalanced(treeNode* root);
    treeNode* makeBalanced(treeNode* root);
    void numofNodes(treeNode* root, int* count);
    void getNodes(treeNode* root, treeNode** array, int* element);
    treeNode* arrayToBST(treeNode** array, int first, int last);
    void burnTree(treeNode* root);

    int main(void)
    {
        treeNode* root = NULL;
        for(int i = 1; i<16; i++)
        {
            root = createTree(root, i);
        }
        display(root);
        printf("\nisBST: %d\tHeight: %d\tisBalanced: %d\n\n", 
                isBST(root, -100, 100), height(root), isBalanced(root));

        root = makeBalanced(root);
        display(root);
        printf("\nisBST: %d\tHeight: %d\tisBalanced: %d\n", 
                isBST(root, -100, 100), height(root), isBalanced(root));
                
        burnTree(root);
        root = NULL;
    }

    void display(treeNode* root)
    {
        if(!root) return;
        if(root->left) display(root->left);
        printf("[ %d ]", root->val);
        if(root->right) display(root->right);
        return;
    }

    treeNode* newNode(int data)
    {
        treeNode* temp = malloc(sizeof(treeNode)*1);
        temp->val = data;
        temp->left = temp->right = NULL;
        return temp;
    }

    treeNode* createTree(treeNode* root, int data)
    {
        if(!root)
        {
            root = newNode(data);
            return root;
        }

        treeNode *curr, *temp;
        curr = temp = root;
        while(temp)
        {
            curr = temp;
            if(data > temp->val)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
        if(data > curr->val)
        {
            curr->right = newNode(data);
        }
        else
        {
            curr->left = newNode(data);
        }

        return root;
    }

    int isBST(treeNode* root, int min, int max)
    {
        if(!root) return 1;
        if(root->val <= min || root->val >= max) return 0;
        int L = isBST(root->left, min, root->val);
        if(L == 0) return 0;
        return isBST(root->right, root->val, max);
    }

    int height(treeNode* root)
    {
        if(!root) return 0;
        int L = height(root->left);
        int R = height(root->right);
        return (L > R) ? (L+1) : (R+1);
    }

    int isBalanced(treeNode* root)
    {
        if(!root) return 1;
        int L = height(root->left);
        int R = height(root->right);
        if(abs(L-R) <= 1)
        {
            if(isBalanced(root->left) && isBalanced(root->right))
            {
                return 1;
            }
        }
        return 0;
    }

    treeNode* makeBalanced(treeNode* root)
    {
        int count = 0;
        numofNodes(root, &count);
        treeNode** nodeArray = malloc(sizeof(treeNode*)*count);
        count = 0;
        getNodes(root, nodeArray, &count);
        root = arrayToBST(nodeArray, 0, count-1);
        free(nodeArray);
        return root;
    }

    void numofNodes(treeNode* root, int* count)
    {
        if(root == NULL) return;
        numofNodes(root->left, count);
        numofNodes(root->right, count);
        (*count)++;
        return;
    }

    void getNodes(treeNode* root, treeNode** array, int* element)
    {
        if(!root) return;
        getNodes(root->left, array, element);
        array[(*element)++] = root;
        getNodes(root->right, array, element);
        return;
    }

    treeNode* arrayToBST(treeNode** array, int first, int last)
    {
        if(first > last) return NULL;
        int mid = (first + last)/2;
        treeNode* root = array[mid];
        root->left = arrayToBST(array, first, mid-1);
        root->right = arrayToBST(array, mid+1, last);
        return root;
    }

    void burnTree(treeNode* root)
    {
        if(!root) return;
        if(root->left) burnTree(root->left);
        if(root->right) burnTree(root->right);
        free(root);
        return;
    }