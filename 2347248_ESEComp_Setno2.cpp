#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GardenNode
{
    int gardenId;
    char gardenName[50];
    float entryFee;
    struct GardenNode *next;
    struct GardenNode *left;  
    struct GardenNode *right; 
};

struct GardenNode *createNode(int id, char name[], float fee)
{
    struct GardenNode *newNode = (struct GardenNode *)malloc(sizeof(struct GardenNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->gardenId = id;
    strcpy(newNode->gardenName, name);
    newNode->entryFee = fee;
    newNode->next = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void displayNode(struct GardenNode *node)
{
    printf("Garden ID: %d\n", node->gardenId);
    printf("Garden Name: %s\n", node->gardenName);
    printf("Entry Fee: %.2f\n", node->entryFee);
    printf("\n");
}


struct GardenNode *linearSearch(struct GardenNode *front, const char name[])
{
    struct GardenNode *current = front;
    while (current != NULL)
    {
        if (strcmp(current->gardenName, name) == 0)
        {
            return current; 
        }
        current = current->next;
    }
    return NULL; 
}

void enqueue(struct GardenNode **front, struct GardenNode **rear, int id, char name[], float fee)
{
    struct GardenNode *newNode = createNode(id, name, fee);
    if (*rear == NULL)
    {
        *front = *rear = newNode;
    }
    else
    {
        (*rear)->next = newNode;
        *rear = newNode;
    }
}


void dequeue(struct GardenNode **front)
{
    if (*front == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    struct GardenNode *temp = *front;
    *front = (*front)->next;
    free(temp);
}


void displayQueue(struct GardenNode *front)
{
    struct GardenNode *current = front;
    while (current != NULL)
    {
        displayNode(current);
        current = current->next;
    }
}

void copyGardenIdsToArray(struct GardenNode *front, int *gardenIds, int *size)
{
    struct GardenNode *current = front;
    *size = 0;

    while (current != NULL)
    {
        gardenIds[*size] = current->gardenId;
        (*size)++;
        current = current->next;
    }
}


void merge(int arr[], int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;

    
    int L[n1], R[n2];

    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];

    
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        
        int middle = left + (right - left) / 2;

        
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        
        merge(arr, left, middle, right);
    }
}


void displaySortedGardenIds(int gardenIds[], int size)
{
    printf("Sorted Garden ID:\n");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", gardenIds[i]);
    }
    printf("\n");
}


struct GardenNode *insertBinaryTree(struct GardenNode *root, int id, char name[], float fee)
{
    struct GardenNode *newNode = createNode(id, name, fee);

    if (root == NULL)
    {
        root = newNode;
        return root;
    }

    struct GardenNode *current;
    struct GardenNode *parent;

    for (current = root; current != NULL;)
    {
        parent = current;

    
        if (current->left == NULL)
        {
            current->left = newNode;
            break;
        }
        else
        {
            current = current->left;
        }

        
        if (current->right == NULL)
        {
            current->right = newNode;
            break;
        }
        else
        {
            current = current->right;
        }
    }

    return root;
}

void inOrderTraversal(struct GardenNode *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        displayNode(root);
        inOrderTraversal(root->right);
    }
}

int main()
{
    struct GardenNode *front = NULL;
    struct GardenNode *rear = NULL;
    struct GardenNode *rootBinaryTree = NULL;
    int choice;
    int gardenIds[100]; 
    int gardenIdSize = 0;

    do
    {
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Search by Garden Name\n");
        printf("5. Copy Garden IDs to Array\n");
        printf("6. Merge Sort and Display Sorted Garden IDs\n");
        printf("7. Insert into Binary Tree\n");
        printf("8. Display Binary Tree in In-Order Traversal\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            int id;
            char name[50];
            float fee;

            printf("Enter Garden ID: ");
            scanf("%d", &id);
            printf("Enter Garden Name: ");
            scanf("%s", name);
            printf("Enter Entry Fee: ");
            scanf("%f", &fee);
           do{
            	printf("Minimum Fee should be Rs.25\n");
            	printf("Enter the fee:");
            	scanf("%f",&fee);
			}while(fee<25);

            enqueue(&front, &rear, id, name, fee);
            printf("Node enqueued successfully\n");
            break;
        }

        case 2:
            dequeue(&front);
            printf("Node dequeued successfully\n");
            break;

        case 3:
            displayQueue(front);
            break;

        case 4:
        {
            char searchName[50];
            printf("Enter Garden Name to search: ");
            scanf("%s", searchName);

            struct GardenNode *result = linearSearch(front, searchName);
            if (result != NULL)
            {
                printf("Node found:\n");
                displayNode(result);
            }
            else
            {
                printf("Node with Garden Name '%s' not found\n", searchName);
            }
            break;
        }

        case 5:
            copyGardenIdsToArray(front, gardenIds, &gardenIdSize);
            printf("Garden IDs copied to array successfully\n");
            break;

        case 6:
            if (gardenIdSize > 0)
            {
                mergeSort(gardenIds, 0, gardenIdSize - 1);
                displaySortedGardenIds(gardenIds, gardenIdSize);
            }
            else
            {
                printf("No Garden IDs to sort\n");
            }
            break;

        case 7:
        {
            int id;
            char name[50];
            float fee;

            printf("Enter Garden ID to insert into binary tree: ");
            scanf("%d", &id);
            printf("Enter Garden Name: ");
            scanf("%s", name);
            printf("Enter Entry Fee: ");
            scanf("%f", &fee);

            rootBinaryTree = insertBinaryTree(rootBinaryTree, id, name, fee);
            printf("Node inserted into binary tree successfully\n");
            break;
        }

        case 8:
            printf("Binary Tree In-Order Traversal:\n");
            inOrderTraversal(rootBinaryTree);
            printf("\n");
            break;

        case 9:
            printf("Exiting program\n");
            break;

        default:
            printf("Invalid choice, please try again\n");
        }

    } while (choice != 9);

    return 0;
}
