#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "src/connect/wifi.h"
#include "src/connect/mqtt.h"
#include "src/adc/read.h"
#include "esp_timer.h"
#include <nvs_flash.h>
#include "src/crypt/encrypt.h"
#include "src/crypt/dencrypt.h"
#include <mbedtls/base64.h>

void app_main(void)
{
    
    ESP_LOGI(__FILE__, "Start...");
    
    if (!loadRsaKeyPub()) {
        ESP_LOGE(__FILE__, "Error to load RSA key");
        return;
    }

    if (!loadRsaKeyDecrypt()) {
        ESP_LOGE(__FILE__, "Error to load RSA key for decryption");
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
            
            size_t olen = 0;
            ESP_LOGD(__FILE__, "len: [%i]", strlen(buffer));
            buffer_payload = encryptPayload(buffer, &olen);
            if(buffer_payload != NULL){

                // esp_mqtt_client_publish(client_mqtt, "esp1/volt2", buffer, 0, 0, 0);

                // char *out = decrypt(olen, buffer_payload);
                // if(out != NULL){
                //     ESP_LOGI(__FILE__, "%s", out);
                //     free(out);
                // }

                size_t encode_len = 0;
                uint8_t enc[1000] = {0};
                mbedtls_base64_encode((uint8_t*)enc, 1000, &encode_len, (const uint8_t*)buffer_payload, olen);
                ESP_LOGI(__FILE__, "%i", olen);
                ESP_LOGI(__FILE__, "%s", enc);
                esp_mqtt_client_publish(client_mqtt, "esp1/volt", (char*)enc, 0, 0, 0);

                free(buffer_payload);
            }
            
            ESP_LOGI(__FILE__, "%s", buffer);
            last_call = esp_timer_get_time();
        }

    }
}