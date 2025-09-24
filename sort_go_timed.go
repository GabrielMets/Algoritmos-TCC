package main

import (
	"bufio"
	"encoding/csv"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strconv"
	"time"
)

func main() {

	nomeArquivoEntrada := os.Args[1]

	file, err := os.Open(nomeArquivoEntrada)
	
	defer file.Close()

	var dados []int
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		numStr := scanner.Text()
		num, _ := strconv.Atoi(numStr)
		
		dados = append(dados, num)
	}

	inicio := time.Now() //inicio
	sort.Ints(dados)    //ordena
	fim := time.Now()   //fim

	duracao := fim.Sub(inicio).Seconds()

	cwd, err := os.Getwd()
	
	pasta := filepath.Base(cwd)

	csvFile, err := os.OpenFile("tempos_ordenacao_go_timed.csv", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	
	defer csvFile.Close()

	writer := csv.NewWriter(csvFile)
	writer.Comma = ';'

	stat, err := csvFile.Stat()
	if err == nil && stat.Size() == 0 {
		writer.Write([]string{"Pasta", "Arquivo", "Tempo_Segundos"})
	}

	writer.Write([]string{pasta, nomeArquivoEntrada, fmt.Sprintf("%.6f", duracao)})
	writer.Flush()
}

