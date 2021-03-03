@echo off
call env.bat
:RUN
west build -b nrf52840dongle_nrf52840
pause
goto RUN