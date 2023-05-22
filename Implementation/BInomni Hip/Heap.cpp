#include "Heap.h"

Heap::Heap()
{
    head = nullptr;
    rootTail = nullptr;
}

Heap::Heap(int k)
{
    head = new Node(nullptr, nullptr, nullptr, k, 0);
    rootTail = new Node(nullptr, nullptr, nullptr, k, 0);
}

Heap::Heap(Node* p)
{
    head = p;
    rootTail = p;
}

void Heap::binomialLink(Node* y, Node* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->incrementDegree();
}

void Heap::insertFromBehind(Node* p)
{
    //prazno
    if (rootTail == nullptr)
    {
        head = p;
        rootTail = p;
        return;
    }

    this->rootTail->sibling = p;
    this->rootTail = this->rootTail->sibling;
}

Heap* Heap::mergeBinomialHeaps(Heap* x, Heap* y)
{
    /*if (x->head == nullptr)
    {
        return y;
    }
    if (y->head == nullptr)
    {
        return x;
    }*/

    Node* ptr;
    Heap* heap = new Heap();

    Node* ptrx = x->head;
    Node* ptry = y->head;
    Node* pom1, * pom2;
    while (ptrx != nullptr && ptry != nullptr)
    {
        if (ptrx->getDegree() == ptry->getDegree())
        {
            if (ptrx->getKey() <= ptry->getKey())
            {
                pom1 = ptrx;
                ptrx = ptrx->sibling;
                pom2 = ptry;
                ptry = ptry->sibling;
                heap->insertFromBehind(pom1);
                heap->insertFromBehind(pom2);
            }
            else
            {
                pom1 = ptrx;
                ptrx = ptrx->sibling;
                pom2 = ptry;
                ptry = ptry->sibling;
                heap->insertFromBehind(pom2);
                heap->insertFromBehind(pom1);
            }
        }
        else if (ptrx->getDegree() < ptry->getDegree())
        {
            pom1 = ptrx;
            ptrx = ptrx->sibling;
            heap->insertFromBehind(pom1);
        }
        else    //ptrx->Degree > ptry->Degree
        {
            pom1 = ptry;
            ptry = ptry->sibling;
            heap->insertFromBehind(pom1);
        }

    }

    if (ptrx == nullptr)
    {
        heap->insertFromBehind(ptry);
        x->head = nullptr;
    }
    else if (ptry == nullptr)
    {
        heap->insertFromBehind(ptrx);
        y->head = nullptr;
    }

    return heap;
}

Node* Heap::findMinimumKey()
{
    if (this->head == nullptr)
    {
        return nullptr;
    }

    Node* ptr = this->head;
    Node* ret = this->head;
    int min = ptr->getKey();
    while (ptr != nullptr)
    {
        if (ptr->getKey() < min)
        {
            ret = ptr;
            min = ptr->getKey();
        }

        ptr = ptr->sibling;
    }

    return ret;
}

Heap* Heap::binomialHeapUnion(Heap* h1, Heap* h2)
{
    Heap* heap = new Heap();

    heap = mergeBinomialHeaps(h1, h2);

    if (heap->head == nullptr)
    {
        return nullptr;
    }

    Node* prevx = nullptr;
    Node* x = heap->head;
    Node* nextx = x->sibling;
    while (nextx != nullptr)
    {
        //1,2
        if ((x->getDegree() != nextx->getDegree()) || (nextx->sibling != nullptr
            && nextx->sibling->getDegree() == x->getDegree()))
        {
            prevx = x;  
            x = nextx;
        }
        else    //3
        {
            if (x->getKey() <= nextx->getKey())
            {
                x->sibling = nextx->sibling;
                binomialLink(nextx, x);
            }
            else
            {    
                    if (prevx == nullptr)
                    {
                        heap->head = nextx;
                    }
                    else
                    {
                        prevx->sibling = nextx;
                    }

                    binomialLink(x, nextx);
                    x = nextx;
                
            }
        }
        nextx = x->sibling;
    }

    return heap;
}

Heap* Heap::binomialHeapInsert(Node* p)
{
    if (p->getKey() < 0)
    {
        std::cout << "Negativan je broj elementa" << std::endl;
        return this;
    }

    Heap* heapX = new Heap(p);
    Heap* heapPrim;
    heapPrim= binomialHeapUnion(this, heapX);
    
    return heapPrim;
}

void Heap::removeRootWithoutDelete(Node* p)
{
    if (head == nullptr)
    {
        return;             //nema sta da se uklanja
    }
    if (head->sibling == nullptr && p == head)          //samo jedan element
    {
        head = nullptr;
        rootTail = nullptr;
        return;
    }
    if (p == head)  //uklanja se prvi element, koji nije jedini
    {
        head = p->sibling;
        return;
    }

    Node* ptr = head;
    while (ptr->sibling != p)
    {
        ptr = ptr->sibling;
    }
    if (p->sibling == nullptr)
    {
        rootTail = ptr;
    }

    ptr->sibling = p->sibling;

}

void Heap::insertFromHead(Node* p)
{
    if (head == nullptr)
    {
        p->sibling = head;
        head = p;
        rootTail = p;
        return;
    }

    p->sibling = head;
    head = p;
}

Heap* Heap::extractMin()
{
    if (head == nullptr)
    {
        return nullptr;
    }

    Node* min = findMinimumKey();
    removeRootWithoutDelete(min);
    
    Heap* heap = new Heap();
    Node* ptr = min->child;
    Node* ptrAdv;
    while (ptr != nullptr)
    {
        min->child = ptr->sibling;
        ptr->parent = nullptr;
        heap->insertFromHead(ptr);

        ptr = min->child;
    }


    delete min;

    return binomialHeapUnion(this, heap);
}

void Heap::exchangeKeys(Node* p1, Node* p2)
{
    int pom = p2->getKey();
    p2->setKey(p1->getKey());
    p1->setKey(pom);
}

void Heap::decreaseKey(Node* x, int key)
{
    if (key > x->getKey())
    {
        std::cout << "key je veci od key-a datog cvora" << std::endl;
        return;
    }

    x->setKey(key);
    Node* y = x;
    Node* p = y->parent;
    while (p != nullptr && y->getKey() < p->getKey())
    {
        exchangeKeys(p, y);

        y = p;
        p = p->parent;
    }
}

Heap* Heap::deleteKey(Node* p)
{
    this->decreaseKey(p, -1);
    return this->extractMin();
}

Heap::~Heap()
{
    while (this->head != nullptr)
    {
        this->extractMin();
    }
}