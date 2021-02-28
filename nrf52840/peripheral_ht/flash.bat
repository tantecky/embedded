@echo on
@call env.bat
nrfutil pkg generate --hw-version 52 --sd-req=0x00 --application build/zephyr/zephyr.hex --application-version 1 app.zip
nrfutil dfu usb-serial -pkg app.zip -p %FLASH_PORT%