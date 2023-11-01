
import zipfile, time, os

os.system("")

class style():

    BLACK = '\033[30m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    MAGENTA = '\033[35m'
    CYAN = '\033[36m'
    WHITE = '\033[37m'
    UNDERLINE = '\033[4m'
    RESET = '\033[0m'

class main():
    def __init__(self,byte):

        ofilesize = int(os.path.getsize(inputf))
        filesize = ofilesize
        pbyte = byte
        bfs = 'Bytes'

        if filesize >= 10**3:
                fs = 'KB'
                filesize = filesize / 10**3
                if filesize >= 10**3:
                    fs = 'MB'
                    filesize = filesize / 10**3
                    if filesize >= 10**3:
                        fs = 'GB'
                        filesize = filesize / 10**3 

        if byte >= 10**3:
            pbyte = byte / 10**3
            bfs = 'KB'
            if pbyte >= 10**3:
                pbyte = byte / 10**3
                bfs = 'MB'        

        TAMANHO_BUFFER = byte #tamanho em bytes                

        start = time.time()

        with zipfile.ZipFile(inputf,'r') as arquivo_zip:
            for entrada in arquivo_zip.infolist():
                with arquivo_zip.open(entrada) as input_zip, open(outputf, 'wb') as output_zip:
                    while True:
                        buffer = input_zip.read(TAMANHO_BUFFER)
                        if not buffer:
                            break
                        output_zip.write(buffer)

        end = time.time()

        print ( style.CYAN  + "\nTamanho do arquivo:",   style.GREEN   ,ofilesize,"Bytes",                    style.MAGENTA + '(',round(filesize,2),fs,')',
                style.CYAN  + "\nTempo de execução: ",   style.GREEN   ,round(end - start,2),"segundos",
                style.CYAN  + "\nTamanho do buffer: ",   style.GREEN   ,TAMANHO_BUFFER,"Bytes",               style.MAGENTA + '(',round(pbyte),bfs,')')

print(style.WHITE)
os.system('cls')

inputf = input("Arquivo de entrada (zip): ")
outputf = input("Arquivo de saída (txt): ")
if not ('.zip') in inputf: 
    inputf=inputf+'.zip'
if not ('.txt') in outputf:
    outputf=outputf+'.txt'

buffer = 32768

print(style.RED + "### INÍCIO ###")

while buffer >= 4:
        main(byte = int(buffer))
        buffer *= .5

print(style.RED + "\n### FIM ###")
print(style.WHITE)

