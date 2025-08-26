#include "../../include/algoritmos/Busca.hpp"
#include <iostream> 

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

#define d 256 
#define q 113 

int Algoritmos::buscaRabinKarp(const std::string& texto, const std::string& padrao) {
    int M = padrao.length();
    int N = texto.length();
    if (M > N) return -1;

    int p_hash = 0; 
    int t_hash = 0;
    int h = 1;

    for (int i = 0; i < M - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < M; i++) {
        p_hash = (d * p_hash + padrao[i]) % q;
        t_hash = (d * t_hash + texto[i]) % q;
    }

    for (int i = 0; i <= N - M; i++) {
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