#include <stdio.h>
#include <stdlib.h>

typedef struct List_RNode List_RNode;
struct List_RNode {
    int Data;
    List_RNode* Next;
    List_RNode* Prev;
};

typedef struct RList {
    List_RNode* Head;
    List_RNode* Tail;
    unsigned long Size;
} RList;

RList* List_Create() {
    RList* NewList = malloc(sizeof(RList));
    NewList->Head = NULL;
    NewList->Tail = NULL;
    NewList->Size = 0;
    return NewList;
}

List_RNode* List_CreateNode(int Data) {
    List_RNode* NewNode = malloc(sizeof(List_RNode));
    NewNode->Data = Data;
    NewNode->Next = NULL;
    NewNode->Prev = NULL;
    return NewNode;
};

void List_InsertAfter(RList* List, List_RNode* Node, int Data) {
    List_RNode* NewNode = List_CreateNode(Data);
    NewNode->Prev = Node;

    if (Node->Next == NULL) {
        List->Tail = NewNode;
    } else {
        NewNode->Next = Node->Next;
        Node->Next->Prev = NewNode;
    }
    Node->Next = NewNode;
    ++List->Size;
}

void List_InsertBefore(RList* List, List_RNode* Node, int Data) {
    List_RNode* NewNode = List_CreateNode(Data);
    NewNode->Next = Node;

    if (Node->Prev == NULL) {
        List->Head = NewNode;
    } else {
        NewNode->Prev = Node->Prev;
        Node->Prev->Next = NewNode;
    }
    Node->Prev = NewNode;
    ++List->Size;
}

void List_InsertHead(RList* List, int Data) {
    if (List->Head == NULL) {
        List_RNode* NewNode = List_CreateNode(Data);
        List->Head = NewNode;
        List->Tail = NewNode;
    } else {
        List_InsertBefore(List, List->Head, Data);
    }
}

void List_InsertTail(RList* List, int Data) {
    if (List->Tail == NULL) {
        List_InsertHead(List, Data);
    } else {
        List_InsertAfter(List, List->Tail, Data);
    }
}

void List_Remove(RList* List, List_RNode* Node) {
    if (Node->Prev == NULL) {
        List->Head = Node->Next;
    } else {
        Node->Prev->Next = Node->Next;
    }

    if (Node->Next == NULL) {
        List->Tail = Node->Prev;
    } else {
        Node->Next->Prev = Node->Prev;
    }

    --List->Size;
}

void List_Traverse(RList* List) {
    List_RNode* TempNode = List->Head;
    printf("Forward [ ");
    while (TempNode != NULL) {
        printf("%d ", TempNode->Data);
        TempNode = TempNode->Next;
    }
    printf("] Size: %lu\n", List->Size);
}

void List_TraverseReverse(RList* List) {
    List_RNode* TempNode = List->Tail;
    printf("Backward [ ");
    while (TempNode != NULL) {
        printf("%d ", TempNode->Data);
        TempNode = TempNode->Prev;
    }
    printf("] Size: %lu\n", List->Size);
}

void List_Destroy(RList* List) {
    List_RNode* TempNode = List->Head;
    List_RNode* FreeNode;

    while (TempNode != NULL) {
        FreeNode = TempNode;
        TempNode = TempNode->Next;

        free(FreeNode);
    }

    free(List);
}

int main() {
    RList* List = List_Create();

    List_InsertHead(List, 1);
    List_InsertHead(List, 3);
    List_InsertHead(List, 4);

    List_Traverse(List);
    List_TraverseReverse(List);

    printf("\n");

    List_InsertTail(List, 9);
    List_InsertTail(List, 0);

    List_Traverse(List);
    List_TraverseReverse(List);
}
