#ifndef _ENCRYPT_
#define _ENCRYPT_

#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "../text_file.h"
#include "esp_log.h"
#include <string.h>
#include <mbedtls/error.h>

mbedtls_pk_context pk;
mbedtls_entropy_context entropy;
mbedtls_ctr_drbg_context ctr_drbg;

bool loadRsaKeyPub()
{
    int ret = 0;
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);
    mbedtls_pk_init(&pk);

    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0)) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, " [-0x%04x: %s]", -ret, msgbuf);
        return false;
    }

   
    if ((ret = mbedtls_pk_parse_public_key(&pk, (const unsigned char *)rsa_key_start, (size_t)(rsa_key_end - rsa_key_start))) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, " [-0x%04x: %s]", -ret, msgbuf);
        return false;
    }

    return true;
}

char *encryptPayload(char *value)
{
    unsigned char buf[MBEDTLS_MPI_MAX_SIZE];

    size_t olen = 0;
    int ret_code = 0;

    if ((ret_code = mbedtls_pk_encrypt(&pk, (const unsigned char *)value, strlen(value), buf, &olen, MBEDTLS_MPI_MAX_SIZE, mbedtls_ctr_drbg_random, &ctr_drbg)) != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret_code, (char *)&msgbuf, 500);
        ESP_LOGI(__FILE__, "Failed in encrypt: [-0x%04x: %s]", -ret_code, (char *)msgbuf);
        return NULL;
    }

    char *ret = malloc(olen);
    memcpy(ret, buf, olen);
    return ret;
}

#endif