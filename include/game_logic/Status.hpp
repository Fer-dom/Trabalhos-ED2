#pragma once
#include <map>

enum class Status {
    VULNERAVEL, // recebe +50% dano
    FRAQUEZA,   // causa -25% dano
    VENENO      // perde X HP por turno
};

using StatusMap = std::map<Status, int>;
