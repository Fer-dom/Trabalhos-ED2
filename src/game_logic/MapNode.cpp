#include "../../include/game_logic/MapNode.hpp"

MapNode::MapNode(int id, int layer, NodeType type) {
    this->id = id;
    this->layer = layer;
    this->type = type;
    this->visited = false;
}