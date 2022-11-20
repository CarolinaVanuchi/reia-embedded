#ifndef _PUBLISH_PAYLOAD_
#define _PUBLISH_PAYLOAD_
#define QoS 2

void send_payload_ch1(esp_mqtt_client_handle_t client, adc1_channel_t adc_channel, const char *topic) {
    char buffer[16] = {0};
    char *buffer_payload;
    size_t olen = 0;

    snprintf(buffer, 15, "%.4f", get_value_adc_1(adc_channel));
    buffer_payload = encryptPayload(buffer, &olen);

    if (buffer_payload != NULL)
    {
        size_t encode_len = 0;
        uint8_t enc[400] = {0};
        mbedtls_base64_encode((uint8_t *)enc, 400, &encode_len, (const uint8_t *)buffer_payload, olen);

        esp_mqtt_client_publish(client, topic, (char *)enc, 0, QoS, 0);
        
        free(buffer_payload);
    }

}

void send_payload_ch2(esp_mqtt_client_handle_t client, adc1_channel_t adc_channel, const char *topic) {
    char buffer[16] = {0};
    char *buffer_payload;
    size_t olen = 0;

    snprintf(buffer, 15, "%.4f", get_value_adc_2(adc_channel));
    buffer_payload = encryptPayload(buffer, &olen);

    if (buffer_payload != NULL)
    {
        size_t encode_len = 0;
        uint8_t enc[400] = {0};
        mbedtls_base64_encode((uint8_t *)enc, 400, &encode_len, (const uint8_t *)buffer_payload, olen);

        esp_mqtt_client_publish(client, topic, (char *)enc, 0, QoS, 0);
        
        free(buffer_payload);
    }

}

#endif