// 20211103Wait.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
 


#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

 // CreateThread함수에 의해 호출되는 함수는 반드시 아래와 같은 함수형을 가져야 한다.
 // 매개변수: LPVOID 1개, 반환형: DWORD, calling convention(함수호출방법): WINAPI
DWORD WINAPI ThreadFunc(LPVOID); // LPVOID == void *

int main()
{
    HANDLE hThrd[5] = {0}; // thread와 관련된 여러 정보를 담고 있다.
    DWORD threadId;
    int i;

    for (i = 0; i < 5; i++)
    {
        // CreateThread: thread's kernel object 생성 후 handle을 반환
        hThrd[i] = CreateThread(NULL,  // function pointer
            0,                      // function pointer
            ThreadFunc,             // function pointer
            (LPVOID)i,              // one parameter
            0,
            &threadId);
        if (hThrd[i])
        {
            printf("Thread launched %d\n", i);
            //CloseHandle(hThrd);
        }
        else { // 스레드 생성에 실패하면 hThread ==NULL
            printf("error creating a thread\n");
            return 0;
        }
    } 

    Sleep(2000); // 현재 스레드를 2000ms만큼 블록시킴, 워커 스레드가 동작을 완료하길 기다림. sleep이 정답은 아님
    // 스레드가 제대로 종료하였는지 알 수 있는 방법
    // 1. 모든 KO는 두 가지 상태(signaled/ nonsignaled)를 가짐
    // 2. state의 의미는 KO마다 다르다.
    // 3. thread KO의 상태 의미: signaled-종료, nonsignaled-수행 중
    // 4. KO의 상태를 알 수 있는 api: WaitForSingleObject(HANDLE, DWORD)/WaitForMultipleObjects()
    //WaitForSingleObject(hThrd[0], INFINITE); // DWORD milliseconds: timeout
    WaitForMultipleObjects(5, hThrd, TRUE, INFINITE);
    for (int i = 0; i < 5; i++)
        CloseHandle(hThrd[i]);
    // 1. thread 실행 종료, 2. CloseHandle() 스레드 KO소멸

    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID in)
{
    int i;
    int n = (int)in;
    for (i = 0; i < 10; i++)
        printf("%d%d%d%d%d%d%d%d\n", n, n, n, n, n, n, n, n);
    return 0;
}
