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
    //std::pair del {(3, 5), (6, 8), (6, 10)};

    build_graph::linear_ref(seq, NodeList);
    build_graph::add_SNP(NodeList, insert, del, substitution);

    for(auto& node : NodeList)
        for(auto& TO : node.to)
            std::cout << "id: " << node.id << " , to: " << TO << std::endl;
    
    //G_prefix_sort::show(NodeList);
//    for(auto& node : NodeList)
//        for(auto& inc : node.income)
//            std::cout << "id: " << node.id << " , inc: " << inc << std::endl;
    
    std::vector<Prefix> PrefixList;
    G_prefix_sort::init_split(NodeList);

    for(auto& node : NodeList)
    {
        std::cout << "id: " << node.id << " , label: " << node.label;
        for(auto& to : node.to)
            std::cout << " , to: " << to << " ";
        std::cout << std::endl;
    }
    //for(auto& fuck6 : NodeList[6].to)
    //    std::cout << fuck6 << " ";

    
    G_prefix_sort::init_prefix(NodeList, PrefixList);
    for(auto& pre : PrefixList)
        std::cout << "from: " << pre.from << " , id: " << pre.id << " , rank: " << NodeList[pre.id].preFix << " suc: " << pre.successor << " , sorted: " << pre.sorted << std::endl;
    std::cout << "init done\n\n\n";
    //for(auto& pre : PrefixList)
    //    std::cout << "from: " << pre.from << " , id: " << pre.id << " , rank: " << NodeList[pre.id].preFix << " , sorted: " << pre.sorted << std::endl;
    
    //std::cout << "node: $$$$$$$$$$$$$\n";
    
    //for(auto& node : NodeList)
    //{
    //    std::cout << "from: " << node.label << " , id: " << node.id;
    //    for(auto& To : node.to)
    //        std::cout << " , to: " << To;
    //    std::cout << "\n";
    //}
    std::cout << "iter 1: \n";
    G_prefix_sort::double_node(NodeList, PrefixList);
    int node_id = 0;
    //for(auto& node : NodeList)
    //{
    //    std::cout << "from: ( " << node.id << " ) " << node.label << " , id: " << node.id << " preFix: " << node.preFix << "\n";
    //    for(auto& To : node.to)
    //        std::cout << " , to: " << To;
    //    std::cout << "\n";
    //    ++node_id;
    //}
    //std::cout << "node done\n";
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
