# Projeto de Estrutura de Dados - Arch Arcanum (Etapa 1: Algoritmos de Busca)

**Autor:** Fernando Rezende Domingues
**Matrícula:** 32321BSI022

## Visão Geral da Entrega

Este projeto implementa os algoritmos de busca **Sequencial, Binária e Rabin-Karp** dentro da estrutura de um jogo de RPG no estilo roguelike deck-builder. O objetivo é demonstrar não apenas a implementação correta dos algoritmos, mas também sua aplicação prática em diferentes contextos de um software funcional.

## Como Testar e Demonstrar

O programa oferece duas formas principais de demonstrar os algoritmos de busca:

### 1. Módulo de Testes Isolados (Opção 2 do Menu)

Esta é a forma mais direta de validar cada algoritmo. Ao selecionar a **opção 2**, o programa iniciará uma série de demonstrações interativas:

* **Busca Sequencial:** Uma lista pequena e desordenada (simulando a mão de um jogador) é apresentada. O usuário pode digitar o nome de uma carta para ver o algoritmo percorrer a lista item por item.
* **Busca Binária:** Uma lista maior (simulando uma biblioteca de feitiços) é criada e ordenada. O usuário pode então buscar por uma carta para testemunhar a eficiência da busca binária, que encontra o resultado em poucas comparações.
* **Rabin-Karp:** Um texto base é apresentado, e o usuário pode digitar uma "palavra-chave" para que o algoritmo encontre sua posição no texto.

### 2. Integração no Jogo Funcional (Opção 1 do Menu)

Para demonstrar a aplicação prática, a **Busca Sequencial** foi integrada diretamente no loop de combate do jogo.

* Ao selecionar a **opção 1**, um combate se inicia.
* No turno do jogador, a sua mão de cartas é exibida.
* Ao digitar o nome de uma das cartas da mão (e.g., "Raio Etereo"), o sistema utiliza a **Busca Sequencial** para localizar a carta no vetor da mão e aplicar seu efeito no jogo.

## Análise de Complexidade (Big O)

A tabela abaixo resume a eficiência de cada algoritmo de busca implementado.

| Algoritmo        | Complexidade de Tempo (Pior Caso) | Aplicação e Contexto no Jogo                                                              |
| :--------------- | :----------------------------------- | :------------------------------------------------------------------------------------------- |
| **Busca Sequencial** | $$O(N)$$                            | **Mão do jogador:** Ideal para um número pequeno e variável de itens que não precisam de ordenação. |
| **Busca Binária** | $$O(\log N)$$                       | **Biblioteca/Grimório:** Performance superior para coleções grandes e estáticas que podem ser mantidas em ordem. |
| **Rabin-Karp** | $$O(N \cdot M)$$                    | **Pesquisa textual:** Ferramenta especializada para encontrar padrões em descrições de cartas ou lore do jogo. |


## Como Compilar e Executar

O projeto foi desenvolvido em C++ e compilado com g++ (MinGW) no Windows.

1.  **Pré-requisito:** Compilador g++ configurado no PATH do sistema.
2.  **Navegar para a Pasta Raiz:** `cd /caminho/para/o/projeto/Arch`
3.  **Compilar:**
    ```powershell
    g++ src/main.cpp src/TestesModule.cpp src/game_logic/Card.cpp src/game_logic/Player.cpp src/game_logic/Inimigo.cpp src/game_logic/Game.cpp src/game_logic/CardLibrary.cpp src/algoritmos/Busca.cpp -I include -o ArchArcanum.exe -std=c++17
    ```
4.  **Executar:**
    ```powershell
    ./ArchArcanum.exe
    ```