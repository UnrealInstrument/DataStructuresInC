#include <stdio.h>
#include <stdlib.h>

typedef struct Queue_RNode Queue_RNode;
struct Queue_RNode {
    int Data;
    Queue_RNode* Next;
};

typedef struct {
    Queue_RNode* Head;
    Queue_RNode* Tail;
    unsigned long Size;
} RQueue;

RQueue* Queue_Create() {
    RQueue* NewQueue = malloc(sizeof(RQueue));
    NewQueue->Head = NULL;
    NewQueue->Tail = NULL;
    NewQueue->Size = 0;
    return NewQueue;
}

Queue_RNode* Queue_CreateNode(int Data) {
    Queue_RNode* NewNode = malloc(sizeof(Queue_RNode));
    NewNode->Data = Data;
    NewNode->Next = NULL;
    return NewNode;
}

void Queue_Enqueue(RQueue* Queue, int Data) {
    Queue_RNode* NewNode = Queue_CreateNode(Data);
    if (Queue->Head == NULL) {
        Queue->Head = NewNode;
        Queue->Tail = NewNode;
    } else {
        Queue->Tail->Next = NewNode;
        Queue->Tail = Queue->Tail->Next;
    }
    ++Queue->Size;
}

void Queue_Dequeue(RQueue* Queue) {
    Queue_RNode* TempNode = Queue->Head;
    Queue->Head = Queue->Head->Next;
    --Queue->Size;
    free(TempNode);
}

void Queue_Traverse(RQueue* Queue) {
    Queue_RNode* TempNode = Queue->Head;
    printf("[ ");
    while (TempNode != NULL) {
        printf("%d ", TempNode->Data);
        TempNode = TempNode->Next;
    }
    printf("] Size: %lu\n", Queue->Size);
}

void Queue_Destroy(RQueue* Queue) {
    Queue_RNode* TempNode = Queue->Head;
    Queue_RNode* FreeNode;

    free(Queue);

    while (TempNode != NULL) {
        FreeNode = TempNode;
        TempNode = TempNode->Next;

        free(FreeNode);
    }
}


int main() {
    RQueue* Queue = Queue_Create();
    Queue_Enqueue(Queue, 1);
    Queue_Enqueue(Queue, 4);
    Queue_Enqueue(Queue, 7);
    Queue_Traverse(Queue);

    Queue_Dequeue(Queue);
    Queue_Traverse(Queue);

    Queue_Enqueue(Queue, 8);
    Queue_Traverse(Queue);

    Queue_Destroy(Queue);
}
