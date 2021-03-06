#include"./header/Online_DFS.h"


	OnlineDFS::OnlineDFS() {}

	OnlineDFS::OnlineDFS(Puzzle PROBLEM)
	{
		problem = PROBLEM;
		answer = Main();
	}

	OnlineDFS::~OnlineDFS() {}
	
	Puzzle OnlineDFS::get_result() { return answer; }

	void OnlineDFS::PrintVector(std::vector<int> x) {
		for (int i = 0; i < x.size(); i++)
		{
			std::cout << x[i];
		}
		std::cout << std::endl;
	}

	void OnlineDFS::PrintMatrix(std::vector<std::vector<int> > a) {
		for (unsigned int i = 0; i < a.size(); i++) {
			for (unsigned int j = 0; j < a[i].size(); j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::string OnlineDFS::hash_value(Puzzle a, int x)
	{
		std::string answer;
		for (size_t i = 0; i < a.get_table().size(); i++)
		{
			for (size_t j = 0; j < a.get_table()[i].size(); j++)
			{
				answer.push_back(a.get_table()[i][j]);
			}
		}
		answer.push_back(x);
		return answer;
	}
	
	std::string OnlineDFS::hash_puzzle(Puzzle a)
	{
		std::string answer;
		std::vector <int> movements = a.get_movements();
		for (size_t i = 0; i < a.get_table().size(); i++)
		{
			for (size_t j = 0; j < a.get_table()[i].size(); j++)
			{
				answer.push_back(a.get_table()[i][j]);
			};
		}
		//for (size_t i = 0; i < movements.size(); i++)
		//{
		//	answer.push_back(movements[i]);
		//}
		return answer;
	}

	Puzzle OnlineDFS::Main()
	{
		clock_t tbegin = clock(), tend;
		size_t tmax = 150000;
		Puzzle current = problem;
		int moviment = 100;
		int count = 0;

		while (moviment != 10 && moviment != 11 )
		{
			count++;
			//std::cout << "-----------ESTADO ATUAL-------------\n";
			//PrintMatrix(current.get_table());
			//std::cout << "-----------MOVIMENTOS-------------\n";
			//PrintVector(current.get_movements());
			moviment = Agent(current);
			if (moviment == 10)
			{
				return current;
			}
			else if (moviment == 11)
			{
				//std::cout << "RESPOSTA NAO ENCONTRADA\n";
				return current;
			}
			else if (clock() - tbegin >= tmax)
			{
				tend = clock();
				std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
				std::cout << "TEMPO TOTAL DE EXECUCAO: " << tend << std::endl;
				//std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
				std::cout << "MEMORIA UTILIZADA: " << get_memory() << std::endl;
				return current;
			}
			else
			{

				current = Puzzle(current, moviment);
				////std::cout << "-----------PROXIMA ACAO:" << moviment << std::endl;
			}
		}

}

	int OnlineDFS::OppositeMovement(int x) {
		switch (x)
		{
		case 1:
		{
			return 2;
		}
		case 2:
		{
			return 1;
		}
		case 3:
		{
			return 4;
		}
		case 4:
		{
			return 1;
		}
		}
	}

	int OnlineDFS::Agent(Puzzle s1)
	{

		Puzzle temporary;

		if (s1.is_objetive())
		{			   //testa pra saber se � o objetivo
			std::cout << "OBJETIVO\n";
			return 10; //resultado
		}
		if (untried.find(hash_puzzle(s1)) == untried.end())
		{
			//std::cout << "NEW STATE\n";
			//possibleMovements = s1.get_possibleMovements();
			untried[hash_puzzle(s1)] = s1.get_possibleMovements();
			//PrintVector(untried[hash_puzzle(s1)]);
		}

		if (!s.get_table().empty())
		{
			//std::cout << "S IS NOT NULL\n";
			result[hash_value(s, a)] = s1;
			unbacktracked[hash_puzzle(s1)].push_back(s);
		}
		if (untried[hash_puzzle(s1)].empty())
		{
			//std::cout << "UNTRIED EMPTY\n";
			if (unbacktracked[hash_puzzle(s1)].empty())
			{
			//	std::cout << "UNBACKTRACKED EMPTY\n";
				return 11; //erro
			}
			else
			{
			//	std::cout << "ACTION B SUCH THAT RESULTS\n";
				Puzzle unbacktrackedState = unbacktracked[hash_puzzle(s1)].back();
				unbacktracked[hash_puzzle(s1)].pop_back();
				std::vector<int> actionsUnbacktracked = s1.get_possibleMovements();
				while (!actionsUnbacktracked.empty())
				{
					int movement = actionsUnbacktracked.back();
					actionsUnbacktracked.pop_back();
					std::string hashKey = hash_value(s1, movement);
					//Puzzle lastUnback = unbacktracked[hash_puzzle(s1)].back();
					if (result[hashKey].is_equal(unbacktrackedState))
					{
						a = movement;
						actionsUnbacktracked.clear();
					}
					else if(actionsUnbacktracked.empty())
					{
				//		std::cout << "teste\n";
					}
				}
			}
		}
		else
		{
			a = untried[hash_puzzle(s1)].back();
			untried[hash_puzzle(s1)].pop_back();
		}
		
		s = s1;

		//return OppositeMovement(a);
		return a;
		}