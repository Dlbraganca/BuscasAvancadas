#pragma once
#ifndef And_Or_Graph_Search_H
#define And_Or_Graph_Search_H
#include<vector>
#include <map>
#include"../../problem/header/puzzle.h"
#include"Puzzle_Tree.h"


class AndOrGraphSearch
{
public:

	inline AndOrGraphSearch(Puzzle PROBLEM);
	inline ~AndOrGraphSearch();

protected:

	Puzzle problem;
	PuzzleTree plan;

private:
	
	inline bool State_on_path(Puzzle state, std::vector<int> path);
	
	inline bool Falure(Puzzle s, std::vector<int> plan);
	
	inline std::vector<Puzzle> Result(Puzzle state, std::vector<int> actions);

	inline PuzzleTree Or_Search(Puzzle state, Puzzle problem, std::vector<Puzzle> path);

	inline PuzzleTree And_Search(std::vector<Puzzle> states, Puzzle problem, std::vector<Puzzle> path);

};
#endif	