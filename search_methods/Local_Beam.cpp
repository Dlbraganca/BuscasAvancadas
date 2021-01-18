#include"./header/Local_Beam.h"

	LocalBeam::LocalBeam() {}
	LocalBeam::LocalBeam(Puzzle Problem) {
		problem = Problem;
		result = Main(problem);
	}
	LocalBeam::~LocalBeam() {}

	Puzzle LocalBeam::get_result() { return result; }

	Puzzle LocalBeam::Main(Puzzle current) {

		std::vector<int> possibleMoviments;
		std::vector<int> lastMoviments;
		std::vector<Puzzle> states;
		std::vector<double> possibleHeuristics;
		Puzzle bestResult;
		double worstHeuristic = 1000000; //variavel para guardar a melhor heuristica
		double bestHeuristic = 100000;
		bool loopControl = true;

		while (loopControl)
		{
			possibleMoviments = current.get_possibleMovements();
			//size_t interator; //variavel para escolher a posicao da melhor heuristica
			for (size_t i = 0; i < possibleMoviments.size(); i++)
			{
				lastMoviments = current.get_movements(); //recebe os ultimos movimentos executados
				lastMoviments.push_back(possibleMoviments[i]); //adiciona o proximo movimento a lista
				Puzzle temporary(current.Action(possibleMoviments[i]), current.get_objective(), lastMoviments); //cria a nova classe puzzle com o proximo estado
				if (temporary.is_objetive())
				{
					loopControl = false;
					return temporary;
				}
				if (temporary.get_heuristic() <= worstHeuristic) // chega se essa � a melhor heuristica
				{
					if (states.size()> 3) //estipula o maximo de caminhos possiveis
					{
						states.erase(states.begin());
					}
					//bestHeuristic = temporary.get_heuristic(); //define a nova heuristica a ser batida
					states.push_back(temporary); // adiciona o novo estado para a lista dos possiveis estados
					std::sort(states.begin(), states.end(), [](Puzzle& a, Puzzle& b)->bool {return a.get_heuristic() > b.get_heuristic(); }); //ordena o vetor por heuristica
					worstHeuristic = states.back().get_heuristic();
				}

				if (states.size() == 0) //caso nao tenha estado com uma heuristica menor
				{
					std::cout << "RESPOSTA NAO ENCONTRADA\nMELHOR RESULTADO\n";
					return bestResult;
				}
			}
			if (states.back().get_heuristic() < bestHeuristic)
			{
				bestHeuristic = states.back().get_heuristic();
				bestResult = states.back();
			}
			current = states.back(); //pega o estado com a melhor heuristica
				//bestHeuristic = states.back().get_heuristic(); //define a nova heuristica a ser batida
			states.pop_back(); // remove ele da lista
		}
		return bestResult;
	}
