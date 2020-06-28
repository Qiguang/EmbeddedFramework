#include <Windows.h>
#include <stdint.h>
#include "../bsp.h"
CRITICAL_SECTION criticalSection;
DWORD WINAPI timeCountDownService(_In_ LPVOID lpParameter);
TimeoutCallback timeoutCallback;
uint32_t countDownTime;
HANDLE resumeEvent;
HANDLE countDownEvent;
static uint32_t elapsedTime = 0;
void Bsp_init()
{
    InitializeCriticalSection(&criticalSection);
    resumeEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("ResumeEvent"));
    countDownEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("CountDownEvent"));
    // TODO: don't forget CloseHandle(resumeEvent) when exit
    // TODO: don't forget CloseHandle(countDownEvent) when exit
    CreateThread(NULL, 0, timeCountDownService, NULL, 0, NULL);
}
void Bsp_onIdle()
{
    WaitForSingleObject(resumeEvent, INFINITE);
}
void Bsp_exitIdle()
{
    SetEvent(resumeEvent);
}
void Bsp_startCountDown(uint32_t time)
{
    countDownTime = time;
    SetEvent(countDownEvent);
}
uint32_t Bsp_stopCountDown()
{
    uint32_t rv = elapsedTime;
    countDownTime = 0;
    
    return rv;
}
void setTimeoutCallback(TimeoutCallback callback)
{
    ENTER_CRITICAL_SESSION();
    timeoutCallback = callback;
    EXIT_CRITICAL_SESSION();
}
void ENTER_CRITICAL_SESSION()
{
    EnterCriticalSection(&criticalSection);
}
void EXIT_CRITICAL_SESSION()
{
    LeaveCriticalSection(&criticalSection);
}

DWORD WINAPI timeCountDownService(_In_ LPVOID lpParameter)
{
    while (1) {
        WaitForSingleObject(countDownEvent, INFINITE);
        while (countDownTime) {
            Sleep(1);
            elapsedTime++;
            if (!--countDownTime) {
                if (timeoutCallback) {
                    timeoutCallback(elapsedTime);
                }
                elapsedTime = 0;
            }
        }
    }
}

