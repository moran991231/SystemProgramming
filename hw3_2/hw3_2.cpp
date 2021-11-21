 #include <stdio.h> 
#include <stdlib.h>
#include <windows.h>

typedef struct _node {
    int data;
    struct _node* pNext;
} node;

typedef struct List { // List 구조체
    node* pHead;
    HANDLE hMutex;
};

typedef struct MyThreadData {
    List* l1, * l2;
    int id, trial;
};

// functions for list
List* createList();
void DeleteList(List* pList);
void swapLists(List* list1, List* list2, int time);

// functions for node
node* createNode(int data);
void insertNode(List* pList, node* newNode);

// functions for thread
MyThreadData* createMyThData(List* l1, List* l2, int id);
DWORD WINAPI ThreadFunc(LPVOID in);

int main()
{
    // make list
    List* lists[2] = { NULL, NULL };
    lists[0] = createList();
    lists[1] = createList();  
    insertNode(lists[0], createNode(111));
    insertNode(lists[1], createNode(222));     
    printf("Thread data: (L1 %d) (L2 %d) \n", lists[0]->pHead->data, lists[1]->pHead->data);

    // make thread data
    MyThreadData* pdata_arr[2];
    pdata_arr[0] = createMyThData(lists[0], lists[1], 1);
    pdata_arr[1] = createMyThData(lists[1], lists[0], 2);

    // create thread
    HANDLE hThrd[2] = { 0 }; 
    for (int i = 0; i < 2; i++)
    {
        hThrd[i] = CreateThread(NULL, 0, ThreadFunc, (LPVOID)pdata_arr[i], 0, NULL);
        if (hThrd[i])        
            printf("Thread launched %d\n", i + 1);        
        else {
            printf("error creating a thread\n");
            return 0;
        }
    }

    // wait for threads
    WaitForMultipleObjects(2, hThrd, TRUE, INFINITE);
    printf("All threads are ended: (L1 %d) (L2 %d) \n", lists[0]->pHead->data, lists[1]->pHead->data);

    // clean up memories
    DeleteList(lists[0]);
    DeleteList(lists[1]);
    free(pdata_arr[0]);
    free(pdata_arr[1]);
    
}

DWORD WINAPI ThreadFunc(LPVOID in)
{ // content of a thread
    MyThreadData* d = (MyThreadData*)in;
    for (d->trial = 1; d->trial <= 2000000; d->trial++) {
        swapLists(d->l1, d->l2, d->trial); //swap
        if (d->trial % 1000 == 0) {
            printf("thread %d swaped %d -times: (L1 %d) (L2 %d)\n", d->id, d->trial, d->l1->pHead->data, d->l2->pHead->data);
            Sleep(1);
        }
    }
    return 0;
}

List* createList() {
    List* pList = (List*)malloc(sizeof(List));
    pList->pHead = NULL;
    pList->hMutex = CreateMutex(NULL, FALSE, NULL);
    return pList;
}
void DeleteList(List* pList) {
    node* pnode = pList->pHead;
    node* pnext = NULL;
    CloseHandle(pList->hMutex); 
    free(pList);

    // release nodes
    while (pnode != NULL) {
        pnext = pnode->pNext;
        free(pnode);
        pnode = pnext;
    }
}

void swapLists(List* list1, List* list2, int time) {
    node* tmp_list;
    HANDLE handles[2] = { list1->hMutex, list2->hMutex };

    // grasp resources
    WaitForMultipleObjects(2, handles, TRUE, INFINITE); 

    // swap
    tmp_list = list1->pHead;
    list1->pHead = list2->pHead;
    list2->pHead = tmp_list;

    // release resources
    ReleaseMutex(handles[0]);
    ReleaseMutex(handles[1]);

}
node* createNode(int data) {
    node* ret = (node*)malloc(sizeof(node));
    ret->data = data;
    ret->pNext = NULL;
    return ret;
}

void insertNode(List* pList, node* newNode) {
    newNode->pNext = pList->pHead;
    pList->pHead = newNode;
}


MyThreadData* createMyThData(List* l1, List* l2, int id) {
    MyThreadData* ret = (MyThreadData*)malloc(sizeof(MyThreadData));
    *ret = { l1, l2, id, 0 };
    return ret;
}