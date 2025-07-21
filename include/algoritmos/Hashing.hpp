#pragma once

#include <string>

namespace Algoritmos {
    unsigned long simpleHash(const std::string& texto);
   unsigned long shiftFoldingHash(const std::string& texto, int chunkSize);
    unsigned long boundaryFoldingHash(const std::string& texto, int chunkSize);
} 