#ifndef _G_prefix_sort_hpp_
#define _G_prefix_sort_hpp_

#include <iostream>
#include <queue>
#include <vector>

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

    static void init_split(std::vector<Node>& NodeList)
    {
        int num = NodeList.size();
        int ori_num = NodeList.size();
        for(int iter_num = 0; iter_num < ori_num; ++iter_num)
        {
            for(int i = 1; i < NodeList[iter_num].to.size(); ++i)
            {
                std::cout << "init split id: " << NodeList[iter_num].id << " to " << NodeList[iter_num].to[i] << std::endl;
                //Node tmp {NodeList[iter_num].label, num, NodeList[iter_num].to[i]};
                NodeList.emplace_back(NodeList[iter_num].label, num, NodeList[iter_num].to[i]);
                for(auto& inc : NodeList[iter_num].income)
                    NodeList[inc].to.push_back(num);
                ++num;
            }
            NodeList[iter_num].to.resize(1);
        }
    }

    static void init_prefix(std::vector<Node>& NodeList, std::vector<Prefix>& PrefixList)
    {
        std::queue<int> Q;
        bool visit[NodeList.size()] {false};
        Q.push(0);
        visit[0] = true;
        while(!Q.empty())
        {
            auto now_node = Q.front();
            Q.pop();
            for(auto& To : NodeList[now_node].to)
            {
                PrefixList.emplace_back(NodeList[now_node].label, now_node, To, NodeList[To].label);
                if(!visit[To])
                {
                    Q.push(To);
                    visit[To] = true;
                }

            }
        }
    }


};



#endif
