#include <iostream>
#include <cstdio>
#include <cstring>
#include <functional>

class Graph {
public:
    Graph(size_t _num_vertices, size_t _num_edges)
        : num_vertices(_num_vertices), num_edges(_num_edges) {
        adj_mat = new int*[num_vertices];
        for (size_t index = 0; index < num_vertices; ++index) {
            adj_mat[index] = new int[num_vertices];
            std::memset(adj_mat[index], 0, sizeof(int) * num_vertices);
        }
        floyd_mat = new int*[num_vertices];
        for (size_t index = 0; index < num_vertices; ++index) {
            floyd_mat[index] = new int[num_vertices];
            std::memset(floyd_mat[index], 0, sizeof(int)* num_vertices);
        }
    }

    ~Graph() {
        if (adj_mat != nullptr) {
            for (size_t index = 0; index < num_vertices; ++index) {
                delete[] adj_mat[index];
            }
            delete[] adj_mat;
            adj_mat = nullptr;
        }
        if (floyd_mat != nullptr) {
            for (size_t index = 0; index < num_vertices; ++index) {
                delete[] floyd_mat[index];
            }
            delete[] floyd_mat;
            floyd_mat = nullptr;
        }
    }

    void load() {
        size_t from, to;
        int val;
        for (size_t index = 0; index < num_edges; ++index) {
            std::scanf("%u%u%d", &from, &to, &val);
            adj_mat[from][to] = val;
        }
        std::scanf("%u%u", &special_from, &special_to);
    }

    void PrintFloyd() {
        if (floyd_mat == nullptr) {
            return;
        }
        for (size_t row = 0; row < num_vertices; ++row) {
            for (size_t col = 0; col < num_vertices; ++col) {
                std::printf("%d\t", floyd_mat[row][col]);
            }
            std::putchar('\n');
        }
    }

    void PrintAdj() {
        if (adj_mat == nullptr) {
            return;
        }
        for (size_t row = 0; row < num_vertices; ++row) {
            for (size_t col = 0; col < num_vertices; ++col) {
                std::printf("%d\t", adj_mat[row][col]);
            }
            std::putchar('\n');
        }
    }

    bool Strongly_Connected() {
        char* visited = new char[num_vertices];
        std::memset(visited, 0, sizeof(char) * num_vertices);
        size_t count = 0;

        size_t* record = new size_t[num_vertices];
        std::memset(record, 0, sizeof(size_t) * num_vertices);
        size_t top = 0;

        auto FindRoute = [&](size_t from) {
            size_t ret;
            for (ret = 0; ret < num_vertices; ++ret) {
                if (visited[ret] == 0 && adj_mat[from][ret] > 0) {
                    break;
                }
            }
            return ret; // ret == num_vertices if not found.
        };

        size_t cur = 0;
        while (1) {
            ++count; // number of vertices we have stepped on
            if (count == num_vertices) {
                return true;
            }
            record[top] = cur;
            ++top;

            visited[cur] = 1;

            auto next = FindRoute(cur);
            if (next != num_vertices) {
                cur = next;
            } else if (top != 1) {
                top -= 2;
                cur = record[top];
                --count; // we would stepped on the same vertex again
            } else { // top == 0
                return false;
            }
        }
    }

    void floyd() {
        for (size_t row = 0; row < num_vertices; ++row) {
            std::memcpy(floyd_mat[row], adj_mat[row], sizeof(int) * num_vertices);
        }

        for (size_t k = 0; k < num_vertices; ++k) {
            for (size_t from = 0; from < num_vertices; ++from) {
                for (size_t to = 0; to < num_vertices; ++to) {
                    if (from == to) {
                        continue;
                    }
                    bool new_valid_route = (floyd_mat[from][k] > 0) && (floyd_mat[k][to] > 0);
                    bool old_valid_route = floyd_mat[from][to] > 0;
                    int old_length = floyd_mat[from][to];
                    int new_length = floyd_mat[from][k] + floyd_mat[k][to];

                    if (new_valid_route && (
                                (old_valid_route && new_length < old_length)
                                || (!old_valid_route)
                            ))
                    {
                        floyd_mat[from][to] = new_length;
                    }
                }
            }
        }
    }

    void dijkstra() {
        int** routes = new int*[num_vertices];
        for (size_t index = 0; index < num_vertices; ++index) {
            routes[index] = new int[num_vertices];
            std::memset(routes[index], 0, num_vertices * sizeof(int));
        }

        int* length = new int[num_vertices];
        std::memcpy(length, adj_mat[special_from], num_vertices * sizeof(int));

        char* added = new char[num_vertices];
        std::memset(added, 0, num_vertices * sizeof(char));
        added[special_from] = 2;

        auto NearestVertex = [&]() {
            int min_length = 0;
            size_t ret = special_from;
            for (size_t index = 0; index < num_vertices; ++index) {
                if (added[index] != 0) {
                    continue;
                }

                if (min_length == 0) {
                    min_length = length[index];
                    ret = index;
                } else {
                    if (length[index] != 0 && length[index] < min_length) {
                        min_length = length[index];
                        ret = index;
                    }
                }
            }
            return ret;
        };

        auto check = [&](size_t to) {
            auto route = routes[to];
            int len = 0;
            
            if (route[0] == 0) {
                len = adj_mat[special_from][to];
            } else if (route[0] == 1) {
                len = adj_mat[special_from][route[1]]
                    + adj_mat[route[1]][to];
            } else {
                len = adj_mat[special_from][routes[to][1]];
                for (size_t index = 2; index <= routes[to][0]; ++index) {
                    len += adj_mat[route[index - 1]][route[index]];
                }
                len += adj_mat[route[route[0]]][to];
            }
            std::printf("From %u to %u: length = %d\n", special_from, to, len);

            for (size_t i = 0; i < num_vertices; ++i) {
                std::printf("%d\t", length[i]);
            }
        };

        for (size_t k = 0; k < num_vertices - 1; ++k) {
            // add the nearest vertex
            auto nearest_index = NearestVertex();

            added[nearest_index] = 1;

            // ???? !added u
            // ? v -> nearest -> u ?? ??? v -> u
            // ?? u

            for (size_t index = 0; index < num_vertices; ++index) {
                if (added[index] != 0) {
                    continue;
                }
                if (length[nearest_index] > 0 && adj_mat[nearest_index][index] > 0 &&
                    (length[index] == 0 || length[nearest_index] + adj_mat[nearest_index][index] < length[index]))
                {
                    length[index] = length[nearest_index] + adj_mat[nearest_index][index];
                    std::memcpy(routes[index], routes[nearest_index], (routes[nearest_index][0] + 1) * sizeof(int));
                    ++routes[index][0];
                    routes[index][routes[index][0]] = nearest_index;
                }
            }
        }

        for (size_t index = 1; index <= routes[special_to][0]; ++index) {
            std::printf("%u\t", routes[special_to][index]);
        }
        std::putchar('\n');

        for (size_t to = 0; to < num_vertices; ++to) {
            check(to);
        }

        for (size_t index = 0; index < num_vertices; ++index) {
            delete[] routes[index];
        }
        delete[] routes;
    }

    size_t num_vertices;
    size_t num_edges;
    size_t special_from;
    size_t special_to;
    int** adj_mat;
    int** floyd_mat;
};

int main() {
    size_t num_vertices, num_edges;
    std::scanf("%u%u", &num_vertices, &num_edges);
    Graph graph(num_vertices, num_edges);
    graph.load();
    graph.PrintAdj();
    std::putchar('\n');
    graph.floyd();
    graph.PrintFloyd();
    std::putchar('\n');
    graph.dijkstra();
    //std::cout << graph.Strongly_Connected() << std::endl;
    return 0;
}
