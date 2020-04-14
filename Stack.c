#include <stdio.h>
#include <stdlib.h>

typedef struct Stack_RNode Stack_RNode;
struct Stack_RNode {
    int Data;
    Stack_RNode* Next;
};

typedef struct {
    Stack_RNode* Head;
    unsigned long Size;
} RStack;

RStack* Stack_Create() {
    RStack* NewStack = malloc(sizeof(RStack));
    NewStack->Head = NULL;
    NewStack->Size = 0;
    return NewStack;
}

Stack_RNode* Stack_CreateNode(int Data) {
    Stack_RNode* NewNode = malloc(sizeof(Stack_RNode));
    NewNode->Data = Data;
    NewNode->Next = NULL;
    return NewNode;
}

void Stack_Push(RStack* Stack, int Data) {
    Stack_RNode* NewNode = Stack_CreateNode(Data);
    NewNode->Next = Stack->Head;
    Stack->Head = NewNode;
    ++Stack->Size;
}

void Stack_Pop(RStack* Stack) {
    Stack_RNode* TempNode = Stack->Head;
    Stack->Head = Stack->Head->Next;
    --Stack->Size;
    free(TempNode);
}

void Stack_Traverse(RStack* Stack) {
    Stack_RNode* TempNode = Stack->Head;
    printf("[ ");
    while (TempNode != NULL) {
        printf("%d ", TempNode->Data);
        TempNode = TempNode->Next;
    }
    printf("] Size: %lu\n", Stack->Size);
}

void Stack_Destroy(RStack* Stack) {
    Stack_RNode* TempNode = Stack->Head;
    Stack_RNode* FreeNode;

    free(Stack);

    while (TempNode != NULL) {
        FreeNode = TempNode;
        TempNode = TempNode->Next;

        free(FreeNode);
    }
}


int main() {
    RStack* Stack = Stack_Create();
    Stack_Push(Stack, 1);
    Stack_Push(Stack, 4);
    Stack_Push(Stack, 7);
    Stack_Traverse(Stack);

    Stack_Pop(Stack);
    Stack_Traverse(Stack);

    Stack_Push(Stack, 8);
    Stack_Traverse(Stack);

    Stack_Destroy(Stack);
}
