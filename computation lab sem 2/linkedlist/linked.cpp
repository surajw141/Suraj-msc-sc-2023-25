#include <bits/stdc++.h>

struct node
{
    int data;
    node *next;
};

int main()
{
    struct node *head;
    head = data = 0;
    struct node *tail;
    tail = data = 0;
    head = next = tail;
    Tail = next = NULL;
}

/*
pointer
variable -> cariable
int a = 10
int *p = &a;
*/

node *head;
head = data = 0;
for (int i = 1, i < 10; i++)
{
    node *new_node = new node;
    new_node->data = i;
    new_node->next = head;
    head = new_node;
}

// print linked list)