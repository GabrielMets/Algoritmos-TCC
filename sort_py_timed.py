import sys
import os
import time
import csv

def main():

    nome_arquivo_entrada = sys.argv[1]
    pasta = os.path.basename(os.getcwd())
    nome_csv = "tempos_ordenacao_py_timed.csv"

    with open(nome_arquivo_entrada, "r") as f:
        dados = [int(linha) for linha in f if linha.strip()]

    inicio = time.perf_counter() #inicio
    dados.sort()                #ordena
    fim = time.perf_counter()   #fim

    duracao = fim - inicio

    #verificar se o arquivo CSV já existe
    novo_arquivo = not os.path.exists(nome_csv)

    #CSV para acrescentar resultados
    with open(nome_csv, "a", newline="") as csvfile:
        escritor = csv.writer(csvfile, delimiter=';')
        if novo_arquivo:
            escritor.writerow(["Pasta", "Arquivo", "Tempo_Segundos"])
        escritor.writerow([pasta, nome_arquivo_entrada, f"{duracao:.6f}"])

if __name__ == "__main__":
    main()

