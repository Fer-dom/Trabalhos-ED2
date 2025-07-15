#pragma once

#include <string>
#include <vector>
#include <map>

namespace Algoritmos {

    
    struct HuffmanNode {
        char data;               
        unsigned frequencia;       // A frequência do caractere.
        HuffmanNode *esquerda, *direita; 
        HuffmanNode(char data, unsigned frequencia);
    };

    class HuffmanArchiver {
    public:
        
        HuffmanArchiver();

        ~HuffmanArchiver();

        std::string compress(const std::string& texto);

        std::string decompress(const std::string& textoComprimido);

    private:
  
        HuffmanNode* raizDaArvore; 
        std::map<char, std::string> mapaDeCodigos; 

        void construirArvore(const std::string& texto);
        void gerarCodigos(HuffmanNode* no, std::string codigoAtual);
        void limparArvore(HuffmanNode* no);
    };

} 