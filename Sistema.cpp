#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Deletar ponteiros de exercicios e fichas para liberar memória
    for (Exercicio* e : exercicios) {
        delete e;
    }
    exercicios.clear();
    for (Ficha* f : fichas) {
        delete f;
    }
    fichas.clear();
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {
    // Carregar exercicios.txt
    exercicios.clear();
    std::ifstream inEx("exercicios.txt");
    if (inEx.is_open()) {
        std::string linha;
        while (std::getline(inEx, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string token;
            // Ler tipo
            std::getline(ss, token, ';');
            int tipo = std::stoi(token);
            // id
            std::getline(ss, token, ';'); int id = std::stoi(token);
            // nome
            std::getline(ss, token, ';'); std::string nome = token;
            if (tipo == 1) {
                // Cardio: DURACAO;CALORIAS_POR_MIN;STATUS
                std::getline(ss, token, ';'); int dur = std::stoi(token);
                std::getline(ss, token, ';'); double cpm = std::stod(token);
                std::getline(ss, token, ';'); int status = std::stoi(token);
                Cardio* c = new Cardio(id, nome, status==1, dur, cpm);
                exercicios.push_back(c);
            } else if (tipo == 2) {
                // Forca: CARGA;SERIES;REPETICOES;DESCANSO;STATUS
                std::getline(ss, token, ';'); double carga = std::stod(token);
                std::getline(ss, token, ';'); int series = std::stoi(token);
                std::getline(ss, token, ';'); int reps = std::stoi(token);
                std::getline(ss, token, ';'); int descanso = std::stoi(token);
                std::getline(ss, token, ';'); int status = std::stoi(token);
                Forca* f = new Forca(id, nome, status==1, carga, series, reps, descanso);
                exercicios.push_back(f);
            }
        }
        inEx.close();
    }

    // Carregar fichas
    fichas.clear();
    std::ifstream inFich("fichas.txt");
    if (inFich.is_open()) {
        std::string linha;
        while (std::getline(inFich, linha)) {
            if (linha.empty()) continue;
            std::stringstream ss(linha);
            std::string token;
            // idFicha
            std::getline(ss, token, ';'); int idFicha = std::stoi(token);
            // nomeFicha
            std::getline(ss, token, ';'); std::string nomeFicha = token;
            // total
            std::getline(ss, token, ';'); int total = std::stoi(token);
            Ficha* f = new Ficha(idFicha, nomeFicha);
            for (int i = 0; i < total; ++i) {
                std::getline(ss, token, ';'); int idEx = std::stoi(token);
                Exercicio* ex = buscarExercicioPorId(idEx);
                if (ex) f->adicionarExercicio(ex);
            }
            fichas.push_back(f);
        }
        inFich.close();
    }

    // Carregar historico (por fim)
    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    std::ofstream outEx("exercicios.txt");
    if (outEx.is_open()) {
        for (Exercicio* e : exercicios) {
            if (!e) continue;
            int tipo = e->getTipo();
            if (tipo == 1) {
                Cardio* c = dynamic_cast<Cardio*>(e);
                outEx << "1;" << c->getId() << ";" << c->getNome() << ";"
                      << c->getDuracao() << ";" << c->getCaloriasPorMinuto() << ";" << (c->isAtivo()?1:0) << "\n";
            } else if (tipo == 2) {
                Forca* f = dynamic_cast<Forca*>(e);
                outEx << "2;" << f->getId() << ";" << f->getNome() << ";"
                      << f->getCarga() << ";" << f->getSeries() << ";" << f->getRepeticoes() << ";"
                      << f->getTempoDescanso() << ";" << (f->isAtivo()?1:0) << "\n";
            }
        }
        outEx.close();
    }

    // Salvar fichas.txt
    std::ofstream outF("fichas.txt");
    if (outF.is_open()) {
        for (Ficha* f : fichas) {
            if (!f) continue;
            outF << f->getId() << ";" << f->getNome() << ";" << f->getExercicios().size();
            for (Exercicio* e : f->getExercicios()) {
                if (e) outF << ";" << e->getId();
            }
            outF << "\n";
        }
        outF.close();
    }

    // Salvar histórico
    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (Exercicio* e : exercicios) {
        if (e && e->getId() == id) return e;
    }
    return nullptr;
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {
    for (Ficha* f : fichas) {
        if (f && f->getId() == id) return f;
    }
    return nullptr;
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    limparTela();
    std::cout << "Cadastrar Exercicio" << std::endl;
    std::cout << "1. Cardio\n2. Forca\nOpcao: ";
    int tipo; std::cin >> tipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (tipo == 1) {
        std::string nome; int dur; double cpm;
        std::cout << "Nome: "; std::getline(std::cin, nome);
        std::cout << "Duracao (min): "; std::cin >> dur;
        std::cout << "Calorias por minuto: "; std::cin >> cpm;
        Cardio* c = new Cardio(nome, dur, cpm);
        exercicios.push_back(c);
        std::cout << "Cardio cadastrado com ID " << c->getId() << std::endl;
    } else if (tipo == 2) {
        std::string nome; double carga; int series, reps, descanso;
        std::cout << "Nome: "; std::getline(std::cin, nome);
        if (nome.empty()) std::getline(std::cin, nome);
        std::cout << "Carga (kg): "; std::cin >> carga;
        std::cout << "Series: "; std::cin >> series;
        std::cout << "Repeticoes: "; std::cin >> reps;
        std::cout << "Tempo descanso (s): "; std::cin >> descanso;
        Forca* f = new Forca(nome, carga, series, reps, descanso);
        exercicios.push_back(f);
        std::cout << "Forca cadastrada com ID " << f->getId() << std::endl;
    } else {
        std::cout << "Opcao invalida" << std::endl;
    }
    pausar();
}

// Listar exercícios ativos
void Sistema::listarExercicios() {
    limparTela();
    std::cout << "=== Exercicios Ativos ===" << std::endl;
    for (Exercicio* e : exercicios) {
        if (e && e->isAtivo()) {
            e->exibirDetalhes();
        }
    }
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio() {
    limparTela();
    std::cout << "ID do exercicio para desativar: ";
    int id; std::cin >> id;
    Exercicio* e = buscarExercicioPorId(id);
    if (e) {
        e->desativar();
        std::cout << "Exercicio desativado." << std::endl;
    } else {
        std::cout << "Exercicio nao encontrado." << std::endl;
    }
    pausar();
}

// Criar nova ficha
void Sistema::criarFicha() {
    limparTela();
    std::cout << "Nome da nova ficha: ";
    std::string nome; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::getline(std::cin, nome);
    Ficha* f = new Ficha(nome);
    fichas.push_back(f);
    std::cout << "Ficha criada com ID " << f->getId() << std::endl;
    pausar();
}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {
    limparTela();
    std::cout << "ID da ficha: "; int idF; std::cin >> idF;
    Ficha* f = buscarFichaPorId(idF);
    if (!f) { std::cout << "Ficha nao encontrada." << std::endl; pausar(); return; }
    std::cout << "ID do exercicio a adicionar: "; int idE; std::cin >> idE;
    Exercicio* e = buscarExercicioPorId(idE);
    if (!e) { std::cout << "Exercicio nao encontrado." << std::endl; pausar(); return; }
    f->adicionarExercicio(e);
    std::cout << "Exercicio adicionado na ficha." << std::endl;
    pausar();
}

// Listar todas as fichas
void Sistema::listarFichas() {
    limparTela();
    std::cout << "=== Fichas Cadastradas ===" << std::endl;
    for (Ficha* f : fichas) {
        if (f) {
            f->exibirFicha();
            std::cout << "-------------------------" << std::endl;
        }
    }
    pausar();
}

// Registrar treino realizado
void Sistema::registrarTreino() {
    limparTela();
    std::cout << "ID da ficha realizada: "; int idF; std::cin >> idF;
    Ficha* f = buscarFichaPorId(idF);
    if (!f) { std::cout << "Ficha nao encontrada." << std::endl; pausar(); return; }
    double tempo = f->calcularTempoTotal();
    double calorias = f->calcularCaloriasTotais();
    RegistroTreino r;
    r.dataHora = getDataHoraAtual();
    r.idFicha = f->getId();
    r.nomeFicha = f->getNome();
    r.tempoTotal = tempo;
    r.caloriasTotal = calorias;
    historico.adicionarRegistro(r);
    historico.salvarEmArquivo();
    std::cout << "Treino registrado: " << r.dataHora << " | Tempo: " << tempo << " | Calorias: " << calorias << std::endl;
    pausar();
}

// Exibir histórico de treinos
void Sistema::exibirHistorico() {
    limparTela();
    historico.exibirHistorico();
    pausar();
}
