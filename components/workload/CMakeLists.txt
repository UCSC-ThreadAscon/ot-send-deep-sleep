idf_component_register(SRCS "periodic.c"
                            "common.c"
                            "./client/request.c"
                            "./client/response_callback.c"
                       INCLUDE_DIRS "include"
                       PRIV_REQUIRES "openthread")
