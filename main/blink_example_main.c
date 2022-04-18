#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#define BLINK_GPIO 1
#define GPIO_BASE 0x60004000
#define GPIO_ENABLE_REG 0x0020
#define GPIO_OUT_REG 0x0004
#define DELAY_MS 500

void app_main(void)
{
    // set as output
    (*(volatile uint32_t*)(GPIO_BASE + GPIO_ENABLE_REG) |= (0x1 << BLINK_GPIO));

    while (1) {
        (*(volatile uint32_t*)(GPIO_BASE + GPIO_OUT_REG) |= (0x1 << BLINK_GPIO));
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
        (*(volatile uint32_t*)(GPIO_BASE + GPIO_OUT_REG) &= ~(0x1 << BLINK_GPIO));
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}
