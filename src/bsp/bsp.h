#ifndef BSP_H
#define BSP_H
typedef void (*TimeTickCallback)();
void Bsp_init();
void Bsp_onIdle();
void setTimeTickCallback(TimeTickCallback callback);
void ENTER_CRITICAL_SESSION();
void EXIT_CRITICAL_SESSION();
#endif /* ifndef BSP_H */
