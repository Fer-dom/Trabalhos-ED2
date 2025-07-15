#include "../../include/algoritmos/Busca.hpp" // Inclui o "contrato" que definimos acima
#include <iostream> // Para usar std::cout nos logs de teste

// --- Implementação da Busca Sequencial ---
Card* Algoritmos::buscaSequencial(const std::vector<Card*>& colecao, const std::string& nomeAlvo) {
    int comparacoes = 0;
    for (Card* carta : colecao) {
        comparacoes++;
        if (carta->getName() == nomeAlvo) {
            std::cout << "  [Busca Sequencial] Carta '" << nomeAlvo << "' encontrada! (Apos " << comparacoes << " comparacoes)\n";
            return carta;
        }
    }
    std::cout << "  [Busca Sequencial] Carta '" << nomeAlvo << "' NAO encontrada. (Total de " << comparacoes << " comparacoes)\n";
    return nullptr;
}

// --- Implementação da Busca Binária ---
Card* Algoritmos::buscaBinaria(const std::vector<Card*>& colecaoOrdenada, const std::string& nomeAlvo) {
    int esquerda = 0;
    int direita = colecaoOrdenada.size() - 1;
    int comparacoes = 0;

    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        std::string nomeDoMeio = colecaoOrdenada[meio]->getName();

        if (nomeDoMeio == nomeAlvo) {
            std::cout << "  [Busca Binaria] Carta '" << nomeAlvo << "' encontrada! (Apos " << comparacoes << " comparacoes)\n";
            return colecaoOrdenada[meio];
        }
        if (nomeDoMeio < nomeAlvo) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    std::cout << "  [Busca Binaria] Carta '" << nomeAlvo << "' NAO encontrada. (Total de " << comparacoes << " comparacoes)\n";
    return nullptr;
}

// --- Implementação da Busca de Rabin-Karp ---

// Constantes para o algoritmo de Rabin-Karp
#define d 256 // Número de caracteres no alfabeto ASCII
#define q 113 // Um número primo para o módulo (ajuda a evitar colisões)

int Algoritmos::buscaRabinKarp(const std::string& texto, const std::string& padrao) {
    int M = padrao.length();
    int N = texto.length();
    if (M > N) return -1;

    int p_hash = 0; // hash para o padrão
    int t_hash = 0; // hash para a janela do texto
    int h = 1;

    // Calcula h = (d^(M-1)) % q
    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    // Calcula o hash inicial do padrão e da primeira janela do texto
    for (int i = 0; i < M; i++) {
        p_hash = (d * p_hash + padrao[i]) % q;
        t_hash = (d * t_hash + texto[i]) % q;
    }

    // Desliza a janela sobre o texto
    for (int i = 0; i <= N - M; i++) {
        // Se os hashes são iguais, verifica se é um match real
        if (p_hash == t_hash) {
            int j = 0;
            for (j = 0; j < M; j++) {
                if (texto[i + j] != padrao[j]) {
                    break;
                }
            }
            if (j == M) {
                std::cout << "  [Rabin-Karp] Padrao encontrado no indice " << i << "\n";
                return i;
            }
        }

        // Calcula o hash da próxima janela usando "rolling hash"
        if (i < N - M) {
            t_hash = (d * (t_hash - texto[i] * h) + texto[i + M]) % q;
            if (t_hash < 0) {
                t_hash = (t_hash + q);
            }
        }
    }
    
    std::cout << "  [Rabin-Karp] Padrao nao foi encontrado no texto.\n";
    return -1;
}