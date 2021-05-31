#include <iostream>
#include <queue>
#include <algorithm>

#include "ds.hpp"


bool check_sort(std::vector<Prefix>& PrefixList)
{
    for(int i = 0; i < PrefixList.size(); ++i)
    {
        if(i == PrefixList.size() - 1) // last prefix
        {
            if(PrefixList[i].from != PrefixList[i-1].from || PrefixList[i].rank != PrefixList[i-1].rank) // Unique
                PrefixList[i].sorted = true;
        }
        else if(i == 0)
        {
            if(PrefixList[i].from != PrefixList[i+1].from || PrefixList[i].rank != PrefixList[i+1].rank) // Unique
                PrefixList[i].sorted = true;
        }
        else
            if((PrefixList[i].from != PrefixList[i-1].from || PrefixList[i].rank != PrefixList[i-1].rank) &&
              (PrefixList[i].from != PrefixList[i+1].from || PrefixList[i].rank != PrefixList[i+1].rank))
                PrefixList[i].sorted = true;

    }

}



void first_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
{
    std::sort(PrefixList.begin(), PrefixList.end(), [&NodeList](Prefix a, Prefix b) {
        if(a.from == b.from)
            return NodeList[a.id].preFix < NodeList[b.id].preFix;
        else
            return a.from < b.from;
    } );
    check_sort(PrefixList);
}




void prefix_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
{
    for(auto& prefix : PrefixList)
    {
        if(!prefix.sorted)
            prefix.rank += NodeList[prefix.successor].preFix;
    }
    for(auto& prefix : PrefixList)
    {
        if(!prefix.sorted)
            NodeList[prefix.id].preFix = prefix.rank;
    }
        
    std::sort(PrefixList.begin(), PrefixList.end(), [&NodeList](Prefix a, Prefix b) {
        if(a.from == b.from)
            return NodeList[a.id].preFix < NodeList[b.id].preFix;
        else
            return a.from < b.from;
    } );
    check_sort(PrefixList);

}






int main(void)
{
    std::vector<char> seq {'A', 'C', 'T', 'C', 'T', '$'};
    
    std::vector<Edge> EdgeList;
    std::vector<Node> NodeList;
    std::vector<Prefix> PrefixList;
    for(int iter_seq = 0; iter_seq < seq.size(); ++iter_seq)
    {
        //EdgeList.emplace_back(iter_seq, iter_seq + 1, seq[iter_seq], seq[iter_seq + 1]);
        if(iter_seq == seq.size() - 1) // last node
        {
            NodeList.emplace_back(seq[iter_seq], iter_seq, 0, seq[0]);
            PrefixList.emplace_back(seq[iter_seq], iter_seq, 0, seq[0]);
        }
        else
        {
            NodeList.emplace_back(seq[iter_seq], iter_seq, iter_seq + 1, seq[iter_seq + 1]);
            PrefixList.emplace_back(seq[iter_seq], iter_seq, iter_seq + 1, seq[iter_seq + 1]);
        }
    }
    
    for(auto& prefix : PrefixList)
        std::cout << "from: " << prefix.from << " , to: " << prefix.rank << std::endl;
    std::cout << std::endl;
    
    //prefix_sort(NodeList, PrefixList);
    first_sort(NodeList, PrefixList);
    for(auto& prefix : PrefixList)
        std::cout << "from: " << prefix.from << " , to: " << NodeList[prefix.id].preFix  << std::endl;
    std::cout << std::endl;



    prefix_sort(NodeList, PrefixList);
    for(auto& prefix : PrefixList)
        std::cout << "from: " << prefix.from << " , to: " << NodeList[prefix.id].preFix << std::endl;
    std::cout << "----------------------" << std::endl;
    
    for(auto& node : NodeList)
        std::cout << "label: " << node.label << " , to: " << node.preFix << std::endl;

    std::cout << "----------------------" << std::endl;
    
    
    for(auto& prefix : PrefixList)
        std::cout << "from: " << prefix.from << " , to: " << prefix.rank << std::endl;
        //std::cout << "from: " << prefix.from << " , to: " << prefix.rank << " , sorted: " << prefix.sorted << std::endl;
    
    return 0;
}
