#include "Cardio.h"
#include <iostream>

// Construtor para novos cadastros
Cardio::Cardio(std::string nome, int duracao, double caloriasPorMinuto) 
    : Exercicio(nome) {
    // Sou aluno: aqui eu guardo os valores do cardio quando o usuário cadastra
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Construtor para leitura de arquivo
Cardio::Cardio(int id, std::string nome, bool ativo, int duracao, double caloriasPorMinuto)
    : Exercicio(id, nome, ativo) {
    // Construtor usado ao ler do arquivo
    this->duracao = duracao;
    this->caloriasPorMinuto = caloriasPorMinuto;
}

// Exibir detalhes do exercício
void Cardio::exibirDetalhes() const {
    // Exibe informações básicas do cardio
    std::cout << "[Cardio] ID: " << id << " | Nome: " << nome;
    std::cout << " | Status: " << (ativo ? "Ativo" : "Inativo");
    std::cout << " | Duracao: " << duracao << " min";
    std::cout << " | Cal/min: " << caloriasPorMinuto << std::endl;
}

// Calcular tempo estimado (duração em minutos)
double Cardio::calcularTempoEstimado() const {
    // O tempo estimado é exatamente a duração em minutos
    return static_cast<double>(duracao);
}

// Calcular calorias gastas
double Cardio::calcularCaloriasGastas() const {
    // Calorias = duracao * caloriasPorMinuto
    return duracao * caloriasPorMinuto;
}

// Retornar tipo do exercício (1 = Cardio)
int Cardio::getTipo() const {
    return 1;
}

// Getter de duração
int Cardio::getDuracao() const {
    return duracao;
}

// Getter de calorias por minuto
double Cardio::getCaloriasPorMinuto() const {
    return caloriasPorMinuto;
}
