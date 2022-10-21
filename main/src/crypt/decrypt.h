#ifndef _DECRYPT_
#define _DECRYPT_

#include "mbedtls/pk.h"
#include "mbedtls/ctr_drbg.h"
#include "../text_file.h"
#include "esp_log.h"
#include <string.h>
#include <mbedtls/error.h>
#include <mbedtls/base64.h>


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
        char msgbuf[400] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 400);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return false;
    }

    if( ( ret = mbedtls_pk_parse_key( &pk, (const unsigned char*)rsa_private_key_start, (size_t)(rsa_private_key_end - rsa_private_key_start), NULL, 0) ) != 0 )
    {
        char msgbuf[400] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 400);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return false;
    }

    return true;
}

char *decryptPayload(size_t i, char *in)
{
    char buffer[512] = {0};
    size_t olen = 0;
    size_t decode_olen = 0;
    
    uint8_t decode_data[i];

    mbedtls_base64_decode(decode_data, i, &decode_olen, (uint8_t *)in, i);
    
    if( (ret = mbedtls_pk_decrypt( 
            &pk, 
            (const unsigned char*)decode_data, 
            decode_olen, 
            (unsigned char *)buffer, 
            &olen, 
            512,
            mbedtls_ctr_drbg_random, 
            &ctr_drbg )
    ) != 0 
    ){
        char msgbuf[400] = {0};
        mbedtls_strerror(ret, (char *)&msgbuf, 400);
        ESP_LOGE(__FILE__, "[%i] loadRsaKeyDecrypt: [-0x%04x: %s]", __LINE__, -ret, msgbuf);
        return NULL;
    }

  
    char *out = calloc(sizeof(char), olen + 1);
    memcpy(out, buffer, olen);
    return out;
}
#endif