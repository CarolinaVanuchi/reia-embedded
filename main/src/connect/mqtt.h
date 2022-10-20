#ifndef _MQTT_
#define _MQTT_

#include <stdint.h>
#include "esp_log.h"
#include "mqtt_client.h"
#include "esp_tls.h"
#include "sdkconfig.h"
#include "../text_file.h"
#include "src/crypt/dencrypt.h"

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    int msg_id;
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;

    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(__FILE__, "MQTT_EVENT_CONNECTED");
       msg_id = esp_mqtt_client_subscribe(client, "webserver/sampling", 2);
        // ESP_LOGI(__FILE__, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(__FILE__, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_DATA:

        ESP_LOGI(__FILE__, "MQTT_EVENT_DATA");

        char *out_dec = decryptPayload(event->data_len, event->data);
        
        ESP_LOGI(__FILE__, "received: %s", out_dec);

        if(out_dec != NULL) free(out_dec);
        
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(__FILE__, "MQTT_EVENT_ERROR");
        if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT)
        {
            ESP_LOGE(__FILE__, "Last error code reported from esp-tls: 0x%x", event->error_handle->esp_tls_last_esp_err);
            ESP_LOGE(__FILE__, "Last tls stack error number: 0x%x", event->error_handle->esp_tls_stack_err);
            ESP_LOGE(__FILE__, "Last captured errno : %d (%s)", event->error_handle->esp_transport_sock_errno,
                     strerror(event->error_handle->esp_transport_sock_errno));
        }
        else if (event->error_handle->error_type == MQTT_ERROR_TYPE_CONNECTION_REFUSED)
            ESP_LOGE(__FILE__, "Connection refused error: 0x%x", event->error_handle->connect_return_code);
        else
            ESP_LOGW(__FILE__, "Unknown error type: 0x%x", event->error_handle->error_type);

        break;
    default:
        ESP_LOGI(__FILE__, "Other event id:%d", event->event_id);
        break;
    }
}

esp_mqtt_client_handle_t setup_mqtt()
{
    const esp_mqtt_client_config_t mqtt_conf = {
        .uri = CONFIG_MQTT_IP_PORT,
        .cert_pem = (const char *)cacert_start,
        .username = CONFIG_MQTT_USERNAME,
        .password = CONFIG_MQTT_PASSWORD,
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_conf);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
    return client;
}
#endif