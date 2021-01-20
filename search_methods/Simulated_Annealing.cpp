//#include "8puzzle.h"
#include"./header/Simulated_Annealing.h"

	SimulatedAnnealing::SimulatedAnnealing(Puzzle PROBLEM) {
		problem = PROBLEM;
		result = Main();
	}

	SimulatedAnnealing::SimulatedAnnealing(Puzzle PROBLEM, double INITIALTEMPETURE, double DECAY) {
		problem = PROBLEM;
		tempeture = INITIALTEMPETURE;
		decay = DECAY;
		result = Main();
	}
	SimulatedAnnealing::~SimulatedAnnealing() {}

	Puzzle SimulatedAnnealing::get_result() { return result; }

	Puzzle SimulatedAnnealing::RandomValue(Puzzle current) { // funcao que retorna o menor valor disponivel

		std::vector<int> movements;
		std::vector<int> lastmovements;
		std::vector<Puzzle> states;
		//unsigned int seed = clock() * 100000;
		//std::cout << "seed: " << seed << std::endl;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed); 

		movements = current.get_possibleMovements(); //recebe lista de movimentos possiveis

		for (unsigned int i = 0; i < movements.size(); i++) //cria um vector com os novos estados gerados
		{
			Puzzle temporary(current, movements[i], "min"); //cria a nova classe puzzle com o proximo estado
			states.push_back(temporary); //adiciona no vetor de possibilidades
		}
		
		std::uniform_int_distribution <int> distribution(0, movements.size()-1); // cria uma distribuicao uniforme com os valores min e max 
		int randNum = distribution(generator); //gera o n�mero aleatorio
		return states[randNum]; //retorna o movimento do numero aleatorio
	}

	bool SimulatedAnnealing::RandomProbability(double delE, double T) { // funcao que retorna o menor valor disponivel


		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 generator(seed);

		//gerar aleatorio entre 0 e 1
		std::uniform_real_distribution <> distribution(0, 1); // cria uma distribuicao normal com os valores min e max 
		double randNum = distribution(generator); //gera o n�mero aleatorio

		//gerar aleatorio entre 0 e 1 se rand <= exp pegar se nao nao pegar (se der ruim troca)
		if (randNum < exp(delE / T))
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	Puzzle SimulatedAnnealing::Main() {

		double delE;
		int x = 1;
		double bestHeuristic = problem.get_heuristic();

		Puzzle current = problem; //define a corrente como estado inicial
		Puzzle next;
		Puzzle best;
		unsigned int count = 0;

		while (tempeture > 0)
		{
			next = RandomValue(current); //funcao que retorna um estado aleatorio
			delE = next.get_heuristic() - current.get_heuristic();
			if (delE > 0.0)
			{
				current = next;
				if (current.get_heuristic() > bestHeuristic)
				{
					bestHeuristic = current.get_heuristic();
					best = current;
				}
			}
			else if (RandomProbability(delE, tempeture))
			{
				current = next;
			}
			tempeture = tempeture - decay;
			count++;
			std::cout << "\nheuristica: " << current.get_heuristic() << "-----TEMPERATURA: " << tempeture;
			std::cout << "\n NUMERO DE ESTADOS VISITADOS: " << count << std::endl;
		}
		return best;
	}
