#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#define BLINK_GPIO 1
#define GPIO_BASE 0x60004000
#define GPIO_ENABLE_REG 0x0020
#define GPIO_OUT_REG 0x0004
#define DELAY_MS 100

void app_main(void)
{
    // set as output
    // (*(volatile uint32_t*)(GPIO_BASE + GPIO_ENABLE_REG) |= (0x1 << BLINK_GPIO));

    //clang from godbolt
    // C --> RISC-V rv32gc clang 14.0.0

    __asm__(
          "addi    sp, sp, -16\n\t"
          "sw      ra, 12(sp)\n\t"
          "sw      s0, 8(sp)\n\t"
          "addi    s0, sp, 16\n\t"
          "lui     a1, 393220\n\t"
          "lw      a0, 32(a1)\n\t"
          "ori     a0, a0, 2\n\t"
          "sw      a0, 32(a1)\n\t"
          "li      a0, 0\n\t"
          "lw      ra, 12(sp)\n\t"
          "lw      s0, 8(sp)\n\t"
          "addi    sp, sp, 16\n\t"
      );

    while (1) {
    // set
    __asm__(
          "addi    sp, sp, -16\n\t"
          "sw      ra, 12(sp)\n\t"
          "sw      s0, 8(sp)\n\t"
          "addi    s0, sp, 16\n\t"
          "lui     a1, 393220\n\t"
          "lw      a0, 4(a1)\n\t"
          "ori     a0, a0, 2\n\t"
          "sw      a0, 4(a1)\n\t"
          "li      a0, 0\n\t"
          "lw      ra, 12(sp)\n\t"
          "lw      s0, 8(sp)\n\t"
          "addi    sp, sp, 16\n\t"
      );
  // (*(volatile uint32_t*)(GPIO_BASE + GPIO_OUT_REG) |= (0x1 << BLINK_GPIO));
      vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);

    //clear
    __asm__(
        "addi    sp, sp, -16\n\t"
        "sw      ra, 12(sp)\n\t"
        "sw      s0, 8(sp)\n\t"
        "addi    s0, sp, 16\n\t"
        "lui     a1, 393220\n\t"
        "lw      a0, 4(a1)\n\t"
        "andi    a0, a0, -3\n\t"
        "sw      a0, 4(a1)\n\t"
        "li      a0, 0\n\t"
        "lw      ra, 12(sp)\n\t"
        "lw      s0, 8(sp)\n\t"
        "addi    sp, sp, 16\n\t"
      );

        // (*(volatile uint32_t*)(GPIO_BASE + GPIO_OUT_REG) &= ~(0x1 << BLINK_GPIO));
      vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
    }
}
