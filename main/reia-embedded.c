#include <stdio.h>
#include "sdkconfig.h"
#include <nvs_flash.h>
#include "esp_log.h"
#include "src/connect/wifi.h"
#include "esp_timer.h"
#include "src/adc/gpio_adc.h"
#include "src/mqtt/publish_payload.h"

void app_main(void)
{

    if (nvs_flash_init() != ESP_OK)                 return;
    if (esp_netif_init() != ESP_OK)                 return;
    if (esp_event_loop_create_default() != ESP_OK)  return;
    if (connect_wifi_connect() != ESP_OK)           return;
    
    if (!loadRsaKeyEncrypt())                       return;
    if (!loadRsaKeyDecrypt())                       return;

    setup_gpio_adc1(&adc_gpio_ch1_36, ADC1_CHANNEL_0);
    setup_gpio_adc1(&adc_gpio_ch1_39, ADC1_CHANNEL_3);
    setup_gpio_adc1(&adc_gpio_ch1_34, ADC1_CHANNEL_6);
    setup_gpio_adc1(&adc_gpio_ch1_35, ADC1_CHANNEL_7); 
    setup_gpio_adc1(&adc_gpio_ch1_32, ADC1_CHANNEL_4);
    setup_gpio_adc1(&adc_gpio_ch1_33, ADC1_CHANNEL_5);

    // setup_gpio_adc1(&adc_gpio_ch1_37, ADC1_CHANNEL_1);
    // setup_gpio_adc1(&adc_gpio_ch1_38, ADC1_CHANNEL_2);
    
    esp_mqtt_client_handle_t client_mqtt = setup_mqtt();

    int64_t last_call = esp_timer_get_time();
    while (1)
    {
        if (sampling > 0 && (esp_timer_get_time() - last_call > sampling) )
        {
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_0, CONFIG_TOPIC_GPIO36);
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_3, CONFIG_TOPIC_GPIO39);
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_6, CONFIG_TOPIC_GPIO34);
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_7, CONFIG_TOPIC_GPIO35);
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_4, CONFIG_TOPIC_GPIO32);
            send_payload_ch1(client_mqtt, ADC1_CHANNEL_5, CONFIG_TOPIC_GPIO33);

            // send_payload_ch1(client_mqtt, ADC1_CHANNEL_1, CONFIG_TOPIC_GPIO37);
            // send_payload_ch1(client_mqtt, ADC1_CHANNEL_2, CONFIG_TOPIC_GPIO38);

            last_call = esp_timer_get_time();   
        }
    }
}

