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

void setup_gpio_adc2(const gpio_config_t *gpio, adc2_channel_t adc_channel)
{
    gpio_config(gpio);
    adc2_config_channel_atten(adc_channel, ADC_ATTEN_DB_11);
}

// Channel 1
gpio_config_t adc_gpio_ch1_36 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<36) 
};

gpio_config_t adc_gpio_ch1_37 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<37) 
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

// Channel 2
gpio_config_t adc_gpio_ch2_04 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<4) 
};

gpio_config_t adc_gpio_ch2_00 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<0) 
};

gpio_config_t adc_gpio_ch2_02 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<2) 
};

gpio_config_t adc_gpio_ch2_15 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<15) 
};

gpio_config_t adc_gpio_ch2_13 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<13) 
};

gpio_config_t adc_gpio_ch2_12 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<12) 
};

gpio_config_t adc_gpio_ch2_14 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<14) 
};

gpio_config_t adc_gpio_ch2_27 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<27) 
};

gpio_config_t adc_gpio_ch2_25 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<25) 
};

gpio_config_t adc_gpio_ch2_26 = { 
    .mode = GPIO_MODE_INPUT, 
    .pin_bit_mask = (1ULL<<26) 
};

#endif
