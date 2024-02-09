#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "kalman.h"
#include "hx711.h"

#define AVG_SAMPLES 10
#define GPIO_DATA GPIO_NUM_21
#define GPIO_SCLK GPIO_NUM_22

static const char *TAG = "HX711_TEST";

static void weight_reading_task(void *arg);
static void initialise_weight_sensor(void);

#define AVG_SCALE (0.8f)
#define CALIB_WEIGHT (9.74f / 4450.0f)

static void weight_reading_task(void *arg)
{
    HX711_init(GPIO_DATA, GPIO_SCLK, eGAIN_128);
    HX711_tare();
    kalman_init(0.0, 5, 33);
    float weight_avg = 0;

    while (1)
    {
        float weight = HX711_get_units(1);
        float weight_filterd = kalman_filter_update(weight);
        weight_avg = (1.0f - AVG_SCALE) * weight_filterd + AVG_SCALE * weight_avg;
        ESP_LOGI(TAG, "weight = %.0f, %.3f, %.3f, %.3f", weight, weight_filterd, weight_avg, (weight_avg * CALIB_WEIGHT));
    }
}

static void initialise_weight_sensor(void)
{
    ESP_LOGI(TAG, "****************** Initialing weight sensor **********");
    xTaskCreatePinnedToCore(weight_reading_task, "weight_reading_task", 2048, NULL, 1, NULL, 0);
}

void app_main(void)
{
    initialise_weight_sensor();
}
