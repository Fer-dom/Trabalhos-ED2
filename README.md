# Arch Arcanum - Projeto de Estrutura de Dados II

**Autor:** Fernando Rezende Domingues  
**Matrícula:** 32321BSI022  

---

## 1. Tema e Justificativa (Parte 1)

O **Arch Arcanum** é um jogo do gênero *roguelike deckbuilder* com temática de fantasia arcana.  
O jogador é um **Arcanista Renegado** que se aventura no **Vazio Proibido**, usando seu grimório de feitiços (cartas) para enfrentar inimigos e eventos.  

Escolhi este tema pela sua afinidade com conceitos da computação, permitindo integrar de forma natural e criativa os tópicos da disciplina de **Estruturas de Dados II**.  
Além disso, roguelikes baseados em cartas usam **sistemas procedurais, mapas em grafo e gerenciamento de recursos**, o que se encaixa perfeitamente nos algoritmos estudados.

---

## 2. Visão Geral das Funcionalidades
- **Sistema de combate por turnos** baseado em cartas.  
- **Mapa procedural** gerado como um grafo de salas conectadas.  
- **Fragmentos Etéreos** recompensam o jogador, sendo purificados por algoritmos de compressão.  
- **Testes interativos** para cada algoritmo implementado (busca, compressão, hashing, grafos).  
- **Menu principal** para escolher entre jogar ou rodar os testes.

---

## 3. Integração da Ementa
Cada tópico da ementa da disciplina foi adaptado como mecânica do jogo:

- **Grafos (Mapa do Vazio)**: o mundo é gerado como um grafo de salas (combate, eventos, fogueiras, chefe).  
  - *Dijkstra/A***: usado para sugerir caminhos de menor custo.  
  - *Fluxo Máximo*: planejado para a luta final, onde o jogador sela o coração do Vazio.  

- **Algoritmos de Busca**:  
  - *Busca Sequencial*: procurar cartas na mão durante o turno.  
  - *Busca Binária*: consultar grimórios ordenados.  
  - *Rabin-Karp*: decifrar marcas de corrupção em textos arcanos.  

- **Hashing**: usado como mecânica de "Quebra de Selos" e para gerar identificadores únicos de fragmentos ou cartas.  

- **Compressão de Dados**:  
  - *Huffman*: purificação de fragmentos secretos.  
  - *RLE (planejado)*: usado em runas repetitivas ou profecias.  

- **Teoria da Complexidade (NP-Difícil)**: minigame planejado baseado no Problema do Caixeiro Viajante (reativar nexos de energia).  

- **Algoritmos Gulosos**:  
  - *Mochila Fracionária*: sugerir melhores jogadas no turno (razão efeito/custo).  
  - *Escalonamento de Intervalos*: inimigos temporais que agendam maldições.  

- **Programação Dinâmica**:  
  - *Mochila 0/1*: otimizar o grimório (deck) respeitando limites de páginas arcanas.  

---

## 4. Implementações Concluídas (Parte 2)

### Algoritmos de Busca
- Sequencial
- Binária
- Rabin-Karp

### Compressão
- Huffman (compressão e descompressão de fragmentos)

### Hashing
- DJB2 (simpleHash)
- Folding (shift e boundary)

### Loop de Jogo
- Combate por turnos com IA simples de inimigos.  
- Recompensa pós-batalha com purificação (Huffman).  

---

## 5. Módulo de Grafos (Parte 3)

### Representações
- **Lista de Adjacência** (armazenamento principal).  
- **Matriz de Adjacência** (gerada para visualização).  

### Operações
- Adicionar/remover vértices e arestas.  
- Imprimir lista de adjacência.  
- Imprimir matriz de adjacência.  

### Algoritmos Implementados
- **DFS** (exploração em profundidade).  
- **BFS** (exploração em largura / menor nº de saltos).  
- **Dijkstra** (caminho mínimo ponderado).  
- **Coloração (Welch-Powell)** (alocação de recursos sem conflito).  
- **Ordenação Topológica (Kahn)** (sequência de habilidades/missões).  
- **Árvore Geradora Mínima (Kruskal)** (rede de rotas de custo mínimo).  

### Integração no Jogo
- `StageMap` gera o mundo como grafo.  
- `Game` usa salas conectadas (grafo).  
- `TestesModule` demonstra todos os algoritmos separadamente, com visualização.

---

## 6. Como Compilar e Executar

### Compilação (Linux/WSL)
---
g++ -std=c++20 -Iinclude src/**/*.cpp main.cpp -o arch_arcanum

### Compilação (Windows - MinGW)
---
g++ src/main.cpp src/TestesModule.cpp src/game_logic/*.cpp src/algoritmos/*.cpp -I include -o ArchArcanum.exe -std=c++17

### Execução
---
./arch_arcanum   # Linux
./ArchArcanum.exe # Windows

### Menu Principal

=========================================
               ARCH ARCANUM
=========================================
1. Iniciar combate (jogo)
2. Executar Testes de Algoritmos
0. Sair

## 7. Análise de Complexidade
| Algoritmo              | Complexidade (Pior Caso) | Uso no Projeto                  |
| ---------------------- | ------------------------ | ------------------------------- |
| Busca Sequencial       | O(N)                     | Procurar carta na mão           |
| Busca Binária          | O(log N)                 | Consultar grimórios ordenados   |
| Rabin-Karp             | O(N·M) / O(N+M) médio    | Decifrar padrões de corrupção   |
| Hashing (DJB2/Folding) | O(L)                     | Geração de IDs e verificação    |
| Huffman                | O(N log N)               | Purificação de fragmentos       |
| DFS / BFS              | O(V+E)                   | Exploração do mapa / propagação |
| Dijkstra               | O((V+E) log V)           | Caminho mais seguro             |
| Welch-Powell           | O(V²)                    | Alocação de cores/recursos      |
| Ordenação Topológica   | O(V+E)                   | Dependências de missões         |
| Kruskal (MST)          | O(E log E)               | Rede mínima de teleporte        |

## 8. Próximas Etapas

NP-Difícil: minigame de Caixeiro Viajante para estabilizar nexos de energia.

Gulosos: estratégias rápidas no turno (mochila fracionária, escalonamento).

Dinâmica: mochila 0/1 para otimizar grimório antes da aventura.

Interface Gráfica: migrar do console para SFML