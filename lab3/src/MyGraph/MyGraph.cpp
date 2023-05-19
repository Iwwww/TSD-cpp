#include "MyGraph.hpp"

namespace YMM {
MyGraph::MyGraph() {}

MyGraph::~MyGraph() {}

void MyGraph::addVertice() {
    if (this->size() != 0) {
        std::vector<int> new_vec{};
        for (int i = 0; i <= this->size(); i++) {
            new_vec.push_back(0);
        }
        // new_vec.push_back(1);

        // add zero for other vertices
        for (auto &v: this->adjacency_matrix) {
            v.push_back(0);
        }

        this->adjacency_matrix.push_back(new_vec);
    } else {
        this->adjacency_matrix.push_back(std::vector<int>{0});
    }
}

void MyGraph::addEdge(int v1, int v2) {
    addArrow(v1, v2);
    addArrow(v2, v1);
}

void MyGraph::addEdge(int v1, int v2, int weigth) {
    addArrow(v1, v2, weigth);
    addArrow(v2, v1, weigth);
}

void MyGraph::addArrow(int from, int to) {
    addArrow(from, to, 1);
}

void MyGraph::addArrow(int from, int to, int weight) {
    from--;
    to--;
    this->adjacency_matrix[from][to] = weight;
}

void MyGraph::removeVertice(int vertice) {
    vertice--;
    for (auto& v: this->adjacency_matrix) {
        v.erase(v.begin() + vertice);
    }
    this->adjacency_matrix.erase(adjacency_matrix.begin() + vertice);
}

void MyGraph::removeEdge(int v1, int v2) {
    removeArrow(v1, v2);
    removeArrow(v2, v1);
}

void MyGraph::removeArrow(int from, int to) {
    from--;
    to--;
    this->adjacency_matrix[from][to] = 0;
}

void MyGraph::printGraph() {
    // header
    std::cout << "\\  ";
    for (int i = 1; i <= adjacency_matrix.size(); i++) {
         std::cout << i << "  ";
    }
    std::cout << std::endl;
    std::cout << " \\";
    for (int i = 1; i <= adjacency_matrix.size(); i++) {
         std::cout << "___";
    }
    std::cout << std::endl;

    for (int i = 0; i < adjacency_matrix.size(); i++) {
         std::cout << i + 1 << "| ";
         for (int j = 0; j < adjacency_matrix.size(); j++) {
            std::cout << adjacency_matrix[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}

void MyGraph::dfs(int vertice) {
    // init visited_ptr
    this->visited_ptr = this->init_visited();

    sub_dfs(vertice);

    // clear visited_ptr
    delete visited_ptr;
    visited_ptr = nullptr;
}

void MyGraph::sub_dfs(int vertice) {
    std::cout << vertice + 1 << " ";
    (*this->visited_ptr)[vertice] = true;
    for (int i = 0; i < adjacency_matrix[vertice].size(); i++) {
        if (vertice != i &&
            adjacency_matrix[vertice][i] && 
            (*this->visited_ptr)[i] == false) {
            sub_dfs(i);
        }
    }
}

void MyGraph::bfs(int vertice) {
    std::unique_ptr<std::vector<int>> visited(new std::vector<int>(this->size()));

    int* queue = new int[this->size()]{};
    int count = 0;
    int head = 0;
    queue[count++] = vertice;
    (*visited)[vertice] = true;
    while (head < count) {
        vertice = queue[head++];
        std::cout << vertice + 1 << " ";
        for (int i = 0; i < this->size(); i++) {
            if (adjacency_matrix[vertice][i] && !(*visited)[i]) {
                queue[count++] = i;
                (*visited)[i] = true;
            }
        }
    }
    delete []queue;
}

int MyGraph::size() {
    return this->adjacency_matrix.size();
}

bool MyGraph::isEulerPath() {
    if (this->size() == 0) return 0;

    bool euler_flag = true;

    // bfs
    std::unique_ptr<std::vector<int>> visited(new std::vector<int>(this->size()));

    int* queue = new int[this->size()]{};
    int count = 0;
    int head = 0;
    int vertice = 0;
    queue[count++] = vertice;
    (*visited)[vertice] = true;
    while (head < count) {
        vertice = queue[head++];
        int arrow_count = 0;
        for (int i = 0; i < this->size(); i++) {
            if (adjacency_matrix[vertice][i]) {
                arrow_count++;
                if (!(*visited)[i]) {
                    queue[count++] = i;
                    (*visited)[i] = true;
                }
            }
        }

        // arrow_count == 0
        // unlinked vertice
        if (arrow_count % 2 == 1) euler_flag = false;

        // for (int i = 0; i < this->size(); i++) {
        //     if (adjacency_matrix[i][vertice]) {
        //         arrow_count--;
        //     }
        // }
        // // arrow_count != 0
        // if (arrow_count) euler_flag = false;
    }
    delete []queue;
    return euler_flag;
}

std::vector<std::vector<int>> MyGraph::getEulerPathes() {
    std::vector<std::vector<int>> pathes{};
    std::vector<int> path(this->getEdgesCount());
    std::iota(path.begin(), path.end(), 0);

    do {
        bool flag = true;
        // for (int i = 0; i < this->size() - 1; i++) {
        //     if (!(this->adjacency_matrix[path[i]][path[i + 1]])) {
        //         flag = false;
        //         break;
        //     }
        // }
        if (flag) pathes.push_back(path);
    } while(std::next_permutation(path.begin(), path.end()));

    return pathes;
}

void MyGraph::setAdjacencyMatrix(std::vector<std::vector<int>> matrix) {
    this->adjacency_matrix = matrix;
}

std::vector<std::vector<int>> MyGraph::getAdjacencyMatrix() {
    return this->adjacency_matrix;
}

int MyGraph::getEdgesCount() {
    int count = 0;
    for (auto i: adjacency_matrix) {
        for (auto j: i) {
            if (j) count++;
        }
    }
    return count / 2;
}

void MyGraph::clear() {
    this->adjacency_matrix.clear();
}
bool MyGraph::isEmpty() {
    return this->adjacency_matrix.size() ? true : false;
}

std::vector<bool>* MyGraph::init_visited() {
    std::vector<bool>* vec = new std::vector<bool>();
    for (int i = 0; i < this->size(); i++) {
        vec->push_back(false);
    }
    return vec;
}
} // namespace YMM
