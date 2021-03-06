#pragma once
#ifndef ONLINE_LOCAL_SEARCH_H
#define ONLINE_LOCAL_SEARCH_H
#include<vector>
#include<unordered_map>
#include"../../problem/header/puzzle.h"
#include <iostream>
#include <stdlib.h>  
#include <math.h>
#include "windows.h"
#include "psapi.h"

class OnlineLocalSearch
{
public:
	inline OnlineLocalSearch() {};
	inline OnlineLocalSearch(Puzzle PROBLEM);
	inline ~OnlineLocalSearch();
	inline Puzzle get_result();

private:
	Puzzle problem, answer;
	std::unordered_map<std::string, Puzzle> result; //uma tabela, indexada por a��o e estado, inicialmente vazia
	std::unordered_map<std::string, double> H;
	//std::unordered_map<std::string, std::vector<Puzzle>> unbacktracked;
	//std::stack <Puzzle> untriedS;
	//std::stack <Puzzle> untriedS1;
	//std::stack <Puzzle> unbacktrackedS;
	//std::stack <Puzzle> unbacktrackedS1;
	//std::unordered_map <unsigned int, Puzzle> unbacktrackedS; //uma tabela que lista, para cada estado visitado, os retrocessos ainda n�o tentados
	//std::unordered_map <unsigned int, Puzzle> unbacktrackedS1; //uma tabela que lista, para cada estado visitado, os retrocessos ainda n�o tentados
	//std::unordered_map <unsigned int, Puzzle> untriedS; //uma tabela que lista, para cada estado visitado, as a��es ainda n�o tentadas
	//std::unordered_map <unsigned int, Puzzle> untriedS1; //uma tabela que lista, para cada estado visitado, as a��es ainda n�o tentadas
	std::vector<int> possibleMovements, lastMovements;
	int a; Puzzle s; //estado e a a��o anteriores, inicialmente nulos

	inline void PrintVector(std::vector<int> x);

	inline void PrintMatrix(std::vector<std::vector<int> > a);

	inline std::string hash_value(Puzzle a, int x);
	
	inline std::string hash_puzzle(Puzzle a);

	inline Puzzle Main();

	inline int OppositeMovement(int x);

	inline double LRTA_COST(Puzzle s, int a, Puzzle s1, std::unordered_map<std::string, double> H);

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