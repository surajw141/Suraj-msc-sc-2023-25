#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct Node
{
    int data;
    struct Node *next;
};

// Function to create a linked list with n nodes
void createNodeList(int n)
{
    struct Node *head = NULL;
    struct Node *tail = NULL;

    // Create n nodes and add them to the linked list
    for (int i = 1; i <= n; ++i)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        if (newNode == NULL)
        {
            printf("Memory allocation failed.\n");
            return;
        }

        printf("Enter data for node %d: ", i);
        scanf("%d", &newNode->data);
        newNode->next = NULL;

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Display the data entered in the linked list
    printf("\nData entered in the list:\n");
    struct Node *current = head;
    while (current != NULL)
    {
        printf("Data = %d\n", current->data);
        current = current->next;
    }

    // Clean up memory (not shown in this snippet)
}

int main()
{
    int n;
    printf("Enter the number of nodes (e.g., 10): ");
    scanf("%d", &n);
    createNodeList(n);
    return 0;
}
