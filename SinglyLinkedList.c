#include <stdio.h>
#include <stdlib.h>

typedef struct List_RNode List_RNode;
struct List_RNode {
    int Data;
    List_RNode* Next;
};

typedef struct {
    List_RNode* Head;
    unsigned long Size;
} RList;

RList* List_Create() {
    RList* NewList = malloc(sizeof(RList));
    NewList->Head = NULL;
    NewList->Size = 0;
    return NewList;
}

List_RNode* List_CreateNode(RList* List, int Data) {
    List_RNode* NewNode = malloc(sizeof(List_RNode));
    NewNode->Data = Data;
    NewNode->Next = NULL;
    ++List->Size;
    return NewNode;
}

void List_Insert(RList* List, int Data) {
    List_RNode* NewNode = List_CreateNode(List, Data);
    NewNode->Next = List->Head;
    List->Head = NewNode;
}

void List_Remove(RList* List) {
    List_RNode* TempNode = List->Head;
    List->Head = List->Head->Next;
    --List->Size;
    free(TempNode);
}

void List_Traverse(RList* List) {
    List_RNode* TempNode = List->Head;
    printf("[ ");
    while (TempNode != NULL) {
        printf("%d ", TempNode->Data);
        TempNode = TempNode->Next;
    }
    printf("] Size: %lu\n", List->Size);
}

void List_Destroy(RList* List) {
    List_RNode* TempNode = List->Head;
    List_RNode* FreeNode;

    free(List);

    while (TempNode != NULL) {
        FreeNode = TempNode;
        TempNode = TempNode->Next;

        free(FreeNode);
    }
}


int main() {
    RList* List = List_Create();
    List_Insert(List, 1);
    List_Insert(List, 4);
    List_Insert(List, 7);
    List_Traverse(List);

    List_Remove(List);
    List_Traverse(List);

    List_Insert(List, 8);
    List_Traverse(List);

    List_Destroy(List);
}
