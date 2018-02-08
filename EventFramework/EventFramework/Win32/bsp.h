#ifndef BSP_H
#define BSP_H
typedef void (*TimeTickCallback)();
void initBsp();
void onIdle();
void setTimeTickCallback(TimeTickCallback callback);
void ENTER_CRITICAL_SESSION();
void EXIT_CRITICAL_SESSION();
#endif /* ifndef BSP_H */
