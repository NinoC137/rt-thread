/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-05-06     Jiawei.Deng      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: GPIO_68 = PC4 */
#define LED1_PIN    PIN_NUM(GPIO_68)

/*******************************************************************************
 * Variables
 ******************************************************************************/
static rt_thread_t led1_thread = RT_NULL;

/*******************************************************************************
 * Functions
 ******************************************************************************/
static void led1_thread_entry(void *parameter)
{
    /* LED1 线程：每 500 ms 翻转一次，用于观察线程调度是否正常。 */
    RT_UNUSED(parameter);

    while (1)
    {
        GPIO_togglePin(BOARD_LED1_PIN);
        rt_thread_mdelay(500);
    }
}

int main(void)
{
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    /*
     * main 线程创建 LED1 子线程后，自己周期翻转 LED2。
     * 如果 LED1/LED2 都在闪烁，说明基本调度链路正常。
     */
    rt_kprintf("NS800RT7P65 RT-Thread ADC device demo\r\n");

    Interrupt_initVectorTable();

    led1_thread = rt_thread_create("led1",
                                   led1_thread_entry,
                                   RT_NULL,
                                   512,
                                   3,
                                   20);

    if (led1_thread != RT_NULL)
    {
        rt_thread_startup(led1_thread);
    }

    while (1)
    {
        GPIO_togglePin(BOARD_LED2_PIN);
        rt_thread_mdelay(1000);
    }
}

