#include "../../include/algoritmos/Huffman.hpp"
#include <iostream>
#include <queue>   
#include <vector>  
#include <map>    

struct CompareNodes {
    bool operator()(Algoritmos::HuffmanNode* esq, Algoritmos::HuffmanNode* dir) {
        return esq->frequencia > dir->frequencia;
    }
};

Algoritmos::HuffmanNode::HuffmanNode(char data, unsigned frequencia) {
    this->data = data;
    this->frequencia = frequencia;
    this->esquerda = this->direita = nullptr;
}


Algoritmos::HuffmanArchiver::HuffmanArchiver() : raizDaArvore(nullptr) {}

Algoritmos::HuffmanArchiver::~HuffmanArchiver() {
    limparArvore(raizDaArvore);
}

void Algoritmos::HuffmanArchiver::limparArvore(HuffmanNode* no) {
    if (no == nullptr) return;
    limparArvore(no->esquerda);
    limparArvore(no->direita);
    delete no;
}

void Algoritmos::HuffmanArchiver::construirArvore(const std::string& texto) {
    limparArvore(raizDaArvore);
    raizDaArvore = nullptr;
    mapaDeCodigos.clear();

    std::map<char, unsigned> frequencias;
    for (char c : texto) {
        frequencias[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> minHeap;
    for (auto par : frequencias) {
        minHeap.push(new HuffmanNode(par.first, par.second));
    }

    while (minHeap.size() > 1) {
        HuffmanNode* esq = minHeap.top(); minHeap.pop();
        HuffmanNode* dir = minHeap.top(); minHeap.pop();
        HuffmanNode* topo = new HuffmanNode('$', esq->frequencia + dir->frequencia);
        topo->esquerda = esq;
        topo->direita = dir;
        minHeap.push(topo);
    }

    if (!minHeap.empty()) {
        raizDaArvore = minHeap.top();
    } else {
        raizDaArvore = nullptr;
    }
}

void Algoritmos::HuffmanArchiver::gerarCodigos(HuffmanNode* no, std::string codigoAtual) {
    if (!no) return;
    if (!no->esquerda && !no->direita) {
        mapaDeCodigos[no->data] = codigoAtual;
    }
    gerarCodigos(no->esquerda, codigoAtual + "0");
    gerarCodigos(no->direita, codigoAtual + "1");
}

std::string Algoritmos::HuffmanArchiver::compress(const std::string& texto) {
    if (texto.empty()) return "";
    
    construirArvore(texto);
    gerarCodigos(raizDaArvore, "");

    std::cout << "Codigos de Huffman gerados:\n";
   for (const auto& par : mapaDeCodigos) {
    char key = par.first;
    std::string val = par.second;
    std::cout << "  '" << key << "': " << val << "\n";
}

    std::string textoComprimido = "";
    for (char c : texto) {
        textoComprimido += mapaDeCodigos[c];
    }
    return textoComprimido;
}

std::string Algoritmos::HuffmanArchiver::decompress(const std::string& textoComprimido) {
    if (raizDaArvore == nullptr) {
        return "";
    }

    std::string textoDecodificado = "";
    HuffmanNode* noAtual = raizDaArvore;
    
    if (!noAtual->esquerda && !noAtual->direita) {
        for(size_t i = 0; i < noAtual->frequencia; ++i){
            textoDecodificado += noAtual->data;
        }
        return textoDecodificado;
    }

    for (char bit : textoComprimido) {
        if (bit == '0') {
            noAtual = noAtual->esquerda;
        } else {
            noAtual = noAtual->direita;
        }

        if (noAtual->esquerda == nullptr && noAtual->direita == nullptr) {
            textoDecodificado += noAtual->data;
            noAtual = raizDaArvore;
        }
    }
    return textoDecodificado;
}
