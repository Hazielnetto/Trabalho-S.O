
import glob, time, os

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
        fs = bfs

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

        with open(inputf, 'rb') as inputfile:
            with open(outputf, 'wb') as outputfile:
                while True:
                    bloco = inputfile.read(TAMANHO_BUFFER)
                    if not bloco:
                        break
                    outputfile.write(bloco)

        end = time.time()

        print ( style.CYAN  + "\nTamanho do arquivo:",   style.GREEN   ,ofilesize,"Bytes",                    style.MAGENTA + '(',round(filesize,2), fs,')',
                style.CYAN  + "\nTempo de execução: ",   style.GREEN   ,round(end - start,2),"segundos",
                style.CYAN  + "\nTamanho do buffer: ",   style.GREEN   ,TAMANHO_BUFFER,"Bytes",               style.MAGENTA + '(',round(pbyte), bfs,')')

print(style.WHITE)
os.system('cls')

inputf = input(style.CYAN + "Arquivo de entrada: "+style.WHITE)
inputfs = glob.glob(f'{inputf}.*')

if len(inputfs) == 1:
    print(style.RED + f'{inputfs} encontrado')
    inputf = inputfs[0]
elif len(inputfs) > 1:
    print(style.RED + f'Foram encontrados {len(inputfs)} arquivos com o mesmo nome:\n')
    for i, arquivo in enumerate(inputfs):
        print(style.WHITE + f' - {i+1}. {arquivo}')
    i = input(style.CYAN + f'\nSelecione qual arquivo deseja (1 - {len(inputfs)}): '+style.WHITE)
    inputf = inputfs[int(i)-1]      
else:
    print(style.YELLOW + f'Nenhum arquivo foi encontrado com o nome {inputf}.')

outputf = input(style.CYAN + "\nArquivo de saída (txt): ")
if not ('.txt') in outputf:
    outputf=outputf+'.txt'

buffer = 32768

print(style.RED + "\n### INÍCIO ###")

while buffer >= 4:
        main(byte=int(buffer))
        buffer *= .5

print(style.RED + "\n### FIM ###")
print(style.WHITE)

