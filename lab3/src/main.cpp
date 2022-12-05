#include "MyGraph/MyGraph.hpp"
#include <vector>
using namespace YMM;

int main() {
    MyGraph graph{};
    graph.addVertice();
    graph.addVertice();
    graph.addVertice();
    graph.addVertice();
    graph.addVertice();

    // graph.addArrow(1, 2);
    graph.addEdge(1, 3, 5);
    graph.addEdge(4, 2, 8);
    graph.addEdge(4, 3);
    graph.addEdge(3, 5, 7);
    graph.printGraph();
    std::cout << "size: " << graph.size() << std::endl;
    std::cout << "Euiler path: " << graph.isEuler() << std::endl;

    std::cout << "dfs: ";
    graph.dfs(0);
    std::cout << std::endl;

    std::cout << "bfs: ";
    graph.bfs(3);
    std::cout << std::endl;

    // graph.removeVertice(3);
    std::cout << std::endl;

    graph.printGraph();
    std::cout << "size: " << graph.size() << std::endl;
    std::cout << "Euiler path: " << graph.isEuler() << std::endl;

    return 0;
}
