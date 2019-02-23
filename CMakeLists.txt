CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
project(ARDF_Firmware)

SET(AVRSTRIP avr-strip)
SET(OBJCOPY avr-objcopy)

SET(CMAKE_C_COMPILER avr-gcc)
SET(CMAKE_CXX_COMPILER avr-g++)
SET(CDEBUG "-gstabs")
SET(CWARN "-Wall -Wextra -Wpedantic -Wstrict-prototypes")
SET(CTUNING "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums")
SET(COPT "-O3")
SET(CMCU "-mmcu=attiny44")
SET(CDEFS "-DF_CPU=3600000UL")
SET(CFLAGS "${CMCU} ${CDEBUG} ${CDEFS} ${CINCS} ${COPT} ${CWARN} ${CEXTRA}")
SET(CXXFLAGS "${CMCU} ${CDEFS} ${CINCS} ${COPT}")
SET(CMAKE_C_FLAGS  ${CFLAGS})
SET(CMAKE_CXX_FLAGS ${CXXFLAGS})

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_C_STANDARD 11)

SET(SOURCES main.c timer1.c)

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

add_custom_target(strip ALL ${AVRSTRIP} "${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(${PROJECT_NAME}.hex   ALL ${OBJCOPY} -R .eeprom -O ihex "${PROJECT_NAME}.elf" "${PROJECT_NAME}.hex" DEPENDS strip)
