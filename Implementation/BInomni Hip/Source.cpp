#include "Tester.h"

int main()
{
	Heap* hip = new Heap();
	Tester* tester = new Tester();

	std::string filePath10 = "F:\\labaratorijske\\BInomni Hip\\Rezultati10.txt";
	

	tester->performTesting(filePath10, hip);

	delete hip;
	delete tester;
	/*hip = hip->binomialHeapInsert(new Node(3));
	hip = hip->binomialHeapInsert(new Node(2));
	hip = hip->binomialHeapInsert(new Node(12));
	Node* p1 = new Node(10);
	hip = hip->binomialHeapInsert(p1);
	hip = hip->binomialHeapInsert(new Node(7));
	hip = hip->binomialHeapInsert(new Node(14));
	hip = hip->binomialHeapInsert(new Node(21));*/
	//hip = hip->binomialHeapInsert(15);

	//hip = hip->deleteKey(p1);
	////hip = hip->extractMin();
}