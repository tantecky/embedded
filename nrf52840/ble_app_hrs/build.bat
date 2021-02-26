@set "TL_PATH=E:\Programy\GNU Arm Embedded Toolchain\10 2020-q4-major\bin"
@set PATH=%TL_PATH%;%PATH%
@cd pca10059/s140/armgcc
@rmdir /S /Q "_build"
@make.exe
pause