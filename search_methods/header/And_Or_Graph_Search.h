#pragma once
#ifndef And_Or_Graph_Search_H
#define And_Or_Graph_Search_H
#include<vector>
#include"../../problem/header/puzzle.h"

class AndOrGraphSearch
{
public:

	inline AndOrGraphSearch(Puzzle PROBLEM);
	inline ~AndOrGraphSearch();
protected:

	Puzzle problem;

private:
	
	inline bool State_on_path(Puzzle state, std::vector<int> path);
	
	inline bool Falure(Puzzle s, std::vector<int> plan);
	
	inline std::vector<Puzzle> Result(Puzzle state, std::vector<int> actions);

	inline std::vector<int> Or_Search(Puzzle state, Puzzle problem, std::vector<int> path);

	inline std::vector <Puzzle> And_Search(std::vector<std::vector<int>> states, Puzzle problem, std::vector<int> path);
};
#endif