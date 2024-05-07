idf_component_register(SRCS "./init/init.c"
                            "./event/event.c"
                            "./storage/storage.c"
                            "./payload/event_payload.c"
                            "./wakeup/wakeup.c"
                            "handlers.c"
                            "main.c"
                       INCLUDE_DIRS "include")
