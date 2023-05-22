#include "Tester.h"


Tester::Tester()
{
	generator = new std::default_random_engine();
	distribution = new std::uniform_int_distribution<int>(MIN_VALUE, MAX_VALUE);
}

long Tester::performInsertAndMeasure(Heap*& heap,Node* p)
{
	auto pocetak = std::chrono::high_resolution_clock::now();
	heap = heap->binomialHeapInsert(p);
	auto kraj = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kraj - pocetak).count();
	return duration;
}

long Tester::performDeleteAndMeasure(Heap*& heap, Node* p)
{
	auto pocetak = std::chrono::high_resolution_clock::now();
	heap = heap->deleteKey(p);
	auto kraj = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kraj - pocetak).count();
	return duration;
}

long Tester::performExtractAndMeasure(Heap*& heap)
{
	auto pocetak = std::chrono::high_resolution_clock::now();
	heap = heap->extractMin();
	auto kraj = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kraj - pocetak).count();
	return duration;
}

void Tester::performCycle(Heap*& heap, float* vremeInsert, float* vremeDelete, float* vremeExtract)
{
	//*vremeInsert = 0;	// /8
	//*vremeDelete = 0;	// /2
	//*vremeExtract = 0;	// /2
	
	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator)));

	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator)));

	Node* p = new Node((*distribution)(*generator));
	*vremeInsert += performInsertAndMeasure(heap, p);

	*vremeDelete += performDeleteAndMeasure(heap, p);
	*vremeExtract += performExtractAndMeasure(heap);

	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator)));
	p = new Node((*distribution)(*generator));
	*vremeInsert += performInsertAndMeasure(heap, p);
	*vremeDelete += performDeleteAndMeasure(heap, p);

	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator)));
	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator)));
	*vremeExtract += performExtractAndMeasure(heap); 

	*vremeInsert += performInsertAndMeasure(heap, new Node((*distribution)(*generator))); 

	/**vremeInsert /= 8;
	*vremeExtract /= 2;
	*vremeDelete /= 2;*/

}

void Tester::performTesting(std::string path, Heap*& heap)
{
	float* del = new float(0);
	float* insert = new float(0);
	float* extract = new float(0);

	int nizOkretanja[5];
	nizOkretanja[0] = 10;
	nizOkretanja[1] = 100;
	nizOkretanja[2] = 1000;
	nizOkretanja[3] = 10000;
	nizOkretanja[4] = 100000;
	
	int i, j, k;
	int cycles = 10;
	std::ofstream* fajl = new std::ofstream(path, std::ios::trunc);
	if (fajl->is_open())
	{
		*fajl << "Vremena izvrsenja operacija:" << std::endl;
		for (i = 0; i <= 4; i++)
		{
			for (k = 1; k <= nizOkretanja[i]; k++)
			{
				this->performCycle(heap, insert, del, extract);
			}	
			*fajl << "Srednji broj nanosekundi za 1";
			for (j = 0; j <= i; j++)
			{
				*fajl << '0';
			}
			*fajl << "ciklusa:     insert:" << *insert / (8 * nizOkretanja[i])
				<< "     delete : " << *del / (2 * nizOkretanja[i]) <<
				"     extract:" << *extract / (2 * nizOkretanja[i]) << std::endl;
		}
		
		fajl->close();
	}
	else
	{
		std::cout << "Nije mogao da se otvori fajl za upis" << std::endl;
	}

}

Tester::~Tester()
{
	delete generator;
	delete distribution;
}