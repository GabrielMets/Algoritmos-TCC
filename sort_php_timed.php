<?php

$nomeArquivoEntrada = $argv[1];

$linhas = file($nomeArquivoEntrada, FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);
$dados = array_map('intval', $linhas);

$inicio = microtime(true); //inicio
sort($dados);               //ordena
$fim = microtime(true);     //fim

$duracao = $fim - $inicio;

$pastaAtual = basename(getcwd());
$linhaCSV = sprintf("%s;%s;%.6f\n", $pastaAtual, $nomeArquivoEntrada, $duracao);

$nomeCSV = 'tempos_ordenacao_php_timed.csv';
$novoArquivo = !file_exists($nomeCSV);

$fp = fopen($nomeCSV, 'a');
if ($novoArquivo) {
    fwrite($fp, "Pasta;Arquivo;Tempo_Segundos\n");
}
fwrite($fp, $linhaCSV);
fclose($fp);

