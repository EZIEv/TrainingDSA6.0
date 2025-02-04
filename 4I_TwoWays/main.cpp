#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
//#include <sys/resource.h>

using namespace std;

// Рекурсивная функция для вычисления максимальной глубины для каждой вершины на пути диаметра
// Исключает вершины, находящиеся на пути диаметра
void DFS(int node, int parent, int exclude1, int exclude2, const vector<vector<int>>& graph, const vector<int>& diameter_path, vector<pair<int, bool>>& max_depths) {
    for (int neighbor : graph[node]) {
        // Пропускаем родительскую вершину и исключенные вершины
        if (neighbor == parent || neighbor == exclude1 || neighbor == exclude2) {
            continue;
        }
        // Рекурсивный вызов для каждого соседа
        DFS(neighbor, node, -1, -1, graph, diameter_path, max_depths);

        // Обновляем максимальную глубину для текущей вершины
        max_depths[node].first = max(max_depths[node].first, max_depths[neighbor].first + 1);
    }
}

// Функция для поиска самой удаленной вершины от начальной с использованием BFS
// Возвращает пару: вершину, которая наиболее удалена, и массив расстояний от стартовой вершины
pair<int, vector<int>> BFS(int start, int exclude, const vector<vector<int>>& graph, int num_vertices) {
    vector<int> distance(num_vertices + 1, -1);  // Массив для хранения расстояний до всех вершин
    queue<int> q;  // Очередь для BFS
    q.push(start);
    distance[start] = 0;
    int farthest_vertex = start;  // Вершина, которая на данный момент считается самой удаленной

    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();
        // Проходим по всем соседям текущей вершины
        for (int neighbor : graph[current_vertex]) {
            // Пропускаем вершину, которую исключаем из поиска
            if (neighbor == exclude) {
                continue;
            }
            // Если вершина не была посещена
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current_vertex] + 1;  // Обновляем расстояние
                q.push(neighbor);
                if (distance[neighbor] > distance[farthest_vertex]) {  // Обновляем самую удаленную вершину
                    farthest_vertex = neighbor;
                }
            }
        }
    }
    return {farthest_vertex, distance};  // Возвращаем самую удаленную вершину и массив расстояний
}

// Основная функция для решения задачи
uint64_t FindMaxProduct(int num_vertices, const vector<vector<int>>& graph) {

    /*vector<vector<int>> graph(num_vertices + 1);
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }*/
    // Первый BFS: находим одну крайнюю вершину диаметра
    auto bfs_result_1 = BFS(1, -1, graph, num_vertices);
    int vertex_u = bfs_result_1.first;  // Вершина, самая удаленная от 1

    // Второй BFS: находим другую крайнюю вершину диаметра
    auto bfs_result_2 = BFS(vertex_u, -1, graph, num_vertices);
    int vertex_v = bfs_result_2.first;  // Вершина, самая удаленная от вершины vertex_u

    // Строим путь диаметра с помощью родительских ссылок
    vector<int> parent(num_vertices + 1, -1);
    queue<int> q;
    q.push(vertex_u);
    parent[vertex_u] = 0;  // Устанавливаем родителя для начальной вершины

    while (!q.empty()) {
        int current_vertex = q.front();
        q.pop();
        for (int neighbor : graph[current_vertex]) {
            if (parent[neighbor] == -1) {  // Если вершина не посещена
                parent[neighbor] = current_vertex;  // Устанавливаем родителя
                q.push(neighbor);
            }
        }
    }

    // Восстанавливаем путь диаметра от вершины vertex_v до вершины vertex_u
    vector<int> diameter_path;
    int current = vertex_v;
    while (current != vertex_u) {
        diameter_path.push_back(current);
        current = parent[current];
    }

    diameter_path.push_back(vertex_u);  // Добавляем вершину vertex_u в конец пути
    reverse(diameter_path.begin(), diameter_path.end());  // Путь диаметра

    int diameter_length = diameter_path.size() - 1;  // Длина диаметра

    // Массив для хранения максимальной глубины для каждой вершины на пути диаметра
    vector<pair<int, bool>> max_depths(num_vertices + 1, {0, false});
    int subtree_diameter_length = 0;  // Максимальная длина поддерева вне диаметра

    // Для каждой вершины на пути диаметра вычисляем максимальную глубину в её поддереве
    for (int i = 1; i < diameter_path.size() - 1; ++i) {
        DFS(diameter_path[i], -1, diameter_path[i - 1], diameter_path[i + 1], graph, diameter_path, max_depths);
        max_depths[diameter_path[i]].second = i < diameter_path.size() / 2;

        // Для каждого соседа, который не входит в путь диаметра, ищем максимальную длину поддерева
        if (graph[diameter_path[i]].size() > 2) {
            for (int neighbor : graph[diameter_path[i]]) {
                if (neighbor == diameter_path[i + 1] || neighbor == diameter_path[i - 1]) continue;
                auto bfs_result_1 = BFS(neighbor, diameter_path[i], graph, num_vertices);
                int u = bfs_result_1.first;

                auto bfs_result_2 = BFS(u, diameter_path[i], graph, num_vertices);

                subtree_diameter_length = max(subtree_diameter_length, bfs_result_2.second[bfs_result_2.first]);  // Обновляем максимальную длину поддерева
            }
        }
    }

    if (diameter_length <= 2) {
        return 0;
    }

    uint64_t max_prod = 0;

    // Для каждой пары вершин на пути диаметра ищем произведение длин непересекающихся путей
    int left_path_length = 1;
    int right_path_length = diameter_length / 2;
    for (int i = 1; i < diameter_path.size() - 1; ++i) {
        if (max_depths[diameter_path[i]].second) {
            left_path_length = max(left_path_length, i + max_depths[diameter_path[i]].first);
        } else {
            right_path_length = max(right_path_length, diameter_length - i + max_depths[diameter_path[i]].first);
        }
        
        /*if (diameter_length - i - 5 > 0) {
            max_prod = max(max_prod, static_cast<uint64_t>(i + max_depths[diameter_path[i]].first) * (diameter_length - i - 5 + max_depths[diameter_path[i + 5]].first));
        }
        if (diameter_length - i - 4 > 0) {
            max_prod = max(max_prod, static_cast<uint64_t>(i + max_depths[diameter_path[i]].first) * (diameter_length - i - 4 + max_depths[diameter_path[i + 4]].first));
        }*/
        if (diameter_length - i - 3 > 0) {
            max_prod = max(max_prod, static_cast<uint64_t>(i + max_depths[diameter_path[i]].first) * (diameter_length - i - 3 + max_depths[diameter_path[i + 3]].first));
        }
        if (diameter_length - i - 2 > 0) {
            max_prod = max(max_prod, static_cast<uint64_t>(i + max_depths[diameter_path[i]].first) * (diameter_length - i - 2 + max_depths[diameter_path[i + 2]].first));
        }
        if (diameter_length - i - 1 > 0) {
            max_prod = max(max_prod, static_cast<uint64_t>(i + max_depths[diameter_path[i]].first) * (diameter_length - i - 1 + max_depths[diameter_path[i + 1]].first));
        }
    }

    max_prod = max(max_prod, static_cast<uint64_t>(left_path_length) * right_path_length);

    return max(max_prod, static_cast<uint64_t>(subtree_diameter_length) * diameter_length);  // Возвращаем максимальное произведение
}

int main() {
    /*const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);*/
    ios::sync_with_stdio(false);
    cin.tie(0);

    int num_vertices;
    cin >> num_vertices;  // Вводим количество вершин
    vector<vector<int>> graph(num_vertices + 1);  // Создаем граф
    for (int i = 0; i < num_vertices - 1; i++) {
        int u, v;
        cin >> u >> v;  // Вводим рёбра
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << FindMaxProduct(num_vertices, graph);  // Выводим результат
    /*ifstream infile("C:\\Users\\User\\Downloads\\Telegram Desktop\\tests (2).txt");
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        int N;
        stringstream ss(line);
        ss >> N;

        vector<pair<int, int>> edges;
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            infile >> u >> v;
            edges.emplace_back(u, v);
        }

        int expected_result;
        infile >> expected_result;

        long long result = FindMaxProduct(N, edges);

        cout << "Expected: " << expected_result << ", Got: " << result << "\n";
        if (result != expected_result) {
            cout << "Test failed!\n";
            return 1;
        }
    }

    cout << "All tests passed!\n";
    return 0;*/
}
