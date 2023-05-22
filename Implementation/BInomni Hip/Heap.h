#pragma once

#include "Node.h"

class Heap
{
public:
    Node* head;
    Node* rootTail; //ukazuje na najdesnji root, zbog merge se upotrebljava
    Heap();
    Heap(int k);
    Heap(Node* p);
    ~Heap();

    static void binomialLink(Node* y, Node* z);
    static Heap* mergeBinomialHeaps(Heap* x, Heap* y);
    void insertFromBehind(Node* p);
    Node* findMinimumKey();
    static Heap* binomialHeapUnion(Heap* h1, Heap* h2);

    Heap* binomialHeapInsert(Node* p);
    void removeRootWithoutDelete(Node* p);  //"odvezuje" jedan root iz binomnog hipa
    void insertFromHead(Node* p);

    Heap* extractMin();
    void decreaseKey(Node* p, int key);
    void exchangeKeys(Node* p1, Node* p2);
    Heap* deleteKey(Node* p);

};