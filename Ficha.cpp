#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) {
    // Sou aluno: quando crio uma ficha nova, gero um ID automático
    this->nome = nome;
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) {
    this->id = id;
    this->nome = nome;
    // Atualiza o contador estático caso o ID lido seja maior
    if (id >= proximoId) proximoId = id + 1;
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    // Apenas adiciona o ponteiro, sem tomar posse do objeto
    exercicios.push_back(exercicio);
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {
    std::cout << "Ficha ID: " << id << " | Nome: " << nome << std::endl;
    std::cout << "Exercicios:" << std::endl;
    for (size_t i = 0; i < exercicios.size(); ++i) {
        Exercicio* e = exercicios[i];
        if (e) {
            std::cout << " - ";
            e->exibirDetalhes();
        }
    }
    std::cout << "Totais: Tempo (min) = " << calcularTempoTotal()
              << " | Calorias = " << calcularCaloriasTotais() << std::endl;
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {
    double total = 0.0;
    for (Exercicio* e : exercicios) {
        if (e) total += e->calcularTempoEstimado();
    }
    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {
    double total = 0.0;
    for (Exercicio* e : exercicios) {
        if (e) total += e->calcularCaloriasGastas();
    }
    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) proximoId = maiorId + 1;
}
