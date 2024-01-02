set(srcs ".")

set(includes  ".")

if(IDF_TARGET STREQUAL "esp32")
    list(APPEND includes "esp32/inc")
    list(APPEND srcs "esp32/src")
    
endif()

if(IDF_TARGET STREQUAL "esp32s2")
    # currently only S2 beta has its own target-specific includes
    list(APPEND includes "esp32s2/inc")
    list(APPEND includes "esp32s2/i2c_manager")
    list(APPEND includes "esp32s2/uart")
    list(APPEND srcs "esp32s2/src")
    list(APPEND srcs "esp32s2/i2c_manager")
    list(APPEND srcs "esp32s2/uart")
endif()

idf_component_register(
                        INCLUDE_DIRS ${includes}
                        SRC_DIRS ${srcs}
                        REQUIRES ssd1963 DRIVERS
                      )