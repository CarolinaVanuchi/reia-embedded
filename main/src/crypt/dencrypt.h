#ifndef _DENCRYPT_
#define _DENCRYPT_

#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "../text_file.h"
#include "esp_log.h"
#include <string.h>
#include <mbedtls/error.h>


FILE *f;
int ret = 1;
int exit_code = MBEDTLS_EXIT_FAILURE;
unsigned c;

mbedtls_pk_context pk;
mbedtls_entropy_context entropy;
mbedtls_ctr_drbg_context ctr_drbg;
unsigned char result[1024];

const char *pers = "rsa_decrypt";

bool loadRsaKeyDecrypt()
{
    memset(result, 0, sizeof(result));

    mbedtls_pk_init( &pk );
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_entropy_init(&entropy);

    ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func,
                                &entropy, (const unsigned char *)pers,
                                strlen(pers));

    if (ret != 0)
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return false;
    }

    if( ( ret = mbedtls_pk_parse_key( &pk, (const unsigned char*)rsa_private_key_start, (size_t)(rsa_private_key_end - rsa_private_key_start), NULL, 0) ) != 0 )
    {
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return false;
    }

    return true;
}

char *decrypt(size_t i, char *in)
{
    /*
     * Decrypt the encrypted RSA data and print the result.
     */

    char buffer[512] = {0};
    size_t olen = 0;
    ESP_LOGD(__FILE__, "len: [%i]", i);
    if( (ret = mbedtls_pk_decrypt( 
            &pk, 
            (const unsigned char*)in, 
            i, 
            (unsigned char *)buffer, 
            &olen, 
            512,
            mbedtls_ctr_drbg_random, 
            &ctr_drbg )
    ) != 0 
    ){
        char msgbuf[500] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 500);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return NULL;
    }

    ESP_LOGD(__FILE__, "len: [%i]", olen);
    char *out = calloc(sizeof(char), olen + 1);
    memcpy(out, buffer, olen);
    return out;
}
#endif