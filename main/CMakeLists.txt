idf_component_register(SRCS "./init/init.c"
                            "./event/event.c"
                            "./storage/storage.c"
                            "./payload/payload.c"
                            "./handlers/wakeup.c"
                            "./handlers/handlers.c"
                            "./handlers/debug.c"
                            "main.c"
                       INCLUDE_DIRS "include")
