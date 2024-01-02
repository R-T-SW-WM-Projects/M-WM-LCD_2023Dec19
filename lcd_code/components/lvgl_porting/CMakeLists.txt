
idf_component_register(SRCS "lv_port_disp.c"
                            "lv_port_indev.c"
                       INCLUDE_DIRS "."
                       REQUIRES lvgl gt911 ft6x36 ssd1963 MCAL )
