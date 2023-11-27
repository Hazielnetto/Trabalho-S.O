@ECHO off

chcp 65001
cd %cd%

cls

set /p in= "Arquivo de entrada: "
pause
set /p loop= "Quantos loops? "
set "i=1"
del log.txt
del log.csv

:loop
if %i% leq %loop% (
    ECHO --- %i%ª REPETIÇÃO --- >> log.txt
    ECHO. >> log.txt
    ECHO.^          ##### Python ##### >> log.txt
    :: python "Trabalho S.O Buffer.py" %in%
    bufferPython.exe %in%

    ECHO. >> log.txt
    ECHO.^          ##### Java ##### >> log.txt
    :: java "Trabalho_SO_Buffer.java" %in%
    java -jar buffer.jar %in%

    ECHO. >> log.txt
    ECHO.^          ##### Delphi ##### >> log.txt
    echo %in%| bufferDelphi.exe 
    echo.

    ECHO LOG: log.txt & log.csv
    ECHO. >> log.txt
    ECHO.^______________________LOG END______________________ >> log.txt
    ECHO. >> log.txt

    set /a i+=1
    goto loop
)

@REM txtTocsv.exe

pause