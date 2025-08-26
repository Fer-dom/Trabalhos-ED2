#pragma once
#include "MapNode.hpp"
#include <vector>
#include <map>

class StageMap {
public:
    StageMap();
    void generateMap(int depth = 15, int width = 7); 
    void displayConsoleMap() const;    
    MapNode* getCurrentNode() const;
    std::vector<MapNode*> getReachableNodes() const; 
    bool travelToNode(int destinationNodeId);

private:
    std::map<int, MapNode> nodes; 
    int currentNodeId;
};