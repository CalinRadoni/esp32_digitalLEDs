#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "esp32_rmt_dled.h"

static const char *TAG = "main";

void delay_ms(uint32_t ms)
{
    if (ms == 0) return;
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void app_main(void)
{
    esp_err_t err;
    rmt_pixel_strip_t rps;
    pixel_strip_t strip;

    nvs_flash_init();

    dled_strip_init(&strip);
    dled_strip_create(&strip, DLED_WS281x, 300, 32);

    rmt_dled_init(&rps);

    err = rmt_dled_create(&rps, &strip);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "[0x%x] rmt_dled_init failed", err);
        while(true) { }
    }

    err = rmt_dled_config(&rps, 16, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "[0x%x] rmt_dled_config failed", err);
        while(true) { }
    }

    err = rmt_dled_send(&rps);
    if (err != ESP_OK) { ESP_LOGE(TAG, "[0x%x] rmt_dled_send failed", err); }
    else               { ESP_LOGI(TAG, "LEDs initialized and turned off"); }

    uint16_t step;

    step = 0;
    while (step < 6 * strip.length) {
        dled_pixel_move_pixel(strip.pixels, strip.length, strip.max_cc_val, step);
        dled_strip_fill_buffer(&strip);
        rmt_dled_send(&rps);
        step++;
        delay_ms(20);
    }

    step = 0;
    while (true) {
        dled_pixel_rainbow_step(strip.pixels, strip.length, strip.max_cc_val, step);
        dled_strip_fill_buffer(&strip);
        rmt_dled_send(&rps);
        step++;
        delay_ms(50);
    }

    vTaskDelete(NULL);
}
