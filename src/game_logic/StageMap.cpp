#include "../../include/game_logic/StageMap.hpp"
#include <iostream>
#include <random> 
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip> 

StageMap::StageMap() {
    this->currentNodeId = -1; 
}

//Geração do Mapa
void StageMap::generateMap(int depth, int width) {
    nodes.clear(); 
    std::random_device rd;
    std::mt19937 gen(rd());
    int nodeIdCounter = 0;
    std::map<int, std::vector<int>> layerNodes;
    MapNode startNode(nodeIdCounter++, 0, NodeType::INICIO);
    nodes[startNode.id] = startNode;
    layerNodes[0].push_back(startNode.id);
    this->currentNodeId = startNode.id;
    for (int i = 1; i < depth; ++i) {
        std::uniform_int_distribution<> distr(2, width - 2);
        int nodesInLayer = distr(gen);
        for (int j = 0; j < nodesInLayer; ++j) {
            MapNode newNode(nodeIdCounter++, i);
            nodes[newNode.id] = newNode;
            layerNodes[i].push_back(newNode.id);
        }
    }
    MapNode bossNode(nodeIdCounter++, depth, NodeType::CHEFE);
    nodes[bossNode.id] = bossNode;
    layerNodes[depth].push_back(bossNode.id);
    for (int i = 0; i < depth; ++i) {
        if (layerNodes.find(i) == layerNodes.end() || layerNodes.find(i + 1) == layerNodes.end()) continue;

        std::vector<int>& currentLayer = layerNodes[i];
        std::vector<int>& nextLayer = layerNodes[i + 1];

        if (nextLayer.empty() || currentLayer.empty()) continue;

        for (int fromNodeId : currentLayer) {
            std::uniform_int_distribution<> connectDist(0, nextLayer.size() - 1);
            int toNodeId = nextLayer[connectDist(gen)];
            nodes[fromNodeId].nextNodeIds.push_back(toNodeId);
        }

        for (int toNodeId : nextLayer) {
            bool isReachable = false;
            for (int fromNodeId : currentLayer) {
                if (std::find(nodes[fromNodeId].nextNodeIds.begin(), nodes[fromNodeId].nextNodeIds.end(), toNodeId) != nodes[fromNodeId].nextNodeIds.end()) {
                    isReachable = true;
                    break;
                }
            }
            if (!isReachable) {
                std::uniform_int_distribution<> connectDist(0, currentLayer.size() - 1);
                int fromNodeId = currentLayer[connectDist(gen)];
                nodes[fromNodeId].nextNodeIds.push_back(toNodeId);
            }
        }
    }

    //5. Atribuir Tipos de Sala Aleatoriamente
    for (auto& pair : nodes) {
        MapNode& node = pair.second;
        if (node.type == NodeType::INDEFINIDO) {
            std::uniform_int_distribution<> typeDist(1, 100);
            int randomType = typeDist(gen);

            if (randomType <= 50) node.type = NodeType::COMBATE;
            else if (randomType <= 65) node.type = NodeType::COMBATE_ELITE;
            else if (randomType <= 80) node.type = NodeType::FOGUEIRA_REPOUSO;
            else if (randomType <= 90) node.type = NodeType::TESOURO;
            else node.type = NodeType::MERCADOR;
        }
    }
}

MapNode* StageMap::getCurrentNode() const {
    if (nodes.count(currentNodeId)) {
        return (MapNode*)&nodes.at(currentNodeId);
    }
    return nullptr;
}

std::vector<MapNode*> StageMap::getReachableNodes() const {
    std::vector<MapNode*> reachable;
    const MapNode* current = getCurrentNode();
    if (current) {
        for (int nextId : current->nextNodeIds) {
            if (nodes.count(nextId)) {
                reachable.push_back((MapNode*)&nodes.at(nextId));
            }
        }
    }
    return reachable;
}

bool StageMap::travelToNode(int destinationNodeId) {
    const MapNode* current = getCurrentNode();
    if (current) {
        for (int nextId : current->nextNodeIds) {
            if (nextId == destinationNodeId) {
                this->currentNodeId = destinationNodeId;
                nodes[destinationNodeId].visited = true;
                return true;
            }
        }
    }
    return false;
}
std::string getNodeIcon(NodeType type, bool isCurrent, bool isReachable) {
    std::string icon = "[ ? ]";
    switch (type) {
        case NodeType::COMBATE:         icon = "[ C ]"; break;
        case NodeType::COMBATE_ELITE:   icon = "[ E ]"; break;
        case NodeType::TESOURO:         icon = "[ T ]"; break;
        case NodeType::MERCADOR:        icon = "[ M ]"; break;
        case NodeType::FOGUEIRA_REPOUSO:icon = "[ F ]"; break;
        case NodeType::CHEFE:           icon = "[ CHEFE ]"; break;
        case NodeType::INICIO:          icon = "[ INICIO ]"; break;
        default: break;
    }

    if (isCurrent) {
        return "-> " + icon + " <-";
    }
    if (isReachable) {
        return " " + icon + "  *";
    }
    return " " + icon + "   ";
}

void StageMap::displayConsoleMap() const {
    std::cout << "\n--- MAPA DA FASE ---\n";

    std::vector<MapNode*> reachable = getReachableNodes();
    std::vector<int> reachableIds;
    for(const auto& node : reachable) {
        reachableIds.push_back(node->id);
    }
    
    std::map<int, std::vector<const MapNode*>> layerNodes;
    int maxLayer = 0;
    for (const auto& pair : nodes) {
        layerNodes[pair.second.layer].push_back(&pair.second);
        if (pair.second.layer > maxLayer) {
            maxLayer = pair.second.layer;
        }
    }

    for (int i = 0; i <= maxLayer; ++i) {
        std::cout << "Camada " << std::setw(2) << i << ": ";
        if (layerNodes.count(i)) {
            std::sort(layerNodes.at(i).begin(), layerNodes.at(i).end(), 
                      [](const MapNode* a, const MapNode* b){ return a->id < b->id; });
            
            for (const auto& node : layerNodes.at(i)) {
                bool isCurrent = (node->id == this->currentNodeId);
                bool isReachable = std::find(reachableIds.begin(), reachableIds.end(), node->id) != reachableIds.end();
                std::cout << getNodeIcon(node->type, isCurrent, isReachable);
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------\n";
}