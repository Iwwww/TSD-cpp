#include "MyGraph/MyGraph.hpp"
#include "File/File.hpp"
#include "Exception/Exception.hpp"
#include "Menu/Menu.hpp"
#include <any>
#include <vector>
#include <string>

using namespace YMM;

YMM::MyGraph* loadData(std::string file_name) {
    std::string line;

    YMM::File file(file_name, "r");
    line = file.readLine();
    int size = std::stoi(std::string(line));

    YMM::MyGraph* graph_ptr = new YMM::MyGraph{};
    std::vector<std::vector<int>> vec{};

    int count = 0;
    std::vector<int> sub_vec(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            line = file.readLine();
            sub_vec[j] = std::stoi(std::string(line));
        }
        vec.push_back(sub_vec);
    }
    file.close();
    
    graph_ptr->setAdjacencyMatrix(vec);
    return graph_ptr;
}

void writeData(YMM::MyGraph graph, std::string file_name) {
    std::vector vec = graph.getAdjacencyMatrix();
    int size = graph.size();
    File file(file_name, "w");
    file.write(std::to_string(size) + "\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file.write(std::to_string(vec[i][j])+"\n");
        }
    }
    file.close();
}

template<typename T>
T inputRange(T begin, T end) {
    return inputRange<T>(begin, end);
}

template<typename T>
T inputRange(T begin, T end, std::string str) {
    T var{};
    while (true) {
        var = YMM::Menu::input<int>(str);
        if (var >= begin && begin < end && var <= end || var >= begin && begin > end) {
            break;
        } else {
            YMM::Exception::warning("Incorect input range");
        }
    }
    return var;
}

void addVertices(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);

    int num = inputRange<int>(1, 0, "input vertices count: ");
    for (int i = 0; i < num; i++) {
        graph_ptr->addVertice();
    }
}

void addEdge(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        graph_ptr->addEdge(e1, e2);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void addEdgeWeight(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        int weight = inputRange<int>(1, 0, "input weight: ");
        graph_ptr->addEdge(e1, e2, weight);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void addArrow(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        graph_ptr->addArrow(e1, e2);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void addArrowWeight(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        int weight = YMM::Menu::input<int>("input weight: ");
        graph_ptr->addArrow(e1, e2, weight);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void removeVertice(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int index = inputRange<int>(1, graph_ptr->size(), "input vertice: ");
        graph_ptr->removeVertice(index);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void removeEdge(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        graph_ptr->removeEdge(e1, e2);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void removeArrow(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int e1 = inputRange<int>(1, graph_ptr->size(), "input e1: ");
        int e2 = inputRange<int>(1, graph_ptr->size(), "input e2: ");
        graph_ptr->removeArrow(e1, e2);
    } else {
        YMM::Exception::error("No Graph");
    }
}

void clear(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    graph_ptr->clear();
}

void print(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    std::cout << "print graph: " << std::endl;
    graph_ptr->printGraph();
}

void size(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    std::cout << "graph size: " << graph_ptr->size() << std::endl;
}

void dfs(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int vertice = inputRange<int>(1, graph_ptr->size(), "input start vertice: ");
        vertice--;
        graph_ptr->dfs(vertice);
        std::cout << std::endl;
    } else {
        YMM::Exception::error("No Graph");
    }
}

void bfs(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        int vertice = inputRange<int>(1, graph_ptr->size(), "input start vertice: ");
        vertice--;
        graph_ptr->bfs(vertice);
        std::cout << std::endl;
    } else {
        YMM::Exception::error("No Graph");
    }
}

void isEmpty(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
         std::cout << "graph is Not Empty" << std::endl;
    } else {
         std::cout << "graph is Empty" << std::endl;
    }
}

void isEuler(std::vector<std::any> params) {
    auto* graph_ptr = std::any_cast<YMM::MyGraph*>(params[0]);
    if (graph_ptr->isEmpty()) {
        if (graph_ptr->isEuler()) {
             std::cout << "Euler path does exist in the graph" << std::endl;
        } else {
             std::cout << "Euler path does not exist in the graph" << std::endl;
        }
    } else {
        YMM::Exception::error("No Graph");
    }
}

std::string YMM::Exception::log_file_name = "log.log";

int main(int argc, char *argv[]) {
    using namespace YMM;

    // read args
    std::string load_data_file = "data1.txt";
    std::string write_data_file = "data2.txt";
    std::string log_file = "log.log";
    if (argc >= 3) {
        load_data_file = argv[1];
        write_data_file = argv[2];
        log_file = argv[3];
    }

    Exception::setLogFileName(log_file);

    // data
    MyGraph* graph_ptr = nullptr;
    graph_ptr = loadData(load_data_file);
    std::vector<std::any> params{
        graph_ptr
    };

    Menu menu = Menu("Main", std::vector<Menu>{
                         Menu("Add", std::vector<Menu>{
                                  Menu("Add vertices", addVertices),
                                  Menu("Add edge", std::vector<Menu>{
                                           Menu("With weight", addEdgeWeight),
                                           Menu("Without weight", addEdge),
                                       }),
                                  Menu("Add arrow", std::vector<Menu>{
                                           Menu("With weight", addArrowWeight),
                                           Menu("Without weight", addArrow),
                                       }),
                              }),
                         Menu("Remove", std::vector<Menu>{
                                  Menu("Remove vertice", removeVertice),
                                  Menu("Remove edge", removeEdge),
                                  Menu("Remove arrow", removeArrow),
                              }),
                         Menu("Print graph", print),
                         Menu("Size", size),
                         Menu("Is empty", isEmpty),
                         Menu("DFS", dfs),
                         Menu("BFS", bfs),
                         Menu("Clear", clear),
                         Menu("Variant task", std::vector<Menu>{
                            Menu("Euler path", isEuler),
                         }),

                         }, params);

    menu.run();

    writeData(*graph_ptr, write_data_file);

    return 0;
}
