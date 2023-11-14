chcp 65001
cd %cd%

cls
@ECHO off
set /p in= "Arquivo de entrada: "
pause
del %out%
python "Trabalho S.O Buffer.py" %in% %out%
ECHO Arquivo de saída %in%.txt criado com sucesso
ECHO LOG: output.txt 
pause