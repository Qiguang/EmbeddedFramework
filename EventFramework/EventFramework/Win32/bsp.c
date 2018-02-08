#include <Windows.h>
#include <stdint.h>
#include "bsp.h"
CRITICAL_SECTION criticalSection;
DWORD WINAPI timeTickService(_In_ LPVOID lpParameter);
TimeTickCallback timeTickCallback;
uint16_t timeTickCountPerSec = 100U;
void setTimeTickPerSec(uint16_t countPerSec)
{
    timeTickCountPerSec = countPerSec;
}
HANDLE resumeEvent;
void initBsp()
{
    InitializeCriticalSection(&criticalSection);
    resumeEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ResumeEvent"));
    // TODO: don't forget CloseHandle(resumeEvent) when exit
    CreateThread(NULL, 0, timeTickService, NULL, 0, NULL);
}
void onIdle()
{
    WaitForSingleObject(resumeEvent, INFINITE);
}
void setTimeTickCallback(TimeTickCallback callback)
{
    timeTickCallback = callback;
}
void ENTER_CRITICAL_SESSION()
{
    EnterCriticalSection(&criticalSection);
}
void EXIT_CRITICAL_SESSION()
{
    LeaveCriticalSection(&criticalSection);
}

DWORD WINAPI timeTickService(_In_ LPVOID lpParameter)
{
    while (1) {
        Sleep(1000U/timeTickCountPerSec);
        SetEvent(resumeEvent);

        if (timeTickCallback) {
            timeTickCallback();
        }
    }
}
