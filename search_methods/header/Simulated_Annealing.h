#pragma once
#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H
#include<vector>
#include<chrono>
#include<random>
#include"../../problem/header/puzzle.h"

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
	double tempeture = 100;
	double decay = 0.999;

	inline inline Puzzle RandomValue(Puzzle current);

	inline inline bool RandomProbability(double delE, double T);

	inline inline Puzzle Main();
};
#endif