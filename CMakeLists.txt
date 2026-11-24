cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.3.1)
set(toolchainVersion 15_2_Rel1)
set(picotoolVersion 2.3.1)

# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(sigma-os C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# This is where you add new source files
add_executable(omega-os
    src/main.c
)

pico_set_program_name(omega-os "sigma-os")
pico_set_program_version(omega-os "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(omega-os 1)
pico_enable_stdio_usb(omega-os 1)

# Add any pico libraries you use here to link them
target_link_libraries(omega-os
    # Core runtime & standard I/O
    pico_stdlib

    # Kernel scheduling, syscalls & interrupts
    hardware_exception
    hardware_irq
    hardware_timer
    hardware_clocks

    # Synchronization & SMP (dual-core)
    pico_sync
    pico_multicore
    hardware_sync

    # Hardware peripheral drivers (keep what you need)
    hardware_gpio
    hardware_spi
    hardware_i2c
    hardware_pwm
    hardware_pio
    hardware_dma
    hardware_flash
)

# Add the standard include files to the build
target_include_directories(omega-os 
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src
)

pico_add_extra_outputs(omega-os)
