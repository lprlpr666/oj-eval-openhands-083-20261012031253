#include <stdio.h>
#include <stdlib.h>

// Node structure for singly circular linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

// Build circular linked list with n nodes (1 to n)
Node* buildList(int n) {
    if (n <= 0) return NULL;
    
    Node* head = createNode(1);
    Node* current = head;
    
    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);
        current = current->next;
    }
    
    // Make it circular
    current->next = head;
    return head;
}

// Remove the m-th node starting from current position
// Returns the removed node's value and updates head to the next starting position
int removeMthNode(Node** headRef, int m, int* size) {
    if (*headRef == NULL || *size == 0) return -1;
    
    // If only one node left
    if (*size == 1) {
        int value = (*headRef)->data;
        free(*headRef);
        *headRef = NULL;
        *size = 0;
        return value;
    }
    
    // Find the node before the one to be removed
    Node* prev = *headRef;
    
    // Move (m-2) steps to find the node before the one to remove
    // For m=1, we need to move (size-1) steps to find the node before head
    int steps = (m - 2) % (*size);
    if (steps < 0) steps += *size;
    
    for (int i = 0; i < steps; i++) {
        prev = prev->next;
    }
    
    // The node to remove is prev->next
    Node* toRemove = prev->next;
    int value = toRemove->data;
    
    // Remove the node
    prev->next = toRemove->next;
    
    // Update head if we removed the head
    if (toRemove == *headRef) {
        *headRef = toRemove->next;
    }
    
    free(toRemove);
    (*size)--;
    
    // The new starting point is the node after the removed one
    *headRef = prev->next;
    
    return value;
}

// Free all nodes in the circular list
void freeList(Node* head, int size) {
    if (head == NULL) return;
    
    Node* current = head;
    Node* nextNode = NULL;
    
    // Break the circle to avoid infinite loop
    for (int i = 0; i < size; i++) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 1;
    
    Node* head = buildList(n);
    int size = n;
    
    // Simulate the Josephus Ring process
    while (size > 0) {
        int removed = removeMthNode(&head, m, &size);
        printf("%d\n", removed);
    }
    
    return 0;
}