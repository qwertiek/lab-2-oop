#include "graph.hpp"
#include <limits>
#include <set>

namespace template_library {

    void Graph::add_edge(const std::string &from, const std::string &to, uint16_t weight) {
        adj[from].push_back(Edge{to, weight});
        adj[to].push_back(Edge{from, weight}); // Граф неориентированный
    }

    std::vector<std::string> Graph::find_shortest_path(const std::string &start, const std::string &end) {
        using Pair = std::pair<int, std::string>;
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
        std::unordered_map<std::string, int> dist;
        std::unordered_map<std::string, std::string> prev;
        std::vector<std::string> path;

        if (adj.find(start) == adj.end() || adj.find(end) == adj.end()) {
            throw std::invalid_argument("Один или оба города отсутствуют в графе");
        }

        // Инициализация расстояний
        for (const auto &pair : adj) {
            dist[pair.first] = std::numeric_limits<int>::max();
        }
        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [current_dist, current_city] = pq.top();
            pq.pop();

            if (current_dist > dist[current_city]) {
                continue;
            }

            for (const auto &edge : adj[current_city]) {
                int new_dist = current_dist + edge.weight;

                if (new_dist < dist[edge.to]) {
                    dist[edge.to] = new_dist;
                    prev[edge.to] = current_city;
                    pq.push({new_dist, edge.to});
                }
            }
        }

        // Восстановление пути
        if (dist[end] == std::numeric_limits<int>::max()) {
            return {}; // Пути нет
        }

        for (std::string at = end; at != start; at = prev[at]) {
            path.push_back(at);
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());

        return path;
    }
}
