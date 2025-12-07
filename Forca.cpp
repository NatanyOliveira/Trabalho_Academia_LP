#include "Forca.h"
#include <iostream>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome) {
    // Sou aluno: guardo os valores quando o usuário cria o exercício de força
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo) {
    // Construtor usado na leitura do arquivo
    this->carga = carga;
    this->series = series;
    this->repeticoes = repeticoes;
    this->tempoDescanso = tempoDescanso;
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    // Mostra dados simples do exercício de força
    std::cout << "[Forca] ID: " << id << " | Nome: " << nome;
    std::cout << " | Status: " << (ativo ? "Ativo" : "Inativo");
    std::cout << " | Carga: " << carga << " kg";
    std::cout << " | Series: " << series << " x " << repeticoes;
    std::cout << " | Descanso: " << tempoDescanso << " s" << std::endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    // Fórmula em segundos: (series * repeticoes * 3) + (series * tempoDescanso)
    double segundos = (static_cast<double>(series) * repeticoes * 3.0) + (static_cast<double>(series) * tempoDescanso);
    // Converter para minutos
    return segundos / 60.0;
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    // Fórmula dada: series * repeticoes * carga * 0.15
    return static_cast<double>(series) * static_cast<double>(repeticoes) * carga * 0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}
