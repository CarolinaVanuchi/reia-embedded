#ifndef _GPIO_ADC_
#define _GPIO_ADC_

#include "driver/adc.h"
#include "esp_adc_cal.h"

void setup_gpio_adc1(const gpio_config_t *gpio, adc1_channel_t adc_channel)
{
    gpio_config(gpio);    
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
}

gpio_config_t adc_gpio_ch1_36 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<36) 
};

gpio_config_t adc_gpio_ch1_37 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<27) 
};

gpio_config_t adc_gpio_ch1_38 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<38) 
};

gpio_config_t adc_gpio_ch1_39 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<39) 
};

gpio_config_t adc_gpio_ch1_32 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<32) 
};

gpio_config_t adc_gpio_ch1_33 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<33) 
};

gpio_config_t adc_gpio_ch1_34 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<34) 
};

gpio_config_t adc_gpio_ch1_35 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<35) 
};

#endif
