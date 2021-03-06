#include"./header/Hill_Climbing.h"


	HillClimbing::HillClimbing(Puzzle Problem) {
		problem = Problem;
		result = Main();
	}

	HillClimbing::~HillClimbing() {};
	
	Puzzle HillClimbing::get_result() {
		return result;
	}

	bool HillClimbing::CompareHeuristics(Puzzle& a, Puzzle& b) {
		return a.get_heuristic() < b.get_heuristic();
	}

	Puzzle HillClimbing::HighestValue(Puzzle current) { // funcao que retorna o maior valor disponivel

		std::vector<int> Movements;
		std::vector<int> lastMovements;
		std::vector<Puzzle> states;

		Movements = current.get_possibleMovements(); //recebe lista de movimentos possiveis

		for (unsigned int i = 0; i < Movements.size(); i++) //cria um vector com os novos estados gerados
		{
			Puzzle temporary(current, Movements[i]); //cria novo vestado executando o movimendo 
			states.push_back(temporary); //adiciona no vetor de possibilidades
		}
		size_t bestPosition = 0;
		double bestHeuristic = states[0].get_heuristic();

		for (size_t i = 0; i < states.size(); i++)
		{
			if (states[i].get_heuristic() > bestHeuristic)
			{
				bestPosition = i;
			}
		}
		return states[bestPosition];		
	}

	Puzzle HillClimbing::Main() {

		clock_t tbegin = clock(), tend;
		Puzzle current = problem; //define a corrente como estado inicial
		Puzzle neighbor;
		int contador = 0;
		bool loopControl = true;

		while (loopControl)
		{
			contador++;
			neighbor = HighestValue(current);
			if (neighbor.get_heuristic() < current.get_heuristic())
			{
				loopControl = false;
			}
			current = neighbor;
		}
		tend = clock() - tbegin;
		std::cout << "\nTEMPO MEDIO DE ITERACAO: " << tend / contador << std::endl;
		std::cout << "TEMPO TOTAL DE EXECUCAO: " << tend << std::endl;
		std::cout << "NUMERO DE ITERACOES: " << contador << std::endl;
		std::cout << "MEMORIA UTILIZADA: " << get_memory() << std::endl;
		return current;
	}