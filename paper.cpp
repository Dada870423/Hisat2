#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

#include "build_graph.hpp"
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

//    for(auto& node : NodeList)
//        for(auto& inc : node.income)
//            std::cout << "id: " << node.id << " , inc: " << inc << std::endl;

}
