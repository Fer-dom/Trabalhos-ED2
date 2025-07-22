# Arch Arcanum - Projeto de Estrutura de Dados
Projeto de ED2 - Parte 2
**Autor:** Fernando Rezende Domingues
**Matrícula:** 32321BSI022

## 1. Visão Geral do Projeto

O "Arch Arcanum" é um jogo do gênero roguelike deckbuilder com temática de fantasia arcana. O jogador assume o papel de um Arcanista que explora o perigoso Vazio Proibido, usando um grimório de feitiços para enfrentar seus desafios.

Este repositório documenta a implementação do projeto para a disciplina de Estruturas de Dados, focado na aplicação prática de algoritmos em um software funcional e interativo.

---

## 2. Funcionalidades Implementadas (Etapa Atual)

A versão atual do projeto contém a base funcional do jogo e a implementação completa dos seguintes algoritmos, todos demonstrados de forma interativa:

* **Algoritmos de Busca:**
    * Busca Sequencial
    * Busca Binária
    * Busca por Texto (Rabin-Karp)

* **Algoritmo de Compressão:**
    * Huffman (com compressão e descompressão)

* **Algoritmos de Hashing:**
    * Hashing por Dobramento (Enlaceamento Deslocado e Enlaceamento Limite)

* **Loop de Jogo Funcional:**
    * Um sistema de combate por turnos onde o jogador pode usar cartas de um baralho para atacar, defender e se curar contra um inimigo com IA básica.
    * Um sistema de recompensa pós-batalha que utiliza a compressão de Huffman.

---

## 3. Como Compilar e Executar

O projeto foi desenvolvido em C++ e compilado com g++ (MinGW-w64) no Windows.

1.  **Pré-requisito:** Um compilador C++ moderno (padrão C++17) configurado no PATH do sistema.
2.  **Navegar para a Pasta Raiz:** Abra um terminal e navegue para a pasta principal do projeto (`Arch`).
3.  **Compilar:** Execute o seguinte comando para compilar todos os arquivos-fonte.
    ```powershell
    g++ src/main.cpp src/TestesModule.cpp src/game_logic/*.cpp src/algoritmos/*.cpp -I include -o ArchArcanum.exe -std=c++17
    ```
4.  **Executar:**
    ```powershell
    ./ArchArcanum.exe
    ```
5.  **Navegue pelo Menu:**
    * **Opção 1 (Iniciar Jogo):** Inicia o loop de combate interativo.
    * **Opção 2 (Executar Testes):** Abre um submenu para demonstrar cada algoritmo de forma isolada e interativa.

---

## 4. Análise de Complexidade (Big O)

A tabela abaixo resume a eficiência de cada algoritmo implementado e sua aplicação prática no projeto, conforme observado nos testes.

| Algoritmo                 | Complexidade de Tempo (Pior Caso) | Eficiência e Contexto no Jogo                                                                                                       |
| :------------------------ | :----------------------------------- | :---------------------------------------------------------------------------------------------------------------------------------- |
| **Busca Sequencial** | $$O(N)$$                            | **Mão do jogador:** Perfeitamente eficiente para um número pequeno e variável de itens (5-10 cartas).                               |
| **Busca Binária** | $$O(\log N)$$                       | **Biblioteca/Grimório:** Performance superior para coleções grandes e estáticas que podem ser mantidas em ordem.                      |
| **Rabin-Karp** | $$O(N \cdot M)$$                    | **Pesquisa textual:** Muito rápido no caso médio ($$O(N+M)$$), ideal para encontrar padrões em descrições de cartas.                 |
| **Huffman** | $$O(N \log K)$$                     | **Sistema de Recompensa:** Demonstra excelente taxa de compressão. O custo de construir a árvore é adequado para uma ação fora do combate. |
| **Hashing (Dobramento)** | $$O(L)$$                            | **Geração de Hash:** Instantâneo. O tempo depende apenas do tamanho da string de entrada (`L`), não do tamanho da tabela hash.            |

---

## 5. Visão de Design (Próximas Etapas)

O documento de design original estabelece uma visão ambiciosa para o futuro do "Arch Arcanum", integrando todos os tópicos da ementa da disciplina. As próximas etapas planejadas incluem:

* **Grafos (O Mapa do Vazio):** Implementar o mapa do jogo como um grafo, onde o jogador navega entre os nós (combates, eventos, lojas) usando algoritmos como Dijkstra ou A* para encontrar o caminho mais seguro.
* **Teoria da Complexidade (NP-Difícil):** Criar um minigame baseado no Problema do Caixeiro Viajante.
* **Algoritmos Gulosos e Programação Dinâmica:** Usar os conceitos da Mochila (0/1 e Fracionária) para otimizar as escolhas do jogador.
* **Tecnologias:** Migrar a interface de console para uma biblioteca gráfica como a **SFML**, trazendo o jogo para a vida com elementos visuais.
=======
# Trabalhos-ED2
Projeto de ED2 - Parte 1: Documento de Design -
Arch Arcanum
Autor: Fernando Rezende Domingues Matrícula: 32321BSI022

1. Tema do Projeto e Justificativa:
O projeto "Arch Arcanum" é um jogo do gênero roguelike deckbuilder com temática de fantasia arcana. O jogador é um Arcanista Renegado que se aventura no Vazio Proibido, e seu grimório de cartas representa seu arsenal de magias. Escolhi este tema pela sua forte afinidade com conceitos da computação, permitindo uma integração natural e criativa de todos os tópicos da ementa de Estruturas de Dados II. Além disso, o gênero roguelike deckbuilder é particularmente adequado ao escopo da disciplina, pois sua estrutura procedural e baseada em sistemas se alinha perfeitamente com a aplicação de algoritmos de forma prática e interessante, sendo também um gênero de jogo que eu particularmente gosto bastante.

2. Visão Geral das Funcionalidades:
O jogador navegará por um mapa etéreo (um grafo de fluxos de mana) gerado proceduralmente. Cada nó no mapa é um desafio: um duelo arcano por turnos, uma fonte de mana pura ou um evento narrativo místico. Nos duelos, o jogador usa as cartas da sua mão para atacar as Criaturas do Vazio e superar as Anomalias de Mana, gastando "Essência Arcana" como recurso. Após cada vitória, o jogador é recompensado com "Fragmentos Etéreos", que podem ser purificados e infundidos para obter novos feitiços e fortalecer seu grimório para os desafios futuros. O objetivo é chegar ao Coração do Vazio e selá-lo, impedindo sua corrupção.

3. Integração da Ementa: Uma Jornada Mística pelos Dados
Veja como cada conceito da ementa se manifesta como uma mecânica central e interessante no seu jogo, Arch Arcanum

Grafos (O Mapa do Vazio)
O mapa do Vazio Proibido é um grafo de fluxos de mana, gerado proceduralmente a cada exploração. Os vértices são Manifestações do Vazio (Nós Comuns), Câmaras Ocultas (Nós de Elite), Fontes de Mana Pura (Lojas de Rúnicas/Melhorias), Eventos Místicos (Eventos Aleatórios), e o Coração do Vazio (o chefe da fase). As arestas são os caminhos etéreos ou conexões entre as manifestações.
•	Dijkstra/A* (Traçando o Caminho Etéreo): As conexões (arestas) no mapa do Vazio possuem um custo, que se manifesta como "Corrupção Etérea" ou "Drenagem de Vitalidade" acumulada ao percorrê-las. Antes de cada movimento, o jogador pode utilizar um "Guia Astral" – um módulo que implementa os algoritmos de Dijkstra ou A* – para identificar e destacar o caminho até um ponto de interesse que minimize a Corrupção Etérea total. Se a Corrupção Etérea atingir 100%, o Arcanista sucumbe ao Vazio, encerrando a desventura. Adicionalmente, certos caminhos podem apresentar "barreiras mágicas" que exigem o uso de uma carta específica para serem dissolvidas, introduzindo uma camada estratégica de puzzle.
•	Fluxo Máximo (Selando o Coração do Vazio): O "Coração do Vazio" é protegido por um Escudo de Caos com uma capacidade imensa. A batalha final não é sobre reduzir a vida a zero, mas sim sobre "Canalizar Fluxo de Mana Primordial" para sobrecarregar e selar o Escudo. O algoritmo de Fluxo Máximo determinaria a "vida" total desse escudo com base na topologia da rede de mana que o alimenta. O jogador precisa jogar cartas que geram "Mana Primordial" para vencer.

Algoritmos de Busca (Dentro do Duelo Arcano)
Essas mecânicas são usadas durante os combates por turnos.

Hashing (Mecânica de "Quebra de Selos Elementais"): Certos inimigos (Criaturas do Vazio) terão uma defesa chamada "Essência Cristalizada". O jogador precisa ter uma carta específica de "Quebrador de Essência" na mão. Jogar esta carta contra a defesa Essência Cristalizada a dissolve instantaneamente (simulando uma busca em O(1)), permitindo que outros ataques sejam eficazes, enquanto outras formas de ataque são ineficazes. Isso cria um momento de "fraqueza" a ser explorado pelo jogador.

Busca em Texto (KMP) (Mecânica de "Decifrar Conjurações Antigas"): Algumas cartas, como "Analisador de Resquícios Mágicos" ou "Sussurrador de Ecos", permitem que o jogador investigue os "padrões de energia" ou "memórias etéreas" do inimigo. Ao jogar a carta, o algoritmo de KMP rodaria em segundo plano para procurar por "Sequências Mágicas Vulneráveis" (strings pré-definidas). Se encontradas, o jogador ganha uma recompensa (compra mais cartas, ganha Essência Arcana extra, buff temporário, etc.).

Compressão de Dados (Recompensas e Descobertas Mágicas)
Representa o "loot" que você ganha após vencer um duelo ou evento.

Huffman/RLE (Módulo de "Infundir e Purificar Fragmentos"): Ao vencer, você não ganha feitiços diretamente. Você obtém "Fragmentos Etéreos". De volta ao seu Baluarte Místico (entre os combates ou no final da run), você usa um "Forja Arcana" para purificar e infundir esses fragmentos em novos feitiços. Fragmentos que representam padrões mágicos repetitivos (runas de poder, símbolos elementais) usam RLE, enquanto os de textos arcanos (profecias, invocações esquecidas) usam Huffman. O jogador precisa gerenciar seus recursos para decodificar os fragmentos mais promissores, que podem ter diferentes "qualidades" ou "raridades".

Teoria da Complexidade (NP-Difícil) (Um Desafio Especial)

Problema do Caixeiro Viajante (PCV) (Minigame "Estabilizar Nexos de Energia"): Para quebrar a instabilidade principal de um "Nexus de Energia Caótica" (um tipo raro e difícil de nó no mapa), o jogador precisa primeiro reativar uma série de "Focos de Mana Instáveis" em uma ordem específica para otimizar o fluxo de energia. O minigame apresentaria os focos como nós em um subgrafo e o "custo" de energia arcana ou "dano à vitalidade" para ir de um para o outro. O jogador tem um número limitado de turnos para encontrar um caminho que ative todos eles. O jogo pode usar uma heurística (vizinho mais próximo) para sugerir uma rota, explicando que a solução ótima é um problema NP-Difícil, incentivando o jogador a ponderar riscos e recompensas.
Algoritmos Gulosos (A Estratégia no Turno de Conjuração)
Reflete a tomada de decisão em cada turno do combate.

Mochila Fracionária (Abstração para "Eficiência de Essência Arcana"): No seu turno, você tem X "Pontos de Essência Arcana" (mana). Cada carta (feitiço) tem um custo de Essência e um efeito (dano, escudo, buff). Um jogador iniciante naturalmente usará uma estratégia gulosa: conjurar as cartas com a melhor razão efeito/custo para maximizar o resultado naquele turno. O jogo pode ter uma "Visão Eremita" ou uma "Consciência de Mana" que sugere jogadas baseadas nesse princípio, explicando a "eficiência".

Escalonamento de Intervalos (Mecânica do Inimigo "Maldições Temporais do Vazio"): Um tipo de inimigo (Anomalia Temporal ou Eco do Vazio) não ataca diretamente. Em vez disso, ele agenda várias "Distorções de Realidade Maliciosas" em uma linha do tempo futura (ex: "Congelar Magia em 3 turnos", "Invocar Aberrações em 2 turnos"). O jogador precisa usar suas cartas (feitiços de interrupção ou de limpeza temporal) para interromper o máximo de rotinas agendadas antes que elas sejam executadas. O algoritmo de escalonamento de intervalos ajudaria a determinar qual interrupção maximizaria o impacto.
Programação Dinâmica (A Estratégia Fora do Combate)
Foca no "Deckbuilding" — a montagem do seu grimório.

Mochila 0/1 (Módulo "Configuração do Grimório Pessoal"): Seu "Grimório Pessoal" tem uma capacidade de páginas limitadas (ou "peso arcano"). Cada carta (feitiço) que você possui na sua coleção tem um custo de páginas e um nível de poder mágico. Antes de iniciar uma desventura, você deve escolher quais feitiços da sua coleção total irão para o grimório que você usará. Você não pode exceder o limite de páginas do seu grimório. O jogo terá um botão de "Otimizar Grimório", que usará o algoritmo da Mochila 0/1 para selecionar o conjunto de feitiços que oferece o maior "nível de poder mágico" total sem ultrapassar a capacidade. Isso é uma integração perfeita e extremamente temática para um mago.

Tecnologias Escolhidas:

O projeto será desenvolvido em C++, uma linguagem robusta e performática ideal para jogos. Para a renderização gráfica, gerenciamento de janelas e entrada do usuário, utilizarei a biblioteca multimídia SFML (Simple and Fast Multimedia Library), que é orientada a objetos e adequada para projetos 2D.
=======
