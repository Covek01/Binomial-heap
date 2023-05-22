#pragma once
#include <iostream>

class Node
{
private:
    int key;
    int degree;

public:
    Node* parent;
    Node* child;
    Node* sibling;
    Node();
    Node(int k);
    Node(Node* parent, Node* child, Node* sibling, int key, int degree);


    //getters 
    inline int getKey()
    {
        return key;
    }
    inline int getDegree()
    {
        return degree;
    }

    //setters
    inline void setDegree(int deg)
    {
        this->degree = deg;
    }
    inline void incrementDegree()
    {
        this->degree++;
    }
    inline void setKey(int key)
    {
        this->key = key;
    }
};