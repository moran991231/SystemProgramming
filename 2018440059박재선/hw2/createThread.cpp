#include <windows.h>
#include <tchar.h>
#include <strsafe.h> // StringCchPrintf(), StringCchLength()
/*
* 2021-Fall Semester, Univ. of Seoul
* System Programming, pf. SJ Choi
* St No. 2018440059
* St Name: Jaesun Park
* Homework #2
*/

////////// declaration & definition //////////
#define MAX_THREADS 3 // num of threads
#define BUF_SIZE 255 // msg buf size

DWORD WINAPI MyThreadFunction(LPVOID lpParam); // thread function
void ErrorHandler(LPCTSTR lpszFunction);

typedef struct MyData { // parameter type of thread func
    // I can customize here
    int val1;
    int val2;
} MYDATA, * PMYDATA;


////////// main //////////
int _tmain()
{
    PMYDATA pDataArray[MAX_THREADS]; // params of threads
    DWORD   dwThreadIdArray[MAX_THREADS]; // IDs of threads
    HANDLE  hThreadArray[MAX_THREADS]; // handles of threads    

    ////////// create threads //////////
    for (int i = 0; i < MAX_THREADS; i++) // Create MAX_THREADS worker threads.
    {
        // make MyData with dynamic allocation
        pDataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));

        if (pDataArray[i] == NULL) // failed to mem alloc -> system is out of mem => lost its point of err msg  
            ExitProcess(2); // just exit

        // fill my data
        pDataArray[i]->val1 = i;
        pDataArray[i]->val2 = i + 100;

        // Create the thread to begin execution on its own.
        hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size  
            MyThreadFunction,       // thread function name
            pDataArray[i],          // argument to thread function 
            0,                      // use default creation flags 
            &dwThreadIdArray[i]);   // returns the thread identifier 

        if (hThreadArray[i] == NULL) // failed to create a thread
        {
            ErrorHandler(TEXT("CreateThread"));
            ExitProcess(3); // free all dynamically allocated mem and exit
        }
    }

    ////////// wait threads //////////
    // wait for all threads until they are terminated
    WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);

    ////////// dispose threads //////////
    // Close all thread handles and free memory allocations.
    for (int i = 0; i < MAX_THREADS; i++)
    {
        CloseHandle(hThreadArray[i]); // close the thread handle
        if (pDataArray[i] != NULL) // MyData free
        {
            HeapFree(GetProcessHeap(), 0, pDataArray[i]);
            pDataArray[i] = NULL;    // Ensure address is not reused.
        }
    }

    return 0;
} // _tmain() end


////////// thread function //////////
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
    ////////// getting ready ... //////////
    HANDLE hStdout; // std out handle
    PMYDATA pData; // arugument: MyData

    TCHAR msgBuf[BUF_SIZE];
    size_t cchStringSize;
    DWORD dwChars;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // get handle of stdout
    if (hStdout == INVALID_HANDLE_VALUE) // if failed, return
        return 1;

    pData = (PMYDATA)lpParam; // get the argument MyData which isn't NULL

    ////////// the content of thread  //////////
    // I can customize here
    StringCchPrintf(msgBuf, BUF_SIZE, TEXT("Parameters = %d, %d\n"), pData->val1, pData->val2);
    StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
    WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);

    return 0;
} // MyThreadFunction() end


////////// Error handler //////////
void ErrorHandler(LPCTSTR lpszFunction) // called after error occurence of CreateThread
{
    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); // for the analysis of last error code : CreateThread

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, // flags
        NULL, // lpSource
        dw, // Last Error
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Lanugauge
        (LPTSTR)&lpMsgBuf, // buffer to write
        0, // designate the size of buffer when FORMAT_MESSAGE_ALLOCATE_BUFFER flag is not set
        NULL); // the values that are used as insert values in the formatted message

    // Display the error message. 
    // ({lpszFunction:str} failed with error {dw:ulong}: {lpMsgBuf:str}) => This str's len is about (len(lpMsgBuf)+ len(lpszFunction)+40)
    size_t bufLen = (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen(lpszFunction) + 40);
    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, bufLen * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf, bufLen, TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    // Free error-handling buffer allocations.
    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
} // ErrorHandler() end