#ifndef _BUILD_GRAPH_HPP_
#define _BUILD_GRAPH_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>

#include "G_ds.hpp"

class build_graph
{
public:
    static void linear_ref(std::vector<char>& seq, std::vector<Node>& NodeList)
    {
        for(int iter_seq = 0; iter_seq < seq.size(); ++iter_seq)
        {
            if(iter_seq == seq.size() - 1) // last node
                NodeList.emplace_back(seq[iter_seq], iter_seq, iter_seq - 1, 0);
            else
                NodeList.emplace_back(seq[iter_seq], iter_seq, iter_seq - 1, iter_seq + 1);
        }
    }

    static void add_SNP(std::vector<Node>& NodeList, std::vector<std::pair<int, char>>& insert, std::vector<std::pair<int, int>>& del, std::vector<std::pair<int, char>>& substitution)
    {
        int num = NodeList.size();
        //insert
        for(auto& ins : insert)
        {
            NodeList[ins.first].to.push_back(num);
            NodeList.emplace_back(ins.second, num, ins.first, ins.first + 1);
            NodeList[num + 1].income.push_back(num);
            ++num;
        }


        //delete
        for(auto& dele : del)
        {
            NodeList[dele.first].to.push_back(dele.second);
            NodeList[dele.second].income.push_back(dele.first);
        }
        //substitution
        for(auto& sub : substitution)
        {
            NodeList[sub.first - 1].to.push_back(num);
            NodeList.emplace_back(sub.second, num, sub.first - 1, sub.first + 1);
            NodeList[num + 1].income.push_back(num);
            ++num;
        }


    }
};


#endif
