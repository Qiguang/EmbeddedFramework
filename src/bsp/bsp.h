#ifndef BSP_H
#define BSP_H
#include "types.h"
typedef void (*TimeoutCallback)(uint32_t elapsedTime);
void Bsp_init();
void Bsp_onIdle();
void Bsp_exitIdle();
void Bsp_startCountDown(uint32_t time);
uint32_t Bsp_stopCountDown();
void setTimeoutCallback(TimeoutCallback callback);
void ENTER_CRITICAL_SESSION();
void EXIT_CRITICAL_SESSION();
#endif /* ifndef BSP_H */
