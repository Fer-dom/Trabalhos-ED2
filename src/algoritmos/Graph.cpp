#include "../../include/algoritmos/Graph.hpp" 
#include <iostream>
#include <iomanip> 
#include <stack>  
#include <queue>  
#include <vector>
#include <algorithm> 
#include <set>

Graph::Graph() {
    
}

void Graph::addVertex(const std::string& vertexName) {
    if (vertexExists(vertexName)) {
        std::cout << "AVISO: Vertice '" << vertexName << "' ja existe. Nao foi adicionado.\n";
        return; 
    }
    int newId = inverseVertexMap.size();
    vertexMap[vertexName] = newId;
    inverseVertexMap.push_back(vertexName);
    adjList[newId] = {}; 
    std::cout << "Vertice '" << vertexName << "' adicionado com ID " << newId << ".\n";
}

void Graph::addEdge(const std::string& from, const std::string& to, int weight, bool directed) {
    if (!vertexExists(from) || !vertexExists(to)) {
        std::cout << "ERRO: Um ou ambos os vertices ('" << from << "', '" << to << "') nao existem. Aresta nao adicionada.\n";
        return; 
    }

    int fromId = getVertexId(from);
    int toId = getVertexId(to);
    adjList[fromId].push_back({toId, weight});
    std::cout << "Rota adicionada de '" << from << "' para '" << to << "' com custo " << weight << ".\n";

    if (!directed) {
        adjList[toId].push_back({fromId, weight});
        std::cout << "  (Rota de mao dupla: '" << to << "' para '" << from << "' tambem adicionada).\n";
    }
}

void Graph::removeEdge(const std::string& from, const std::string& to, bool directed) {
    if (!vertexExists(from) || !vertexExists(to)) {
        std::cout << "ERRO: Vertice(s) inexistente(s): '" << from << "', '" << to << "'.\n";
        return;
    }
    int u = getVertexId(from), v = getVertexId(to);
    auto& lu = adjList[u];
    lu.remove_if([&](const Edge& e){ return e.to == v; });
    if (!directed) {
        auto& lv = adjList[v];
        lv.remove_if([&](const Edge& e){ return e.to == u; });
    }
    std::cout << "Aresta removida: " << from << (directed ? " -> " : " <-> ") << to << "\n";
}

void Graph::removeVertex(const std::string& vertexName) {
    if (!vertexExists(vertexName)) {
        std::cout << "ERRO: Vertice '" << vertexName << "' nao existe.\n"; return;
    }
    int remId = getVertexId(vertexName);

    // 1) Remover arestas que apontam para remId
    for (auto& [id, lst] : adjList) {
        lst.remove_if([&](const Edge& e){ return e.to == remId; });
    }
    // 2) Remover lista do vertice
    adjList.erase(remId);

    // 3) Compactar IDs: vamos reconstruir maps e listas
    std::map<std::string,int> newMap;
    std::vector<std::string> newInverse;
    std::map<int, std::list<Edge>> newAdj;

    for (size_t oldId = 0; oldId < inverseVertexMap.size(); ++oldId) {
        if ((int)oldId == remId) continue;
        const std::string& name = inverseVertexMap[oldId];
        int newId = (int)newInverse.size();
        newMap[name] = newId;
        newInverse.push_back(name);
    }

    auto remap = [&](int oldId)->int { return newMap.at(inverseVertexMap[oldId]); };

    for (const auto& [oldU, lst] : adjList) {
        // nodes removidos já foram apagados
        if (oldU == remId) continue;
        int u = remap(oldU);
        for (const auto& e : lst) {
            int oldV = e.to;
            if (oldV == remId) continue;
            int v = remap(oldV);
            newAdj[u].push_back({v, e.weight});
        }
    }

    vertexMap.swap(newMap);
    inverseVertexMap.swap(newInverse);
    adjList.swap(newAdj);

    std::cout << "Vertice removido: '" << vertexName << "'. IDs remapeados.\n";
}

void Graph::printAdjList() const {
    std::cout << "\n--- Representacao do Grafo (Lista de Adjacencias) ---\n";
    for (size_t i = 0; i < inverseVertexMap.size(); ++i) { 
        const std::string& vertexName = inverseVertexMap[i];
        int vertexId = i;
        std::cout << "[" << vertexName << "] -> ";
        const std::list<Edge>& edges = adjList.at(vertexId);

        if (edges.empty()) {
            std::cout << "(Nenhuma rota)";
        } else {
            for (const auto& edge : edges) {
                std::string toName = inverseVertexMap[edge.to];
                int weight = edge.weight;
                std::cout << "[" << toName << ", Custo: " << weight << "] ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------------------------\n";
}

void Graph::printAdjMatrix() const {
    std::cout << "\n--- Representacao do Grafo (Matriz de Adjacencias) ---\n";
    int numVertices = inverseVertexMap.size();
    if (numVertices == 0) {
        std::cout << "O grafo esta vazio.\n";
        return;
    }
    
    std::vector<std::vector<int>> matrix(numVertices, std::vector<int>(numVertices, -1));

    for (const auto& pair : adjList) {
        int fromId = pair.first;
        const std::list<Edge>& edges = pair.second;
        for (const auto& edge : edges) {
            int toId = edge.to;
            matrix[fromId][toId] = edge.weight;
        }
    }

    std::cout << std::setw(18) << " ";
    for (int i = 0; i < numVertices; ++i) {
        std::cout << std::setw(18) << inverseVertexMap[i];
    }
    std::cout << std::endl;

    for (int i = 0; i < numVertices; ++i) {
        std::cout << std::setw(18) << inverseVertexMap[i];
        for (int j = 0; j < numVertices; ++j) {
            if (i == j) { 
                std::cout << std::setw(18) << 0;
            } else if (matrix[i][j] == -1) {
                std::cout << std::setw(18) << "---"; 
            } else {
                std::cout << std::setw(18) << matrix[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------------------------------\n";
}

bool Graph::vertexExists(const std::string& vertexName) const {
    return vertexMap.find(vertexName) != vertexMap.end();
}

int Graph::getVertexId(const std::string& vertexName) const {
    if (vertexExists(vertexName)) {
        return vertexMap.at(vertexName);
    }
    return -1; 
}

std::vector<std::string> Graph::dfs(const std::string& startVertexName) {
    std::vector<std::string> result; 
    if (!vertexExists(startVertexName)) {
        std::cout << "ERRO (DFS): Vertice inicial '" << startVertexName << "' nao encontrado.\n";
        return result;
    }

    std::stack<int> stack;
    std::map<int, bool> visited; 
    int startId = getVertexId(startVertexName);
    stack.push(startId);

    while (!stack.empty()) {
        int currentId = stack.top();
        stack.pop(); 

        if (visited.find(currentId) == visited.end()) {
            visited[currentId] = true;
            result.push_back(inverseVertexMap[currentId]);

            const std::list<Edge>& neighbors = adjList.at(currentId);
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it) {
                const Edge& edge = *it;
                if (visited.find(edge.to) == visited.end()) {
                    stack.push(edge.to);
                }
            }
        }
    }
    return result;
}

std::vector<std::string> Graph::bfs(const std::string& startVertexName) {
    std::vector<std::string> result;

    if (!vertexExists(startVertexName)) {
        std::cout << "ERRO (BFS): Vertice inicial '" << startVertexName << "' nao encontrado.\n";
        return result;
    }

    std::queue<int> queue;
    std::map<int, bool> visited;
    int startId = getVertexId(startVertexName);

    visited[startId] = true;
    queue.push(startId);

    while (!queue.empty()) {
        int currentId = queue.front();
        queue.pop();

        result.push_back(inverseVertexMap[currentId]);

        const std::list<Edge>& neighbors = adjList.at(currentId);
        for (const auto& edge : neighbors) {
            if (visited.find(edge.to) == visited.end()) {
                visited[edge.to] = true;
                queue.push(edge.to);
            }
        }
    }
    return result;
}

//Módulo 2:Dijkstra
std::pair<int, std::vector<std::string>> Graph::dijkstra(const std::string& startVertexName, const std::string& endVertexName) {
    if (!vertexExists(startVertexName) || !vertexExists(endVertexName)) {
        std::cout << "ERRO (Dijkstra): Vertice de inicio ou fim nao encontrado.\n";
        return {-1, {}};
    }

    int startId = getVertexId(startVertexName);
    int endId = getVertexId(endVertexName);
    int numVertices = inverseVertexMap.size();

    std::vector<int> distances(numVertices, std::numeric_limits<int>::max());
    std::vector<int> previous(numVertices, -1);
    std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> pq;

    distances[startId] = 0;
    pq.push({startId, 0});

    while (!pq.empty()) {
        int u = pq.top().node;
        int dist_u = pq.top().distance; 
        pq.pop();

        if (dist_u > distances[u]) {
            continue;
        }

        if (u == endId) break;

        for (const auto& edge : adjList.at(u)) {
            int v = edge.to;
            int weight = edge.weight;

            if (distances[u] != std::numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({v, distances[v]});
            }
        }
    }

    std::vector<std::string> path;
    int totalCost = distances[endId];

    if (totalCost == std::numeric_limits<int>::max()) {
        return {-1, {}}; 
    }

    for (int at = endId; at != -1; at = previous[at]) {
        path.push_back(inverseVertexMap[at]);
    }
    std::reverse(path.begin(), path.end());

    return {totalCost, path};
}

//Módulo 3:Welch-Powell
std::map<std::string, int> Graph::welchPowellColoring() {
    std::map<std::string, int> finalResult; 
    int numVertices = inverseVertexMap.size();
    if (numVertices == 0) return finalResult;
    std::vector<std::pair<int, int>> degrees; 
    for (size_t i = 0; i < numVertices; ++i) {
        degrees.push_back({(int)i, (int)adjList.at(i).size()});
    }
    std::sort(degrees.begin(), degrees.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    std::map<int, int> colors; 

    for (const auto& pair : degrees) {
        int u = pair.first;
        
        std::set<int> neighborColors;
        for (const auto& edge : adjList.at(u)) {
            int v = edge.to;
            if (colors.count(v)) {  
                neighborColors.insert(colors.at(v)); 
            }
        }

        int color = 0;
        while (neighborColors.count(color)) {
            color++;
        }
        colors[u] = color;
    }

    for(const auto& pair : colors) {
        finalResult[inverseVertexMap[pair.first]] = pair.second;
    }

    return finalResult;
}

//Módulo 3:(Kahn's Algorithm)
std::vector<std::string> Graph::topologicalSort() {
    int numVertices = inverseVertexMap.size();
    std::vector<int> in_degree(numVertices, 0);
    for (const auto& pair : adjList) {
        for (const auto& edge : pair.second) {
            in_degree[edge.to]++;
        }
    }
    std::queue<int> q;
    for (int i = 0; i < numVertices; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    std::vector<std::string> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(inverseVertexMap[u]);

        for (const auto& edge : adjList.at(u)) {
            int v = edge.to;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    if (result.size() != numVertices) {
        std::cout << "ERRO (Topological Sort): O grafo contem um ciclo! Ordenacao impossivel.\n";
        return {}; // Retorna um vetor vazio para indicar falha
    }

    return result;
}

struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i; 
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]); 
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

struct EdgeInfo {
    int from, to, weight;
};

Graph Graph::kruskalMST() {
    int numVertices = inverseVertexMap.size();
    Graph mst;

    for (const auto& vertexName : inverseVertexMap) {
        mst.addVertex(vertexName);
    }

    std::vector<EdgeInfo> allEdges;
    for (const auto& pair : adjList) {
        int u = pair.first;
        for (const auto& edge : pair.second) {
            int v = edge.to;
            if (u < v) {
                allEdges.push_back({u, v, edge.weight});
            }
        }
    }

    std::sort(allEdges.begin(), allEdges.end(), [](const EdgeInfo& a, const EdgeInfo& b) {
        return a.weight < b.weight;
    });

    DSU dsu(numVertices);
    int edgesInMST = 0;
    for (const auto& edge : allEdges) {
    
        if (dsu.find(edge.from) != dsu.find(edge.to)) {
            dsu.unite(edge.from, edge.to);
            mst.addEdge(inverseVertexMap[edge.from], inverseVertexMap[edge.to], edge.weight, false);
            edgesInMST++;

            if (edgesInMST == numVertices - 1) break;
        }
    }

    return mst;
}
