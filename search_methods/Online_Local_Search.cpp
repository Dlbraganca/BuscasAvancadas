#include"./header/Online_Local_Search.h"


	OnlineLocalSearch::OnlineLocalSearch(Puzzle PROBLEM)
	{
		problem = PROBLEM;
		answer = Main();
	}
	OnlineLocalSearch::~OnlineLocalSearch() {}
	Puzzle OnlineLocalSearch::get_result() { return answer; }

	void OnlineLocalSearch::PrintVector(std::vector<int> x) {
		//setlocale(LC_ALL, "");
		//for (unsigned int j = 0; j < x.size(); j++)
		//{
		//	if (x[j] == 1)
		//	{
		//		std::wcout << L'\u2190';
		//	}
		//	else if (x[j] == 2)
		//	{
		//		std::wcout << L'\u2192';
		//	}
		//	else if (x[j] == 3)
		//	{
		//		std::wcout << L'\u2191';
		//	}
		//	else if (x[j] == 4)
		//	{
		//		std::wcout << L'\u2193';
		//	}
		//}
		//std::cout << std::endl;
		for (unsigned int i = 0; i < x.size(); i++)
		{
			std::cout << x[i];
		}
		std::cout << std::endl;
	}

	void OnlineLocalSearch::PrintMatrix(std::vector<std::vector<int> > a) {
		for (unsigned int i = 0; i < a.size(); i++) {
			for (unsigned int j = 0; j < a[i].size(); j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	std::string OnlineLocalSearch::hash_value(Puzzle a, int x)
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
	
	std::string OnlineLocalSearch::hash_puzzle(Puzzle a)
	{
		std::string answer;
		for (size_t i = 0; i < a.get_table().size(); i++)
		{
			for (size_t j = 0; j < a.get_table()[i].size(); j++)
			{
				answer.push_back(a.get_table()[i][j]);
			};
		}
		return answer;
	}

	Puzzle OnlineLocalSearch::Main()
	{

		Puzzle current = problem;
		int moviment = 0;
		clock_t tbegin = clock(), tend;
		int count = 0;

		while (moviment != 10 && moviment != 11)
		{ 
			count++;
			//std::cout << "-----------ESTADO ATUAL-------------\n";
			//PrintMatrix(current.get_table());
			//std::cout << "-----------MOVIMENTOS-------------\n";
			//PrintVector(current.get_movements());
			//std::cout << "-----------HEURISTICA--------------\n";
			//std::cout << H[hash_puzzle(current)] << std::endl;;
			moviment = Agent(current);
			if (moviment == 10 || current.is_objetive())
			{
				return current;
			}
			else if (moviment == 11)
			{
				//std::cout << "RESPOSTA NAO ENCONTRADA\n";
				return current;
			}
			else
			{
				
				current = Puzzle (current, moviment);
				if (current.is_objetive())
				{
					tend = clock();
					std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
					std::cout << "TEMPO TOTAL DE EXECUCAO: " << tend << std::endl;
					//std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
					std::cout << "MEMORIA UTILIZADA: " << get_memory() << std::endl;
					return current;
				}
				////std::cout << "-----------PROXIMA ACAO:" << moviment << std::endl;
			}
		}
		tend = clock();
		std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
		std::cout << "TEMPO TOTAL DE EXECUCAO: " << tend << std::endl;
		//std::cout << "NUMERO DE ITERACOES: " << count << std::endl;
		std::cout << "MEMORIA UTILIZADA: " << get_memory() << std::endl;
		return current;
	}
	
	int OnlineLocalSearch::OppositeMovement(int x) {
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

	double OnlineLocalSearch::LRTA_COST(Puzzle s, int a, Puzzle s1, std::unordered_map<std::string, double> H) {
		
		double result;
		std::string hashKey;

		hashKey = hash_puzzle(s1); //cacula a chave do valor s'
		if (H.find(hashKey) == H.end()) // verifica se o valor s' ja foi indexado
		{
			result = s.get_heuristic(); //caso nao, retorna a heuristica daquele valor
			return result;
		}
		else
		{
 			//result = -1*abs(double(s.get_movements().size()) - double(s1.get_movements().size())) + H[hashKey]; //caso sim, atualiza o custo 
			result = -1*double(1) + H[hashKey];
			//std::cout << s.get_movements().size()<< "s1 size: "<< s1.get_movements().size() <<"resutlado nova heuristica: " << result << std::endl;
			return result;
		}
	}

	int OnlineLocalSearch::Agent(Puzzle s1)
	{

		std::vector<Puzzle> newStates;
		std::vector<int> possibleMovements;
		std::vector<int> lastMovements;
		std::vector<double> possibleHeuristic;
		double heuristicResult;
		double minValue = -1000000000;
		std::string hashValue;

		//Puzzle temporary;

		if (s1.is_objetive())
		{			   //testa pra saber se � o objetivo

			std::cout << "OBJETIVO\n";
			return 10; //resultado
		}
		
		hashValue = hash_puzzle(s1);
		if (H.find(hashValue) == H.end())
		{ 
			H[hashValue] = s1.get_heuristic();
		}

		if (!s.get_table().empty()) 
		{
			hashValue = hash_value(s, a);
			result[hashValue] = s1;
			s.set_possibleMovements();
			possibleMovements = s.get_possibleMovements();
			for (size_t i = 0; i < possibleMovements.size(); i++)
			{
				hashValue = hash_value(s, possibleMovements[i]);
				heuristicResult = LRTA_COST(s, possibleMovements[i], result[hashValue], H);
				if (heuristicResult > minValue) //procura o as menores heuristicas possiveis (no caso � maior pq ta invertido)
				{
					minValue = heuristicResult;
				}
			}
			hashValue = hash_puzzle(s);
			H[hash_puzzle(s)] = minValue;
		}

		possibleMovements = s1.get_possibleMovements();
		minValue = -1000000000;

		for (size_t i = 0; i < possibleMovements.size(); i++)
		{
			hashValue = hash_value(s1, possibleMovements[i]);
			heuristicResult = LRTA_COST(s1, possibleMovements[i], result[hashValue], H);
			if (heuristicResult > minValue) //procura o as menores heuristicas possiveis (no caso � maior pq ta invertido)
			{
				minValue = heuristicResult;
				a = possibleMovements[i];
			}
		}
		s = s1;
		return a;

	}