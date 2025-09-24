#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>

#define MAX_NUMEROS 20000000
#define NOME_CSV "tempos_ordenacao_c_timed.csv"

//comparação para qsort
int comparar(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {

    char *nome_arquivo_entrada = argv[1];
    FILE *entrada = fopen(nome_arquivo_entrada, "r");
    

    int *dados = malloc(sizeof(int) * MAX_NUMEROS);
    

    int n = 0;
    while (fscanf(entrada, "%d", &dados[n]) == 1) {
        n++;
    }
    fclose(entrada);

    clock_t inicio = clock();   //inicio
    qsort(dados, n, sizeof(int), comparar); //ordena
    clock_t fim = clock();      //fim

    double duracao = (double)(fim - inicio) / CLOCKS_PER_SEC;

    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    char *pasta = basename(cwd);

    FILE *csv = fopen(NOME_CSV, "a");

    fprintf(csv, "%s;%s;%.6f\n", pasta, nome_arquivo_entrada, duracao);

    fclose(csv);
    free(dados);

    return 0;
}

