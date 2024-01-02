
#set(includes  "."
              #"esp32s2/i2s")
             # 
#set(srcs "esp32s2/i2s/i2s_lcd.c")


#idf_component_register(
 #                       INCLUDE_DIRS ${includes}
  #                      SRCS ${srcs}
   #                   )

idf_component_register(
            SRC_DIRS 
            "esp32s2/i2s"
			
            
            INCLUDE_DIRS 
            "."
            "esp32s2/i2s"
)

