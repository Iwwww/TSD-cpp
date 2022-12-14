#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "MyGraph/MyGraph.hpp"

using namespace YMM;
using namespace std;

void printVec(vector<vector<int>> vec) {
    for (auto i: vec) {
        for (auto j: i) {
            cout << j + 1 << " ";
        }
        cout << endl;
    }
}

void printVec(vector<int> vec) { for (auto i: vec) {
        cout << i << " ";
    }
    cout << endl;
}

vector<vector<int>> gen_vec(vector<vector<int>>& all, vector<int> vec, int size, int depth) {
    if (depth == size) {
        all.push_back(vec);
    }
    for (int i = 0; i < size; i++) {
        vec.push_back(i);
        gen_vec(all, vec, size, ++depth);
    }
    if (depth == 0) {
        return all;
    }
}

int main() {
    MyGraph graph;

    graph.addVertice();
    graph.addVertice();
    graph.addVertice();
    graph.addVertice();
    graph.addVertice();
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 5);
    graph.addEdge(4, 1);
    graph.addEdge(5, 1);

    graph.printGraph();
    cout << "edges count=" << graph.getEdgesCount() << endl;

    std::cout << std::endl;
    vector<vector<int>> pathes = graph.getEulerPathes();
    printVec(pathes);
    return 0;
}
