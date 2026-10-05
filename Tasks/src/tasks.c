#include "tasks.h"

#include "gpio.h"
#include "tim.h"

/* 第二题：取消下一行及下方两处喂狗代码的注释即可恢复第二题。 */
/* #include "iwdg.h" */

volatile uint32_t tick = 0U;

void Tasks_Init(void)
{
    /* 第一题：板载 PC13 LED 为低电平点亮，并保持常亮。 */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    tick = 0U;
    /* 第二题：初始化时喂狗；第三题保持注释。
    if (HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
    {
        Error_Handler();
    }
    */

    /* 第三题：独立看门狗（IWDG）已启动，不再喂狗。
     * 标称超时时间：(1249 + 1) * 64 / 40000 = 2 秒。
     * 看门狗复位后，启动代码会将 tick 重新初始化为零。
     */

    /* 清除配置 TIM2 时产生的更新标志。 */
    __HAL_TIM_SET_COUNTER(&htim2, 0U);
    __HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
    if (HAL_TIM_Base_Start_IT(&htim2) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance != TIM2)
    {
        return;
    }

    /* HSI = HCLK = PCLK1 = 8 MHz，APB1 分频系数为 1，因此 TIM2 时钟频率为 8 MHz。
     * (PSC + 1) * (ARR + 1) / TIM2 时钟频率 = 8 * 1000 / 8000000 = 1 毫秒。
     * 此处不喂狗，让独立看门狗触发单片机硬件复位，以完成第三题。
     */
    tick++;

    /* 第二题：每 1 ms 自增 tick 后喂狗，使 tick 持续增长。
     * 第三题保持注释，让 IWDG 超时触发硬件复位。
    if (HAL_IWDG_Refresh(&hiwdg) != HAL_OK)
    {
        Error_Handler();
    }
    */
}
