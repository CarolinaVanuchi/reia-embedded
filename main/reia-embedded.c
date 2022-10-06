#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "src/connect/wifi.h"
#include "src/connect/mqtt.h"
#include "src/adc/read.h"
#include "esp_timer.h"
#include <nvs_flash.h>
#include "src/crypt/encrypt.h"

void app_main(void)
{
    
    ESP_LOGI(__FILE__, "Start...");
    
    if (!loadRsaKeyPub()) {
        ESP_LOGE(__FILE__, "Error to load RSA key");
        return;
    }

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(connect_wifi_connect());

    setup_read();
    esp_mqtt_client_handle_t client_mqtt = setup_mqtt();

    float volt = 0;
    char buffer[16] = {0};
    char *buffer_payload;
    
    int64_t last_call = esp_timer_get_time(); 
    while (1) 
    {
        if(esp_timer_get_time() - last_call > CONFIG_TIMER_READ_US){
            volt = get_value();
            snprintf(buffer, 15, "%.4f", volt);
            
            buffer_payload = encryptPayload(buffer);
            if(buffer_payload != NULL){
                esp_mqtt_client_publish(client_mqtt, "esp1/volt", buffer_payload, 0, 0, 0);
                free(buffer_payload);
            }
            
            ESP_LOGI(__FILE__, "%f", volt);
            last_call = esp_timer_get_time();
        }

    }
}