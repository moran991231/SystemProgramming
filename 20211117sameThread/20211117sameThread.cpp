
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#include <Windows.h>


int main()
{ 
    CRITICAL_SECTION cs1;
    InitializeCriticalSection(&cs1);
    EnterCriticalSection(&cs1);
    printf("we are taking cs1\n");

    EnterCriticalSection(&cs1); // critical section object is shared in the same thread
    printf("we are taking cs1?????\n");

    HANDLE hM = CreateMutex(NULL, FALSE, NULL);
    WaitForSingleObject(hM, INFINITE);
    printf("we are taking hM\n");
    WaitForSingleObject(hM, INFINITE); // Mutex is also shared in the same thread
    printf("we are taking hM?????????\n");

    return 0;

}
