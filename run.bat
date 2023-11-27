@ECHO off

chcp 65001
cd %cd%

cls

set /p in= "Arquivo de entrada: "
pause

ECHO. >> log.txt
ECHO.^          ##### Python ##### >> log.txt
:: python "Trabalho S.O Buffer.py" %in%
buffer.exe %in%

ECHO. >> log.txt
ECHO.^          ##### Java ##### >> log.txt
:: java "Trabalho_SO_Buffer.java" %in%
java -jar buffer.jar %in%

ECHO. >> log.txt
ECHO.^          ##### Delphi ##### >> log.txt
bufferDelphi.exe %in%

ECHO LOG: log.txt & log.csv
ECHO. >> log.txt
ECHO.^______________________LOG END______________________ >> log.txt
ECHO. >> log.txt

txtTocsv.exe

pause