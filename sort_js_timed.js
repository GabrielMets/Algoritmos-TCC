const fs = require('fs');
const path = require('path');

const NOME_CSV = 'tempos_ordenacao_js_timed.csv';

const nomeArquivoEntrada = process.argv[2];

//caminho absoluto baseado no diretório atual
const caminhoCompleto = path.resolve(process.cwd(), nomeArquivoEntrada);

const conteudo = fs.readFileSync(caminhoCompleto, 'utf-8');
const dados = conteudo
    .trim()
    .split('\n')
    .map(linha => parseInt(linha.trim(), 10));

const inicio = process.hrtime(); //inicio 
dados.sort((a, b) => a - b); //ordena
const fim = process.hrtime(inicio); //fim

const duracao = fim[0] + fim[1] / 1e9;

const pasta = path.basename(process.cwd());

const linhaCSV = `${pasta};${nomeArquivoEntrada};${duracao.toFixed(6)}\n`;
fs.appendFileSync(NOME_CSV, linhaCSV);

