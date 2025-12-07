#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    std::cout << "=== HISTORICO DE TREINOS ===" << std::endl;
    for (const auto& r : registros) {
        std::cout << r.dataHora << " | Ficha ID: " << r.idFicha << " | " << r.nomeFicha
                  << " | Tempo(min): " << r.tempoTotal << " | Calorias: " << r.caloriasTotal << std::endl;
    }
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    return registros;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    registros.clear();
    std::ifstream in("historico.txt");
    if (!in.is_open()) return;
    std::string linha;
    while (std::getline(in, linha)) {
        if (linha.empty()) continue;
        std::stringstream ss(linha);
        RegistroTreino r;
        std::string token;
        // dataHora
        std::getline(ss, token, ';'); r.dataHora = token;
        // idFicha
        std::getline(ss, token, ';'); r.idFicha = std::stoi(token);
        // nomeFicha
        std::getline(ss, token, ';'); r.nomeFicha = token;
        // tempoTotal
        std::getline(ss, token, ';'); r.tempoTotal = std::stod(token);
        // caloriasTotal
        std::getline(ss, token, ';'); r.caloriasTotal = std::stod(token);
        registros.push_back(r);
    }
    in.close();
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream out("historico.txt");
    if (!out.is_open()) return;
    for (const auto& r : registros) {
        out << r.dataHora << ";" << r.idFicha << ";" << r.nomeFicha << ";"
            << r.tempoTotal << ";" << r.caloriasTotal << "\n";
    }
    out.close();
}
