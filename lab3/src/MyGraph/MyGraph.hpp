#pragma once
#include <memory>
#include <vector>
#include <iostream>

namespace YMM {
class MyGraph {
public:
    MyGraph();
    ~MyGraph();

    void addVertice();
    void addEdge(int v1, int v2);
    void addEdge(int v1, int v2, int weight);
    void addArrow(int from, int to);
    void addArrow(int from, int to, int weight);
    void removeVertice(int vertice);
    void removeEdge(int v1, int v2);
    void removeArrow(int from, int to);
    void printGraph();
    // Deep First Search
    void dfs(int vertice);
    // Breadth First Search
    void bfs(int vertice);
    // return vertice count
    int size();
    // return true if Euler path exsists
    bool isEulerPath();
    std::vector<std::vector<int>> getEulerPathes();
    void setAdjacencyMatrix(std::vector<std::vector<int>>);
    std::vector<std::vector<int>> getAdjacencyMatrix();
    void clear();
    bool isEmpty();

private:
    std::vector<bool>* init_visited();
    void sub_dfs(int vertice);


    std::vector<std::vector<int>> adjacency_matrix{};
    std::vector<bool>* visited_ptr = nullptr;
};
}
