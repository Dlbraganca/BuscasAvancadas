#pragma once
#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include<vector>
#include<chrono>
#include<random>
#include"../../problem/header/puzzle.h"
#include "windows.h"
#include "psapi.h"

class SimulatedAnnealing
{
public:

	inline SimulatedAnnealing(Puzzle PROBLEM, double INITIALTEMPETURE, double DECAY);
	inline SimulatedAnnealing(Puzzle PROBLEM);
	inline ~SimulatedAnnealing();

	inline Puzzle get_result();

private:

	Puzzle problem;
	Puzzle result;
	double tempeture = 3;
	double decay = 0.001;

	inline Puzzle RandomValue(Puzzle current);

	inline bool RandomProbability(double delE, double T);

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