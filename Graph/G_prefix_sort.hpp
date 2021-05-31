#ifndef _G_prefix_sort_hpp_
#define _G_prefix_sort_hpp_

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#include "G_ds.hpp"

class G_prefix_sort
{
public:
    static void show(std::vector<Node>& NodeList)
    {
        std::queue<int> Q;
        std::cout << "nodelist size: " << NodeList.size() << std::endl;
        bool visit[NodeList.size()] {false};
        Q.push(0);
        visit[0] = true;
        while(!Q.empty())
        {
            auto now_node = Q.front();
            Q.pop();
            std::cout << now_node << " ( " << NodeList[now_node].label  << " ) :  ";
            for(auto& To : NodeList[now_node].to)
            {
                std::cout << To << " ";
                if(!visit[To])
                {
                    Q.push(To);
                    visit[To] = true;
                }

            }
            std::cout << std::endl;

        }
    }

    static bool check_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
    {//NodeList[pre.id].preFix NodeList[PrefixList[i].id].label
        for(int i = 0; i < PrefixList.size(); ++i)
        {
            if(i == PrefixList.size() - 1) // last prefix
            {
                if(NodeList[PrefixList[i].id].label != NodeList[PrefixList[i-1].id].label || NodeList[PrefixList[i].id].preFix != NodeList[PrefixList[i-1].id].preFix) // Unique 
                    PrefixList[i].sorted = true;
            }
            else if(i == 0)
            {
                if(NodeList[PrefixList[i].id].label != NodeList[PrefixList[i+1].id].label || NodeList[PrefixList[i].id].preFix != NodeList[PrefixList[i+1].id].preFix) // Unique 
                    PrefixList[i].sorted = true;
            }
            else
                if((NodeList[PrefixList[i].id].label != NodeList[PrefixList[i-1].id].label || NodeList[PrefixList[i].id].preFix != NodeList[PrefixList[i-1].id].preFix) &&
                  (NodeList[PrefixList[i].id].label != NodeList[PrefixList[i+1].id].label || NodeList[PrefixList[i].id].preFix != NodeList[PrefixList[i+1].id].preFix))
                    PrefixList[i].sorted = true;
        }
    }



    static void init_split(std::vector<Node>& NodeList)
    {
        int num = NodeList.size();
        int ori_num = NodeList.size();
        for(int iter_num = 0; iter_num < ori_num; ++iter_num)
        {
            for(int i = 1; i < NodeList[iter_num].to.size(); ++i)
            {
                std::cout << "init split id: " << NodeList[iter_num].id << " to " << NodeList[iter_num].to[i] << std::endl;
                NodeList.emplace_back(NodeList[iter_num].label, NodeList[iter_num].id, NodeList[iter_num].to[i]);
                for(auto& inc : NodeList[iter_num].income)
                    NodeList[inc].to.push_back(num);
                ++num;
            }
            NodeList[iter_num].to.resize(1);
        }
    }

    static void init_prefix(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
    {
        for(int iter_node = 0; iter_node < NodeList.size(); ++iter_node)
        {
            PrefixList.emplace_back(NodeList[iter_node].label, iter_node, NodeList[iter_node].to[0], '\0');//NodeList[NodeList[iter_node].to[0]].label);
            NodeList[iter_node].preFix = std::string(1, NodeList[NodeList[iter_node].to[0]].label);
        }
        std::sort(PrefixList.begin(), PrefixList.end(), [&NodeList](Prefix a, Prefix b) {
            if(a.from == b.from)
                return NodeList[a.id].preFix < NodeList[b.id].preFix;
            else
                return a.from < b.from;
        } );
        check_sort(NodeList, PrefixList);
    }

    static void double_node(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
    {
        int prefix_num = PrefixList.size();
        int ori_prefix_num = PrefixList.size();
        for(int iter_prefix = 0; iter_prefix < ori_prefix_num; ++iter_prefix)
        {
            if(PrefixList[iter_prefix].sorted)
                continue;
            else
            {
                for(int iter_to = 1; iter_to < NodeList[PrefixList[iter_prefix].id].to.size(); ++iter_to)
                {
                    int node_num = NodeList.size();
                    int prefix_num = PrefixList.size();
                    //construct new node
                    NodeList.emplace_back(NodeList[PrefixList[iter_prefix].id].label, PrefixList[iter_prefix].id, NodeList[PrefixList[iter_prefix].id].to[iter_to]);
                    for(auto& inc : NodeList[PrefixList[iter_prefix].id].income)
                        NodeList[inc].to.push_back(node_num);
                    NodeList[node_num].preFix = NodeList[PrefixList[iter_prefix].id].preFix;
                    
                    //construct new prefix
                    PrefixList.emplace_back(NodeList[iter_prefix].label, node_num, NodeList[PrefixList[iter_prefix].id].to[iter_to], 'X');
                    PrefixList[prefix_num].rank = PrefixList[iter_prefix].rank;
                    PrefixList[prefix_num].successor = NodeList[PrefixList[iter_prefix].id].to[iter_to];//NodeList[PrefixList[iter_prefix].id].id;
                }
                NodeList[PrefixList[iter_prefix].id].to.resize(1);
                
            }
        }
    }
    static void prefix_sort(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
    {
        for(auto& prefix : PrefixList)
        {
            if(!prefix.sorted)
                prefix.rank = NodeList[prefix.successor].label + NodeList[prefix.successor].preFix;
        }
        for(auto& prefix :PrefixList)
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
        check_sort(NodeList, PrefixList);
    }


};



#endif
