idf_component_register(SRCS "./init/init.c"
                            "./event/event.c"
                            "./storage/storage.c"
                            "./payload/event_payload.c"
                            "./handlers/wakeup.c"
                            "./handlers/handlers.c"
                            "main.c"
                       INCLUDE_DIRS "include")
