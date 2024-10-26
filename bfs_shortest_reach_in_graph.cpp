
// https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach/problem

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <optional>


// Alias for readability
using Vertex = int;
using Weight = int;
using Graph = std::unordered_map<Vertex, std::vector<std::pair<Vertex, Weight>>>;


// Dijkstra's algorithm to find shortest paths from source
std::vector<Weight> dijkstra(const Graph& graph, Vertex source) {
    std::vector<Weight> distances(graph.size(), -1);
    distances[source] = 0;

    auto compare = [](const std::pair<Vertex, Weight>& a, const std::pair<Vertex, Weight>& b) {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<Vertex, Weight>, std::vector<std::pair<Vertex, Weight>>, decltype(compare)> min_heap(compare);

    min_heap.push({source, 0});

    while (!min_heap.empty()) {
        auto [current, current_distance] = min_heap.top();
        min_heap.pop();

        if (distances[current] != -1 && current_distance > distances[current]) {
            continue;
        }
        
        for (const auto& [neighbor, weight] : graph.at(current)) {
            Weight new_distance = current_distance + weight;
            if (distances[neighbor] == -1 || new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                min_heap.push({neighbor, new_distance});
            }
        }
    }

    return distances;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int q;
    std::cin >> q;
    
    for (int t = 0; t < q; t++) {
        int n, m;
        std::cin >> n;

        Graph graph;
        for (int i = 0; i < n; i++) {
            graph[i] = {  };
        }

        std::cin >> m;
    
        for (int i = 0; i < m; i++) {
            Vertex u, v;
            std::cin >> u >> v ;
            u--; v--;
            graph[u].emplace_back(v, 6);
            graph[v].emplace_back(u, 6); 
        }
    
        int s;
        std::cin >> s;
        s--;
        
        auto distances = dijkstra(graph, s);
        
        std::ranges::for_each(distances, [i=0, s](auto& distance) mutable {
            if (i++ != s) {
                std::cout << distance << " ";
            }
        });
 
        std::cout << std::endl;
    }
    
    return 0;
}

