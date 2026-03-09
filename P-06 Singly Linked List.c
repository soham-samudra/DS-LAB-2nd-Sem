#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct LinkedList{
    struct Node* head;
    int size;
};

struct Node* createNode(int value){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if(node == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    node->data = value;
    node->next = NULL;

    return node;
}

struct LinkedList* initializeList(){
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));

    if(list == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    list->head = NULL;
    list->size = 0;

    return list;
}

void insert(struct LinkedList* list, int data, int position){

    if(position < 0 || position > list->size){
        printf("Invalid position\n");
        return;
    }

    struct Node* newNode = createNode(data);

    if(position == 0){
        newNode->next = list->head;
        list->head = newNode;
    }
    else{
        struct Node* temp = list->head;

        int i = 0;
        while(i < position - 1){
            temp = temp->next;
            i++;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    list->size++;

    printf("Element %d inserted at position %d\n", data, position);
}

void deleteNode(struct LinkedList* list, int position){

    if(position < 0 || position >= list->size){
        printf("Invalid position\n");
        return;
    }

    struct Node* temp;

    if(position == 0){
        temp = list->head;
        list->head = temp->next;
    }
    else{
        struct Node* ptr = list->head;

        int i = 0;
        while(i < position - 1){
            ptr = ptr->next;
            i++;
        }

        temp = ptr->next;
        ptr->next = temp->next;
    }

    free(temp);
    list->size--;

    printf("Element at position %d deleted\n", position);
}

void reverse(struct LinkedList* list){

    struct Node* previous = NULL;
    struct Node* current = list->head;
    struct Node* nextNode = NULL;

    while(current != NULL){
        nextNode = current->next;
        current->next = previous;
        previous = current;
        current = nextNode;
    }

    list->head = previous;
}

void display(struct LinkedList* list){

    struct Node* temp = list->head;

    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

void displayReversed(struct LinkedList* list){

    struct Node* temp = list->head;

    while(temp != NULL){
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}

int main(){

    int num_elements;

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &num_elements);

    struct LinkedList* list = initializeList();

    int data;

    printf("Enter the elements:\n");

    for(int i = 0; i < num_elements; i++){
        scanf("%d", &data);
        insert(list, data, i);
    }

    int choice, position;

    while(1){

        printf("Linked List Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Reverse\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch(choice){

            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);

                printf("Enter position to insert: ");
                scanf("%d", &position);

                insert(list, data, position);
                break;

            case 2:
                printf("Enter position to delete: ");
                scanf("%d", &position);

                deleteNode(list, position);
                break;

            case 3:
                reverse(list);
                printf("Reversed List: ");
                displayReversed(list);
                reverse(list);
                break;

            case 4:
                printf("Linked List: ");
                display(list);
                break;

            case 5:
                printf("Exiting program\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}