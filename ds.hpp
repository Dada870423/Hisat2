#ifndef _DS_HPP_
#define _DS_HPP_

#include <iostream>
#include <vector>
#include <string>


class Node
{
public:
    char label; // ACGT
    int id; // location in whole genome

    int to;
    
    Node(char _label, int _id, int _to) : label(_label), id(_id), to(_to) { } 
    ~Node() { }
};


class Prefix
{
public:
    char from; // ACGT
    int successor;
    int id;
    std::string rank;

    Prefix(char _from, int _id, int _successor, char _rank) : from(_from), id(_id), successor(_successor) { rank = std::string(1, _rank);  }
    ~Prefix() { }

};



class Edge
{
public:
    int from, to;
    char c_from, c_to;

    Edge(int _from, int _to, char _c_from, char _c_to) : from(_from), to(_to), c_from(_c_from), c_to(_c_to) { }
    ~Edge() { }
};


#endif
