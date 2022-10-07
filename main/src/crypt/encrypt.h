#ifndef _ENCRYPT_
#define _ENCRYPT_

#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "../text_file.h"
#include "esp_log.h"
#include <string.h>
#include <mbedtls/error.h>

mbedtls_pk_context en_pk;
mbedtls_entropy_context en_entropy;
mbedtls_ctr_drbg_context en_ctr_drbg;

bool loadRsaKeyPub()
{
    int ret = 0;
    mbedtls_ctr_drbg_init(&en_ctr_drbg);
    mbedtls_entropy_init(&en_entropy);
    mbedtls_pk_init(&en_pk);

    if ((ret = mbedtls_ctr_drbg_seed(&en_ctr_drbg, mbedtls_entropy_func, &en_entropy, NULL, 0)) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, " [-0x%04x: %s]", -ret, msgbuf);
        return false;
    }

   
    if ((ret = mbedtls_pk_parse_public_key(&en_pk, (const unsigned char *)rsa_key_start, (size_t)(rsa_key_end - rsa_key_start))) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, " [-0x%04x: %s]", -ret, msgbuf);
        return false;
    }

    return true;
}

char *encryptPayload(char *value, size_t *outlen)
{
    unsigned char buf[MBEDTLS_MPI_MAX_SIZE];

    size_t olen = 0;
    int ret_code = 0;

    if ((ret_code = mbedtls_pk_encrypt(&en_pk, (const unsigned char *)value, strlen(value), buf, &olen, MBEDTLS_MPI_MAX_SIZE, mbedtls_ctr_drbg_random, &en_ctr_drbg)) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret_code, (char *)&msgbuf, 500);
        ESP_LOGI(__FILE__, "Failed in encrypt: [-0x%04x: %s]", -ret_code, (char *)msgbuf);
        return NULL;
    }

    ESP_LOGD(__FILE__, "len: [%i]", olen);
    if(outlen != NULL) *outlen = olen;
    char *ret = malloc(olen);
    memcpy(ret, buf, olen);
    return ret;
}

#endif