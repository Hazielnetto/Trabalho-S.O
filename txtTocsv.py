import csv

# Função para extrair o valor de uma linha do arquivo de texto
def extrair_valor(linha):
    return linha.split(":")[-1].strip()

# Abrir o arquivo de texto
with open("log.txt", "r", encoding="utf-8") as arquivo_txt:
    linhas = arquivo_txt.readlines()

# Inicializar uma lista para armazenar os dados
dados = []

# Processar as linhas e extrair os valores
for i in range(0, len(linhas), 4):
    nome_arquivo = str("video.mp4")  # O nome do arquivo é o mesmo em todos os conjuntos
    tamanho_arquivo_bytes = int(extrair_valor(linhas[i + 1]).split())
    tempo_execucao_segundos = float(extrair_valor(linhas[i + 2]).split())
    tamanho_buffer_bytes = int(extrair_valor(linhas[i + 3]).split())

    conjunto_dados = [
        ["Nome do arquivo", nome_arquivo],
        ["Tamanho do arquivo (Bytes)", tamanho_arquivo_bytes],
        ["Tempo de execucao (segundos)", tempo_execucao_segundos],
        ["Tamanho do buffer (Bytes)", tamanho_buffer_bytes]
    ]
    dados.append(conjunto_dados)

# Escrever os dados em um arquivo CSV
with open("log.csv", mode="w", newline="", encoding="utf-8") as arquivo_csv:
    escritor_csv = csv.writer(arquivo_csv)
    escritor_csv.writerow(["Nome do arquivo", "Tamanho do arquivo (Bytes)", "Tempo de execucao (segundos)", "Tamanho do buffer (Bytes)"])
    for conjunto_dados in dados:
        escritor_csv.writerows([valor for rotulo, valor in conjunto_dados])

print("Arquivo CSV gerado com sucesso.")
