@set "TL_PATH=E:\Programy\GNU Arm Embedded Toolchain\10 2020-q4-major\bin"
@set PATH=%TL_PATH%;%PATH%
@cd pca10059/mbr/armgcc
@rmdir /S /Q "_build"
@make.exe
@REM pause