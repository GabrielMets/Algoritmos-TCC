#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <filesystem>

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {

    string nome_arquivo_entrada = argv[1];
    string pasta = filesystem::current_path().filename().string();
    static const string nome_csv = "tempos_ordenacao_cpp_timed.csv";

    ifstream arquivo_entrada(nome_arquivo_entrada);

    vector<int> dados;
    int numero;
    while (arquivo_entrada >> numero) {
        dados.push_back(numero);
    }
    arquivo_entrada.close();

    auto inicio = high_resolution_clock::now(); //inicio
    sort(dados.begin(), dados.end());           //ordena
    auto fim = high_resolution_clock::now();    //fim
    duration<double> duracao = duration_cast<duration<double>>(fim - inicio);

    //Substitui arq se ja existe
    bool novo_arquivo = !filesystem::exists(nome_csv);

    ofstream arquivo_csv(nome_csv, ios::out | ios::app);

    if (novo_arquivo) {
        arquivo_csv << "Pasta;Arquivo;Tempo_Segundos\n";
    }

    arquivo_csv << pasta << ";" << nome_arquivo_entrada << ";" << duracao.count() << "\n";
    arquivo_csv.close();

    return 0;
}

