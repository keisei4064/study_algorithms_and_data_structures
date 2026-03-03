#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

int main()
{
    using Graph = boost::adjacency_list<
        boost::vecS,
        boost::vecS,
        boost::directedS,
        boost::property<boost::vertex_name_t, std::string>>;

    // 頂点数と辺を固定
    const int n = 7;
    const std::vector<std::pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}};

    Graph g(n);

    // 頂点ラベルを設定
    auto name_map = boost::get(boost::vertex_name, g);
    for (int v = 0; v < n; ++v)
    {
        name_map[v] = "v" + std::to_string(v);
    }

    // 辺を追加
    for (const auto &[from, to] : edges)
    {
        boost::add_edge(from, to, g);
    }

    // DOT ファイルへ出力
    std::ofstream ofs("graph.dot");
    if (!ofs)
    {
        std::cerr << "graph.dot を開けませんでした\n";
        return 1;
    }
    boost::write_graphviz(ofs, g, boost::make_label_writer(name_map));

    std::cout << "Wrote graph.dot\n";
    std::cout << "Next: dot -Tpng graph.dot -o graph.png\n";
    return 0;
}
