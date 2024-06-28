if (TARGET tinyusb_device)

	add_compile_options(-Wall
	        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
	        -Wno-unused-function # we have some for the docs that aren't called
	        -Wno-maybe-uninitialized
	        )

    add_executable(bme280_sensor
            sample_main.c
            bme280/bme280.c
            bme280/pico_userspace.c
            )

    # pull in common dependencies
    target_link_libraries(bme280_sensor 
    					pico_stdlib  
    					hardware_i2c 
    					)

    # enable usb output, disable uart output
    pico_enable_stdio_usb(bme280_sensor 1)
    pico_enable_stdio_uart(bme280_sensor 0)

    # create map/bin/hex/uf2 file etc.
    pico_add_extra_outputs(bme280_sensor)

elseif(PICO_ON_DEVICE)
    message(WARNING "not building bme280_sensor because TinyUSB submodule is not initialized in the SDK")
endif()
