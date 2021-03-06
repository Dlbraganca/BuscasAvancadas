
#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include "windows.h"
#include "psapi.h"
#include"../../problem/puzzle.cpp"
#include<stdio.h>   

class HillClimbing
{
public:

	inline HillClimbing(Puzzle Problem);

	inline ~HillClimbing();
	
	inline Puzzle get_result();

private:

	Puzzle problem;
	
	Puzzle result;

	inline bool CompareHeuristics(Puzzle& a, Puzzle& b);

	inline Puzzle HighestValue(Puzzle current);

	inline Puzzle Main();

	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};

};
#endif
