idf_component_register(SRCS "reia-embedded.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES  "cert/ssl/ca.crt"
                                    "cert/rsa/public.pem"
                                    "cert/rsa/private.pem"
                    )
