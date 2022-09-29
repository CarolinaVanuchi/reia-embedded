#ifndef _READ_
#define _READ_

#include <stdio.h>
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

static esp_adc_cal_characteristics_t adc1_chars;

void setup_read(void)
{
    gpio_config_t adc_gpio = { 
        .mode = GPIO_MODE_INPUT, 
        .pin_bit_mask = (1ULL<<34) 
    };

    gpio_config(&adc_gpio);
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_11, 0, &adc1_chars);
    adc1_config_width(ADC_WIDTH_BIT_11);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
}

float get_value(void)
{
    uint32_t voltage_raw;
    float voltage;
    voltage_raw = adc1_get_raw(ADC1_CHANNEL_6);
    voltage = (voltage_raw*3.3/2048);
    return voltage;
}

#endif
