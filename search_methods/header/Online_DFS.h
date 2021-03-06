#pragma once
#ifndef ONLINE_DFS_H
#define ONLINE_DFS_H
#include<vector>
#include<unordered_map>
#include"../../problem/header/puzzle.h"
#include "windows.h"
#include "psapi.h"

class OnlineDFS
{
public:
	inline OnlineDFS();
	inline OnlineDFS(Puzzle PROBLEM);
	inline ~OnlineDFS();
	inline Puzzle get_result();

private:

	Puzzle problem, answer;
	std::unordered_map<std::string, Puzzle> result; //uma tabela, indexada por a��o e estado, inicialmente vazia
	std::unordered_map<std::string, std::vector<int>> untried;
	std::unordered_map<std::string, std::vector<Puzzle>> unbacktracked;
	std::vector<int> possibleMovements, lastMovements;
	int a;
	Puzzle s; //estado e a a��o anteriores, inicialmente nulos

	inline void PrintVector(std::vector<int> x);

	inline void PrintMatrix(std::vector<std::vector<int> > a);
	
	inline std::string hash_value(Puzzle a, int x);
	
	inline std::string hash_puzzle(Puzzle a);

	inline Puzzle Main();

	inline int OppositeMovement(int x);

	inline int Agent(Puzzle s1);

	SIZE_T get_memory() {

		PROCESS_MEMORY_COUNTERS_EX pmc;

		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
		SIZE_T physMemUsedByMe = pmc.WorkingSetSize;
		return physMemUsedByMe;
	};
};
#endif