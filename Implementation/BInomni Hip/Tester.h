#pragma once
#include <random>
#include <chrono>
#include "Heap.h"
#include <fstream>

#define MIN_VALUE 0
#define MAX_VALUE 100000

class Tester
{
private:
	std::default_random_engine* generator;
	std::uniform_int_distribution<int>* distribution;

public:


	Tester();
	~Tester();

	//void performFirstCycle(Heap*);
	void performCycle(Heap*&, float*, float*, float*);
	void performTesting(std::string, Heap*&);

	long performInsertAndMeasure(Heap*& heap, Node* p);
	long performDeleteAndMeasure(Heap*& heap, Node* p);
	long performExtractAndMeasure(Heap*& heap);

	
};