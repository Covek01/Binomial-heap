#include "Node.h"

Node::Node()
{
    parent = nullptr;
    sibling = nullptr;
    child = nullptr;
    key = 0;
    degree = 0;
}

Node::Node(Node* parent, Node* child, Node* sibling, int key, int degree)
{
    this->parent = parent;
    this->sibling = sibling;
    this->child = child;
    this->key = key;
    this->degree = degree;
}

Node::Node(int k)
{
    this->parent = nullptr;
    this->sibling = nullptr;
    this->child = nullptr;
    this->key = k;
    this->degree = 0;
}

