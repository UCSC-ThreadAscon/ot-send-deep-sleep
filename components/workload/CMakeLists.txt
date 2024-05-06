idf_component_register(SRCS "periodic.c"
                            "client.c"
                            "common.c"
                            "./client/request.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES "openthread")
