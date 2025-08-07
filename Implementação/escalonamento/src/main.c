
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACK_SIZE 1024

#define PRIORIDADE_SENSOR 0
#define PRIORIDADE_TECLADO 1
#define PRIORIDADE_DISPLAY 2

void sensor_thread(void)
{
    while (1) {
        printk("[Sensor] Tempo: %d ms\n", k_uptime_get());
        k_msleep(500);
    }
}

void teclado_thread(void)
{
    while (1) {
        printk("[Teclado] Tempo: %d ms\n", k_uptime_get());
        k_msleep(1000);
    }
}

void display_thread(void)
{
    while (1) {
        printk("[Display] Tempo: %d ms\n", k_uptime_get());
        k_msleep(2000);
    }
}

K_THREAD_DEFINE(sensor_id, STACK_SIZE, sensor_thread, NULL, NULL, NULL,
                PRIORIDADE_SENSOR, 0, 0);
K_THREAD_DEFINE(teclado_id, STACK_SIZE, teclado_thread, NULL, NULL, NULL,
                PRIORIDADE_TECLADO, 0, 0);
K_THREAD_DEFINE(display_id, STACK_SIZE, display_thread, NULL, NULL, NULL,
                PRIORIDADE_DISPLAY, 0, 0);
