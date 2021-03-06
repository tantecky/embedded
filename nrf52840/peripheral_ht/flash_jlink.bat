@echo on
@call env.bat
:RUN
west flash
call reset.bat
pause
@goto:RUN