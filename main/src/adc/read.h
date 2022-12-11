#ifndef _READ_
#define _READ_

#include "driver/adc.h"
#include "esp_adc_cal.h"

float get_value_adc_1(adc1_channel_t adc_channel)
{
    return (adc1_get_raw(adc_channel)*3.3/4096);
}

#endif
