typedef struct node
{
    int number;
    struct node *prev;
    struct node *next;
}node;

extern node *Head;
extern int totalNode;

node * getNode(int x);
int insertNode(int position, int data);
void displayList(void);
void displayListReverse(void);
int deleteNode(int position);
void invertList(void);
void changePosition(void);
void showElement(int oldPos);
void freeList(void);