#include <stdio.h>
#include "sdkconfig.h"
#include "esp_log.h"
#include "src/connect/wifi.h"
#include "src/connect/mqtt.h"
#include "src/adc/read.h"
#include "esp_timer.h"
#include <nvs_flash.h>
#include "src/crypt/encrypt.h"
#include <mbedtls/base64.h>

#define QoS 2

void app_main(void)
{

    ESP_LOGI(__FILE__, "Start...");

    if (!loadRsaKeyEncrypt())
    {
        ESP_LOGE(__FILE__, "Error to load RSA key");
        return;
    }

    if (!loadRsaKeyDecrypt())
    {
        ESP_LOGE(__FILE__, "Error to load RSA key for decryption");
        return;
    }

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(connect_wifi_connect());

    setup_read();
    esp_mqtt_client_handle_t client_mqtt = setup_mqtt();

   
    char buffer[16] = {0};
    char *buffer_payload;
    int64_t last_call = esp_timer_get_time();

    while (1)
    {
     
        if (esp_timer_get_time() - last_call > CONFIG_TIMER_READ_US)
        {

            snprintf(buffer, 15, "%.4f", get_value());
            size_t olen = 0;
            buffer_payload = encryptPayload(buffer, &olen);

            if (buffer_payload != NULL)
            {
                size_t encode_len = 0;
                uint8_t enc[400] = {0};
                mbedtls_base64_encode((uint8_t *)enc, 400, &encode_len, (const uint8_t *)buffer_payload, olen);


                esp_mqtt_client_publish(client_mqtt, "esp1/volt", (char *)enc, 0, QoS, 0);
             
                free(buffer_payload);
            }

            last_call = esp_timer_get_time();
            
        }
    }
}