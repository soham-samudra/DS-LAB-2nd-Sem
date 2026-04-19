#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

typedef struct node *NODE;

// Create a new node with given data
NODE createNodeInCLL(int data) {
    NODE temp = (NODE) malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Create CLL with n nodes
NODE createCLL(int n) {
NODE first = NULL, temp, last;
int x;

if (n <= 0)
return NULL;

scanf("%d", &x);
first = createNodeInCLL(x);
last = first;

for (int i = 2; i <= n; i++) {
scanf("%d", &x);
temp = createNodeInCLL(x);
last->next = temp;
last = temp;
}

last->next = first; // circular link
return first;

}

// Traverse CLL
void traverseListInCLL(NODE first) {
 NODE temp = first;

if (first == NULL)
return;

do {
printf("%d -> ", temp->data);
temp = temp->next;
} while (temp != first);

printf("\n");

}

// Insert at given position in CLL
NODE insertAtPositionInCLL(NODE first, int pos, int x) {
NODE temp = createNodeInCLL(x);

if (pos == 1) {
if (first == NULL) {
temp->next = temp;
return temp;
}

NODE last = first;
while (last->next != first)
last = last->next;

temp->next = first;
last->next = temp;
return temp;
}

NODE cur = first;
for (int i = 1; i < pos - 1; i++) {
cur = cur->next;
if (cur == first) {
printf("Position not found\n");
return first;
}
}

temp->next = cur->next;
cur->next = temp;
return first;
}

// Delete node at given position in CLL
NODE deleteAtPositionInCLL(NODE first, int pos) {
 if (first == NULL)
return NULL;

NODE temp = first, prev = NULL;

if (pos == 1) {
if (first->next == first) {
printf("Deleted element: %d\n", first->data);
free(first);
return NULL;
}

NODE last = first;
while (last->next != first)
last = last->next;

printf("Deleted element: %d\n", first->data);
last->next = first->next;
NODE newFirst = first->next;
free(first);
return newFirst;
}

for (int i = 1; i < pos; i++) {
prev = temp;
temp = temp->next;

if (temp == first) {
printf("Position not found\n");
return first;
}
}

prev->next = temp->next;
printf("Deleted element: %d\n", temp->data);
free(temp);
return first;
}

// Reverse CLL
NODE reverseCLL(NODE first) {
 if (first == NULL || first->next == first)
return first;

NODE prev = NULL, current = first, next;
NODE last = first;

while (last->next != first)
last = last->next;

do {
next = current->next;
current->next = prev;
prev = current;
current = next;
} while (current != first);

first->next = prev;
first = prev;

return first;
}

// Concatenate two CLLs
NODE concatCLL(NODE first, NODE second) {
if (first == NULL)
return second;
if (second == NULL)
return first;

NODE temp1 = first;
while (temp1->next != first)
temp1 = temp1->next;

NODE temp2 = second;
while (temp2->next != second)
temp2 = temp2->next;

temp1->next = second;
temp2->next = first;

return first;

}

int main() {
    NODE first = NULL, second = NULL;
    int x, pos, op, n;

    while (1) {
        printf("1.Create 2.Insert 3.Delete 4.Display 5.Reverse 6.Concat 7.Exit\n");
        printf("choice: ");
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("How many nodes? ");
                scanf("%d", &n);
                first = createCLL(n);
                break;
            case 2:
                printf("Position: ");
                scanf("%d", &pos);
                if (pos <= 0) {
                    printf("Position not found\n");
                } else {
                    printf("Element: ");
                    scanf("%d", &x);
                    first = insertAtPositionInCLL(first, pos, x);
                }
                break;
            case 3:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    printf("Position: ");
                    scanf("%d", &pos);
                    first = deleteAtPositionInCLL(first, pos);
                }
                break;
            case 4:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    printf("Elements in CLL are: ");
                    traverseListInCLL(first);
                }
                break;
            case 5:
                if (first == NULL) {
                    printf("CLL is empty\n");
                } else {
                    first = reverseCLL(first);
                    printf("CLL reversed\n");
                    traverseListInCLL(first);   // <-- display reversed list
                }
                break;
            case 6:
                printf("Creating second CLL to concatenate...\n");
                printf("How many nodes in second CLL? ");
                scanf("%d", &n);
                second = createCLL(n);
                first = concatCLL(first, second);
                printf("Concatenated CLL:\n");
                traverseListInCLL(first);
                break;
            case 7:
                exit(0);
        }
    }
}
