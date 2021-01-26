#pragma once
#ifndef GENETIC_ABEL_H
#define GENETIC_ABEL_H
#include<vector>
#include<ctime>
#include<chrono>
#include<random> 
#include"../../problem/header/puzzle.h"

class GeneticAbel
{
public:
	inline GeneticAbel();
	inline GeneticAbel(Puzzle PROBLEM);
	inline ~GeneticAbel();
	inline Puzzle get_result();
private:
	std::vector<Puzzle> population;
	Puzzle result;
	Puzzle problem;

	inline void PrintVector(std::vector<int> x);

	inline void PrintMatrix(std::vector<std::vector<int> > a);

	inline Puzzle Reproduce(Puzzle x, Puzzle y);

	inline Puzzle Mutate(Puzzle x);

	inline std::vector<Puzzle> CreatePopulation(int deepth, int populationSize);

	inline Puzzle Main(Puzzle problem);

	inline Puzzle GeneticSearch(std::vector<Puzzle> population, int deepth, int maxTime, double pMutate, double pCrossover);
};
#endif