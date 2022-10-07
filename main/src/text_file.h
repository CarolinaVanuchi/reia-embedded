#ifndef _TEXT_FILES_
#define _TEXT_FILES_

extern const unsigned char cacert_start[]               asm("_binary_ca_crt_start");
extern const unsigned char cacert_end[]                 asm("_binary_ca_crt_end");
extern const unsigned char rsa_key_start[]              asm("_binary_public_pem_start");
extern const unsigned char rsa_key_end[]                asm("_binary_public_pem_end");
extern const unsigned char rsa_private_key_start[]      asm("_binary_private_pem_start");
extern const unsigned char rsa_private_key_end[]        asm("_binary_private_pem_end");


#endif