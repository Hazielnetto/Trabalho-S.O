@ECHO off

for /f "tokens=1-3 delims=:." %%a in ("%TIME%") do (
  set hour=%%a
  set minute=%%b
  set second=%%c
)

set year=%date:~-4%
set month=%date:~3,2%
set day=%date:~0,2%

chcp 65001
cd %cd%

cls

set /p in= "Arquivo de entrada: "
pause

ECHO. >> log.txt
ECHO        %day%/%month%/%year%  %hour%:%minute%:%second% >> log.txt
ECHO. >> log.txt
ECHO.^          ##### Rodando o script Python ##### >> log.txt
:: python "Trabalho S.O Buffer.py" %in%
buffer.exe %in%

ECHO. >> log.txt
ECHO.^          ##### Rodando a classe Java ##### >> log.txt
:: java "Trabalho_SO_Buffer.java" %in%
java -jar buffer.jar %in%

ECHO LOG: output.txt 
ECHO. >> log.txt
ECHO.^______________________LOG END______________________ >> log.txt

pause