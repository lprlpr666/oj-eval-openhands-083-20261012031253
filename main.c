#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int val) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

Node* buildList(int n) {
    if (n <= 0) return NULL;
    
    Node* head = createNode(1);
    if (!head) return NULL;
    Node* current = head;
    
    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);
        if (!current->next) return NULL;
        current = current->next;
    }
    
    current->next = head;
    return head;
}

int removeMthNode(Node** headRef, int m, int* size) {
    if (*headRef == NULL || *size == 0) return -1;
    
    if (*size == 1) {
        int value = (*headRef)->data;
        free(*headRef);
        *headRef = NULL;
        *size = 0;
        return value;
    }
    
    Node* prev = *headRef;
    int steps = (m - 2) % (*size);
    if (steps < 0) steps += *size;
    
    for (int i = 0; i < steps; i++) {
        prev = prev->next;
    }
    
    Node* toRemove = prev->next;
    int value = toRemove->data;
    
    prev->next = toRemove->next;
    
    if (toRemove == *headRef) {
        *headRef = toRemove->next;
    }
    
    free(toRemove);
    (*size)--;
    
    *headRef = prev->next;
    
    return value;
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 1;
    
    Node* head = buildList(n);
    if (!head && n > 0) return 1;
    
    int size = n;
    
    while (size > 0) {
        int removed = removeMthNode(&head, m, &size);
        printf("%d\n", removed);
    }
    
    return 0;
}