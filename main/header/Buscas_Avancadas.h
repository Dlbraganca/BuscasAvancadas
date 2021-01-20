#ifndef BUSCAS_AVANCADAS_H
#define BUSCAS_AVANCADAS_H
#include"..\..\search_methods\Hill_Climbing.cpp"
#include"..\..\search_methods\Simulated_Annealing.cpp"
#include"..\..\search_methods\Local_Beam.cpp"
#include"..\..\search_methods\Genetic_Algorithm.cpp"
// #include"../../search_methods/header/Online_DFS.h"
// #include"../../search_methods/header/Online_Local_Search.h"
// #include"..\..\problem\header\puzzle.h"


inline void PrintVector(std::vector<int> x);

inline void PrintMatrix(std::vector<std::vector<int> > a);

inline void Answer(Puzzle a);

inline void InicialProblem(Puzzle a);

int main();

#endif
