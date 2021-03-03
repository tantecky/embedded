@echo on
@call env.bat
:RUN
west flash
pause
@goto:RUN