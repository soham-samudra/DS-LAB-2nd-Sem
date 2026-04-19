#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};
struct TreeNode* createNode(int val) {
struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
newNode->val = val;
newNode->left = newNode->right = NULL;
return newNode;
}

struct TreeNode* insertNode(struct TreeNode* root, int val) {
if (root == NULL) {
return createNode(val);
}

if (val < root->val) {
root->left = insertNode(root->left, val);
} else {
root->right = insertNode(root->right, val);
}

return root;
}


void inorderTraversal(struct TreeNode* root) {
if (root == NULL) {
printf("The tree is empty");
return;
}

if (root->left != NULL)
inorderTraversal(root->left);

printf("%d ", root->val);

if (root->right != NULL)
inorderTraversal(root->right);
}


void preorderTraversal(struct TreeNode* root) {
if (root == NULL) {
printf("The tree is empty");
return;
}

printf("%d ", root->val);

if (root->left != NULL)
preorderTraversal(root->left);

if (root->right != NULL)
preorderTraversal(root->right);
}


void postorderTraversal(struct TreeNode* root) {
if (root == NULL) {
printf("The tree is empty");
return;
}

if (root->left != NULL)
postorderTraversal(root->left);

if (root->right != NULL)
postorderTraversal(root->right);

printf("%d ", root->val);
}


struct TreeNode* findMin(struct TreeNode* root) {
while (root->left != NULL) {
root = root->left;
}
return root;
}


struct TreeNode* deleteNode(struct TreeNode* root, int val, int* found) {
if (root == NULL) {
return NULL;
}

if (val < root->val) {
root->left = deleteNode(root->left, val, found);
    } 
else if (val > root->val) {
root->right = deleteNode(root->right, val, found);
} 
else {
	*found = 1;

// Case 1: No child
if (root->left == NULL && root->right == NULL) {
free(root);
return NULL;
}

// Case 2: One child
else if (root->left == NULL) {
struct TreeNode* temp = root->right;
free(root);
return temp;
} 
else if (root->right == NULL) {
struct TreeNode* temp = root->left;
free(root);
return temp;
}

// Case 3: Two children
struct TreeNode* temp = findMin(root->right);
root->val = temp->val;
root->right = deleteNode(root->right, temp->val, found);
}

return root;
}

// Free entire tree
void freeTree(struct TreeNode* root) {
if (root == NULL) return;
freeTree(root->left);
freeTree(root->right);
free(root);
}

int main() {
    struct TreeNode* root = NULL;
    int choice, data;

    while (1) {
        printf("1. Insert Node\n");
        printf("2. In-Order Traversal\n");
        printf("3. Pre-Order Traversal\n");
        printf("4. Post-Order Traversal\n");
        printf("5. Delete Node\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Data: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;

            case 2:
                inorderTraversal(root);
                printf("\n");
                break;

            case 3:
                preorderTraversal(root);
                printf("\n");
                break;

            case 4:
                postorderTraversal(root);
                printf("\n");
                break;

            case 5: {
                printf("Delete: ");
                scanf("%d", &data);
                int found = 0;
                root = deleteNode(root, data, &found);
                if (!found) {
                    printf("Value not found\n");
                }
                break;
            }

            case 6:
                freeTree(root);
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
