#include <iostream>
#include <queue>
#include "ds.hpp"

void first_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
{
    for(auto& node : NodeList)
    {

    }
}



void prefix_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
{
    for(auto& prefix : PrefixList)
    {
        prefix.rank += Prefix[prefix.successor].rank;
    }
    std::sort(PrefixList.begin(), PrefixList.end(), [](Prefix a, Prefix b) {
        return (a.from < b.from) ? 1 : (a.rank < b.rank);
    } );

}






int main(void)
{
    std::vector<char> seq {'A', 'T', 'C', 'T', '$'};
    
    std::vector<Edge> EdgeList;
    std::vector<Node> NodeList;
    std::vector<Prefix> PrefixList;
    for(int iter_seq = 0; iter_seq < seq.size(); ++iter_seq)
    {
        //EdgeList.emplace_back(iter_seq, iter_seq + 1, seq[iter_seq], seq[iter_seq + 1]);
        if(iter_seq == seq.size() - 1) // last node
        {
            NodeList.emplace_back(seq[iter_seq], iter_seq, 0);
            PrefixList.emplace_back(seq[iter_seq], iter_seq, 0, seq[0]);
        }
        else
        {
            NodeList.emplace_back(seq[iter_seq], iter_seq, iter_seq + 1);
            PrefixList.emplace_back(seq[iter_seq], iter_seq, iter_seq + 1, seq[iter_seq + 1]);
        }
    }
    
    for(auto& prefix : PrefixList)
        std::cout << "from: " << prefix.from << " , to: " << prefix.rank << std::endl;
    std::cout << std::endl;
    
    return 0;
}
