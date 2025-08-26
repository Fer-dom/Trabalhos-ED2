#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include <limits> 


struct Edge {
    int to;       
    int weight;   
};

struct NodeDistance {
    int node;     
    int distance; 
    
    bool operator>(const NodeDistance& other) const {
        return distance > other.distance;
    }
};

class Graph {
public:
    // Módulo 1
    Graph();
    void removeEdge(const std::string& from, const std::string& to, bool directed = true);
    void removeVertex(const std::string& vertexName);
    void addVertex(const std::string& vertexName);
    void addEdge(const std::string& from, const std::string& to, int weight, bool directed = true);
    void printAdjList() const;   
    void printAdjMatrix() const; 

    // Módulo 2
    std::vector<std::string> dfs(const std::string& startVertex);
    std::vector<std::string> bfs(const std::string& startVertex);
    std::pair<int, std::vector<std::string>> dijkstra(const std::string& startVertex, const std::string& endVertex);

    // Módulo 3
    std::map<std::string, int> welchPowellColoring();
    std::vector<std::string> topologicalSort();
    Graph kruskalMST();

private:
    std::map<std::string, int> vertexMap;
    std::vector<std::string> inverseVertexMap;
    std::map<int, std::list<Edge>> adjList;
    int getVertexId(const std::string& vertexName) const;
    bool vertexExists(const std::string& vertexName) const;
};