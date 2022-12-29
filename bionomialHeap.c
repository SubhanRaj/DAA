// Implementation of Bionomial Heap Operations in C Language

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int data;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *sibling;
} node;

node *head = NULL;

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
    {
        // handle error, for example by printing an error message
        // and returning NULL
        printf("Error: failed to allocate memory for new node\n");
        return NULL;
    }
    newNode->data = data;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

node *merge(node *h1, node *h2)
{
    if (h1 == NULL)
    {
        return h2;
    }
    if (h2 == NULL)
    {
        return h1;
    }
    node *res = NULL;
    if (h1->degree <= h2->degree)
    {
        res = h1;
        res->sibling = merge(h1->sibling, h2);
    }
    else
    {
        res = h2;
        res->sibling = merge(h1, h2->sibling);
    }
    return res;
}
void linkNodes(node *y, node *z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

node *unionBionomialHeap(node *h1, node *h2)
{
    if (h1 == NULL && h2 == NULL)
    {
        return NULL;
    }
    node *res = merge(h1, h2);
    node *prev = NULL, *curr = res, *next = res->sibling;
    while (next != NULL)
    {
        if ((curr->degree != next->degree) || ((next->sibling != NULL) && (next->sibling)->degree == curr->degree))
        {
            prev = curr;
            curr = next;
        }
        else
        {
            if (curr->data <= next->data)
            {
                curr->sibling = next->sibling;
                linkNodes(next, curr);
            }
            else
            {
                if (prev == NULL)
                {
                    res = next;
                }
                else
                {
                    prev->sibling = next;
                }
                linkNodes(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return res;
}

node *insert(node *head, int data)
{
    node *newNode = createNode(data);
    if (newNode == NULL)
    {
        // handle error, for example by printing an error message
        // and returning the original head
        printf("Error: failed to insert new node\n");
        return head;
    }
    return unionBionomialHeap(head, newNode);
}

void display(node *h)
{
    while (h)
    {
        printf("%d ", h->data);
        display(h->child);
        h = h->sibling;
    }
}

int revertList(node *h)
{
    if (h->sibling)
    {
        revertList(h->sibling);
        (h->sibling)->sibling = h;
    }
    else
    {
        head = h;
    }
}

node *extractMinBionomialHeap(node *h)
{
    if (h == NULL)
    {
        return NULL;
    }
    node *minNodePrev = NULL;
    node *minNode = h;
    int min = h->data;
    node *curr = h;
    node *prev = NULL;
    while (curr->sibling != NULL)
    {
        if ((curr->sibling)->data < min)
        {
            min = (curr->sibling)->data;
            minNodePrev = prev;
            minNode = curr->sibling;
        }
        prev = curr;
        curr = curr->sibling;
    }
    if (minNodePrev == NULL && minNode->sibling == NULL)
    {
        h = NULL;
    }
    else if (minNodePrev == NULL)
    {
        h = minNode->sibling;
    }
    else
    {
        minNodePrev->sibling = minNode->sibling;
    }
    if (minNode->child != NULL)
    {
        revertList(minNode->child);
        (minNode->child)->sibling = NULL;
    }
    return unionBionomialHeap(h, head);
}

node *findNode(node *h, int data)
{
    if (h == NULL)
    {
        return NULL;
    }
    if (h->data == data)
    {
        return h;
    }
    node *res = findNode(h->child, data);
    if (res != NULL)
    {
        return res;
    }
    return findNode(h->sibling, data);
}

node *decreaseKeyBionomialHeap(node *h, int oldData, int newData)
{
    node *nodeToDec = findNode(h, oldData);
    if (nodeToDec == NULL)
    {
        return h;
    }
    nodeToDec->data = newData;
    node *parent = nodeToDec->parent;
    while (parent != NULL && nodeToDec->data < parent->data)
    {
        int temp = nodeToDec->data;
        nodeToDec->data = parent->data;
        parent->data = temp;
        nodeToDec = parent;
        parent = parent->parent;
    }
    return h;
}

node *deleteKeyBionomialHeap(node *h, int data)
{
    if (h == NULL)
    {
        return NULL;
    }
    h = decreaseKeyBionomialHeap(h, data, INT_MIN);
    return extractMinBionomialHeap(h);
}
void freeBionomialHeap(node *h)
{
    if (h == NULL)
    {
        return;
    }
    node *curr = h;
    while (curr != NULL)
    {
        freeBionomialHeap(curr->child);
        node *temp = curr;
        curr = curr->sibling;
        free(temp);
    }
}
int main()
{
    int choice, data, oldData, newData;
    while (1)
    {
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Extract Min\n");
        printf("4. Decrease Key\n");
        printf("5. Delete Key\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter the data: ");
            scanf("%d", &data);
            head = insert(head, data);
            break;
        case 2:
            display(head);
            printf("");
            break;
        case 3:
            head = extractMinBionomialHeap(head);
            break;
        case 4:
            printf("Enter the old data: ");
            scanf("%d", &oldData);
            printf("Enter the new data: ");
            scanf("%d", &newData);
            head = decreaseKeyBionomialHeap(head, oldData, newData);
            break;
        case 5:
            printf("Enter the data: ");
            scanf("%d", &data);
            head = deleteKeyBionomialHeap(head, data);
            break;
        case 6:
            freeBionomialHeap(head);
            head = NULL;
            exit(0);
        default:
            printf("Invalid choice\n");
        }
        printf("");
    }
    return 0;
}
