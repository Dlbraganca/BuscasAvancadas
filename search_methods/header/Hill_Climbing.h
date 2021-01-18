
#ifndef HILL_CLIMBING_H
#define HILL_CLIMBING_H
#include<vector>
#include<chrono>
#include<random>
#include<algorithm>
#include"../../problem/puzzle.cpp"

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
};
#endif
