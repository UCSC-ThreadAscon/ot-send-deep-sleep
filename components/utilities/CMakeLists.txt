idf_component_register(SRCS "pollperiod.c"
                            "txpower.c"
                            "uuid.c"
                            "hexdump.c"
                            "sleep.c"
                            "./time/time.c"
                            "./time/debug.c"
                    INCLUDE_DIRS "include"
                    REQUIRES "openthread" "workload" "esp_timer")
