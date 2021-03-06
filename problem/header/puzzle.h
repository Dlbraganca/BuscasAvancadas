#pragma once
#ifndef PUZZLE_H
#define PUZZLE_H
#include<vector>
#include<iostream>
#include<math.h>
#include<string>



class Puzzle
{
public:
	inline Puzzle();

	inline Puzzle(std::vector<std::vector<int>>TABLE, std::vector<std::vector<int>>OBJECTIVE);

	inline Puzzle(std::vector<std::vector<int>>TABLE, std::vector<std::vector<int>>OBJECTIVE, std::vector<int> Movements);
	
	inline Puzzle(Puzzle lastState, int x);

	inline Puzzle(Puzzle lastState, int x, std::string HEURSTICMETHOD);

	inline Puzzle(Puzzle PROBLEM, std::vector<int> MOVEMENTS);

	inline ~Puzzle();

	inline std::vector<int> get_possibleMovements();

	inline std::vector<std::vector<int>> get_table() ;
	inline std::vector<std::vector<int>> get_objective();
	inline std::vector<int> get_movements();
	
	inline int get_untried();

	inline bool is_objetive();

	inline bool comparaPuzzle(Puzzle outroPuzzle);
    
	inline void update_heuristic() ;

	inline double get_heuristic() ;

	inline double update_heuristic(std::string method);

	inline double get_original_heuristic() ;

	inline std::vector<std::vector<int>> Puzzle::try_action(int x);

	inline std::vector<std::vector<int>> Action(int x);

	inline int value_return(int x, int y);

	inline std::vector<int> get_position(int element);

	inline void set_possibleMovements() ;

	inline void set_unbacktracked(int LASTMovements, std::vector<std::vector<int>> LASTTABLE);

	inline std::vector<std::vector<int>> get_last_table();

	inline int get_last_movement();

	inline bool is_equal(Puzzle b);

	inline void perform_movements(std::vector<int> mov);

	inline std::vector<int>Puzzle::get_all_actions();
	
	inline std::vector <Puzzle> possible_results(int x);

	inline bool is_empty();

protected:
	std::vector<std::vector<int>> table;
	std::vector<std::vector<int>> objective;
	std::vector<int> movements;
	std::vector<int>possibleMovements;
	int lastMovements;
	std::vector<std::vector<int>> lastTable;
	double heuristicValue;
	double originalHeuristic;
	std::string heursticMethod = "max";

private:

	inline std::vector<int> FindElement(std::vector<std::vector<int>> table, int element);

	inline std::vector<int> PossibleMovements() ;

	inline double heuristic();

	inline void PrintMatrix(std::vector<std::vector<int> > a);
};

#endif
