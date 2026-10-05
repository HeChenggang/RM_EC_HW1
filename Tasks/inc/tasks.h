#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* 第二题和第三题：在 CPU 运行时，使用 Ozone 观察此全局变量。 */
extern volatile uint32_t tick;

/* 在 GPIO、IWDG 和 TIM2 初始化完成后调用一次。 */
void Tasks_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* TASKS_H */
