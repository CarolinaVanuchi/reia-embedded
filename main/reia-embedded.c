#include "sdkconfig.h"
#include "esp_log.h"
#include "src/connect/wifi.h"
#include "src/connect/mqtt.h"
#include "src/adc/read.h"

static const char *TAG = "Main";


void app_main(void)
{
    
    ESP_LOGI(TAG, "Start...");

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(connect_wifi_connect());
    mqtt_app_start();
    // setup_read();
}