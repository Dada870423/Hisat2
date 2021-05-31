#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

#include "build_graph.hpp"
#include "G_prefix_sort.hpp"
#include "G_ds.hpp"

int main(void)
{
    std::vector<Node> NodeList;
    std::vector<char> seq {'#', 'G', 'A', 'C', 'G', 'T', 'A', 'C', 'C', 'T', 'G', '$'};
    std::vector<std::pair<int, char>> insert;// {std::make_pair(1, 'A'), std::make_pair(3, 'C')} ;
    std::vector<std::pair<int, int>> del {std::make_pair(3, 5), std::make_pair(6, 8), std::make_pair(6, 10)} ;
    std::vector<std::pair<int, char>> substitution {std::make_pair(3, 'T')} ;

    build_graph::linear_ref(seq, NodeList);
    build_graph::add_SNP(NodeList, insert, del, substitution);

    std::vector<Prefix> PrefixList;
    G_prefix_sort::init_split(NodeList);

    for(auto& node : NodeList)
    {
        std::cout << "id: " << node.id << " , label: " << node.label;
        for(auto& to : node.to)
            std::cout << " , to: " << to << " ";
        std::cout << std::endl;
    }
    
    G_prefix_sort::init_prefix(NodeList, PrefixList);
    for(auto& pre : PrefixList)
        std::cout << "from: " << pre.from << " , id: " << pre.id << " , rank: " << NodeList[pre.id].preFix << " suc: " << pre.successor << " , sorted: " << pre.sorted << std::endl;
    std::cout << "init done\n\n\n";
    std::cout << "iter 1: \n";
    G_prefix_sort::double_node(NodeList, PrefixList);
    int node_id = 0;
    
    G_prefix_sort::prefix_sort(NodeList, PrefixList);

    for(auto& pre : PrefixList)
        std::cout << "from: " << pre.from << " , id: " << pre.id << " , rank: " << NodeList[pre.id].preFix << " suc: " << pre.successor << " , sorted: " << pre.sorted << std::endl;

    G_prefix_sort::double_node(NodeList, PrefixList);
    G_prefix_sort::prefix_sort(NodeList, PrefixList);
    std::cout << "iter 2: \n";
    for(auto& pre : PrefixList)
        std::cout << "from: " << pre.from << " , id: " << pre.id << " , rank: " << NodeList[pre.id].preFix << " suc: " << pre.successor << " , sorted: " << pre.sorted << std::endl;
    return 0;
}
