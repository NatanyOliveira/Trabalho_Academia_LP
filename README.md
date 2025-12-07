# Explicação dos passos que eu implementei e como compilar (guia para quem clona do GitHub)

Este arquivo serve como um guia rápido e direto para qualquer pessoa que clonar o repositório Trabalho_Academia_LP e desejar compilar e executar o sistema localmente. Ele descreve apenas o essencial para que o projeto seja configurado e colocado em funcionamento, permitindo que o usuário compreenda rapidamente o que é necessário para rodar a aplicação no ambiente local.

---

## 1) Clonar o repositório (passo a passo)

Abra um terminal (PowerShell no Windows, ou um terminal Bash no Linux/WSL/macOS) e execute:

```bash
git clone https://github.com/NatanyOliveira/Trabalho_Academia_LP.git
cd Trabalho_Academia_LP/codigo_base
```

Observação: o código-fonte principal está na pasta `codigo_base`.

---

## 2) Pré-requisitos

- Ter um compilador C++ instalado (g++). Sugestões:
  - Windows: MSYS2 / MinGW-w64 (ou usar WSL).
  - Ubuntu/Debian: `sudo apt update && sudo apt install build-essential`.
  - macOS: instale Xcode Command Line Tools (`xcode-select --install`).

- Opcional: `make` se preferir usar o Makefile.

---

## 3) Compilação (comandos exatos)

Escolha o comando adequado ao seu sistema.

- Windows (PowerShell):

```powershell
cd "C:\caminho\para\Trabalho_Academia_LP\codigo_base"
g++ -std=c++11 -O2 *.cpp -o sgtp.exe
# executar
.\sgtp.exe
```

- Linux / WSL / macOS (bash):

```bash
cd /caminho/para/Trabalho_Academia_LP/codigo_base
g++ -std=c++11 -O2 *.cpp -o sgtp
# executar
./sgtp
```

Se preferir usar `make` (quando disponível):

```bash
make
# e depois
.\sgtp.exe   # no Windows (PowerShell)
./sgtp       # no Linux/macOS
```

## 5) Fluxo mínimo de teste (manual)

1. Execute o programa (`.\sgtp.exe` ou `./sgtp`).
2. No menu principal escolha `1` para Gerenciar Exercícios:
	- `1` para cadastrar Cardio, preencha nome/duração/calorias por minuto.
	- `2` para cadastrar Força, preencha nome/carga/séries/repetições/descanso.
3. Volte para o menu principal e escolha `2` para Gerenciar Fichas:
	- `1` para criar uma ficha (informe nome).
	- `2` para adicionar exercício à ficha (informe ID da ficha e ID do exercício).
	- `3` para visualizar fichas e conferir totais de tempo/calorias.
4. Do menu principal escolha `3` para Registrar Treino (selecionar a ficha realizada). Isso adicionará uma linha em `historico.txt`.
5. Verifique `historico.txt` para confirmar o registro.
