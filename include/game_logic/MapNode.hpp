#pragma once
#include <vector>

enum class NodeType {
    INDEFINIDO,
    COMBATE,
    COMBATE_ELITE,
    TESOURO,
    MERCADOR,
    FOGUEIRA_REPOUSO,
    CHEFE,
    INICIO
};

class MapNode {
public:
    int id;                 
    NodeType type;         
    int layer;             
    bool visited;

    std::vector<int> nextNodeIds;
    MapNode(int id = -1, int layer = 0, NodeType type = NodeType::INDEFINIDO);
};