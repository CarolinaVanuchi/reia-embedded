#ifndef _READ_
#define _READ_

#include "driver/adc.h"
#include "esp_adc_cal.h"

esp_err_t errror;

float get_value_adc_1(adc1_channel_t adc_channel)
{
    return (adc1_get_raw(adc_channel)*3.3/4096);
}

float get_value_adc_2(adc2_channel_t adc_channel)
{
    int read_raw = 0;
    errror = adc2_get_raw(adc_channel, ADC_WIDTH_BIT_12, &read_raw);
    ESP_LOGI(__FILE__, "READ ADC2 [%i]", read_raw);
    ESP_LOGI(__FILE__, "READ ERROR [%s]", esp_err_to_name(errror));
    return (read_raw *3.3/4096);
}


#endif
