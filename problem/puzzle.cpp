#include"./header/puzzle.h"

	Puzzle::Puzzle() {};

	Puzzle::Puzzle(std::vector<std::vector<int>>TABLE, std::vector<std::vector<int>>OBJECTIVE) //contrutor da classe 
	{
		table = TABLE;
		objective = OBJECTIVE;
		if (table[0][0] != 11)
		{
			//heuristicValue = -1 * heuristic() - 1 * movements.size();
			heuristicValue = -1 * heuristic();
		}
	}

	Puzzle::Puzzle(std::vector<std::vector<int>>TABLE, std::vector<std::vector<int>>OBJECTIVE, std::vector<int> MOVEMENTS) //contrutor da classe 
	{
		table = TABLE;
		objective = OBJECTIVE;
		movements = MOVEMENTS;
		if (table[0][0] != 11)
		{
			heuristicValue = -1 * heuristic();
		}
		std::cout <<"heuristica: " << heuristicValue << std::endl;

	}

	Puzzle::Puzzle(Puzzle lastState, int x) {
		table = lastState.get_table();
		objective = lastState.get_objective();
		movements = lastState.get_movements();
		movements.push_back(x);
		table = Action(x);
		if (table[0][0] != 11)
		{
			heuristicValue = -1 * heuristic();
		}
	}

		Puzzle::Puzzle(Puzzle lastState, int x, std::string HEURSTICMETHOD) {
		table = lastState.get_table();
		objective = lastState.get_objective();
		movements = lastState.get_movements();
		heursticMethod = HEURSTICMETHOD;
		movements.push_back(x);
		table = Action(x);
		if (table[0][0] != 11 || heursticMethod == "max")
		{
			heuristicValue = -1 * heuristic();
		}
		else
		{
			heuristicValue = heuristic();
		}
		
	}

	Puzzle::~Puzzle() {};

	std::vector<int> Puzzle::get_possibleMovements() {
		if (possibleMovements.empty())
		{
			return PossibleMovements();
		}
		else
		{
			return possibleMovements;
		}
	}

	std::vector<std::vector<int>> Puzzle::get_table() {
		return table;
	}

	std::vector<std::vector<int>> Puzzle::get_objective() {
		return objective;
	}

	std::vector<int> Puzzle::get_movements() {
		return movements;
	}

	int Puzzle::get_untried() {
		// if (possibleMovements.empty())
		// {
		// 	return NULL; //sem movementsos possiveis 
		// }
		int x = possibleMovements.back();
			possibleMovements.pop_back();
			return x;
	}

	bool Puzzle::is_objetive() {
		for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].size(); j++)
			{
				if (table[i][j] != objective[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

    bool Puzzle::comparaPuzzle(Puzzle outroPuzzle){
        for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].size(); j++)
			{
				if (table[i][j] != outroPuzzle.get_table()[i][j])
				{
					return false;
				}
			}
		}
		return true;
    }
    
	void Puzzle::update_heuristic(double value) {
		heuristicValue = -1*value;
	}

	double Puzzle::get_heuristic() {

		//std::cout << "\nheuristica: " << double(1 / (heuristic() + 0.01));
		//return double(1/ (heuristic() + 0.01));
		return heuristicValue;
	}

	double Puzzle::get_original_heuristic() { return-1* double(movements.size()) -1*heuristic(); }

	std::vector<std::vector<int>> Puzzle::Action(int x) { //funcao que retorna o estado a partir de uma ação
		int aux1, aux2;
		std::vector<int> position;
		std::vector<std::vector<int>> result = table;
		position = FindElement(table, 0);
		if (x == 1) { //esquerda	
			aux1 = result.at(position[0]).at(position[1]);
			aux2 = result.at(position[0]).at(position[1] - 1);
			result.at(position[0]).at(position[1]) = aux2;
			result.at(position[0]).at(position[1] - 1) = aux1;
		}
		if (x == 2) { //direita
			aux1 = result.at(position[0]).at(position[1]);
			aux2 = result.at(position[0]).at(position[1] + 1);
			result.at(position[0]).at(position[1]) = aux2;
			result.at(position[0]).at(position[1] + 1) = aux1;
		}
		if (x == 3) { // cima
			aux1 = result.at(position[0]).at(position[1]);
			aux2 = result.at(position[0] - 1).at(position[1]);
			result.at(position[0]).at(position[1]) = aux2;
			result.at(position[0] - 1).at(position[1]) = aux1;
		}
		if (x == 4) { //baixo
			aux1 = result.at(position[0]).at(position[1]);
			aux2 = result.at(position[0] + 1).at(position[1]);
			result.at(position[0]).at(position[1]) = aux2;
			result.at(position[0] + 1).at(position[1]) = aux1;
		}
		return result;
	}

	int Puzzle::value_return(int x, int y) {
		return table[x][y];
	}

	std::vector<int> Puzzle::get_position(int element) { //funcao retorna a posicao de um elemnto na mesa
		std::vector<int> position;
		for (unsigned int i = 0; i < table.size(); i++) {
			for (unsigned int j = 0; j < table[i].size(); j++) {
				if (table[i][j] == element) {
					position.clear();
					position.push_back(i);
					position.push_back(j);
					break;
				}
			}
		}
		return position;
	}

	void Puzzle::set_possibleMovements() { possibleMovements = PossibleMovements(); }

	void Puzzle::set_unbacktracked(int LASTMovements, std::vector<std::vector<int>> LASTTABLE) {
		lastMovements = LASTMovements;
		lastTable = LASTTABLE;
	}

	std::vector<std::vector<int>> Puzzle::get_last_table() {
		return lastTable;
	}

	int Puzzle::get_last_movement() {
		return movements.back();
	}

	bool Puzzle::is_equal(Puzzle b) {
		for (size_t i = 0; i < table.size(); i++)
		{
			for (size_t j = 0; j < table[i].size(); j++)
			{
				if (table[i][j] != b.get_table()[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}

	void Puzzle::perform_movements(std::vector<int> mov) {
		for (size_t i = 0; i < mov.size(); i++)
		{
			try
			{
				table = Action(mov[i]);
			}
			catch (const std::exception&)
			{
				table = { {11,11,11},{11,11,11},{11,11,11} };
				heuristicValue = -1000000000;
				break;
			}
		}
		if (table[0][0] != 11)
		{
			movements = mov;
			heuristicValue = -1 * heuristic() - 1 * movements.size();
		}
	}

	std::vector<int> Puzzle::FindElement(std::vector<std::vector<int>> table, int element) { //funcao retorna a posicao de um elemnto na mesa
		std::vector<int> position;
		for (unsigned int i = 0; i < table.size(); i++) {
			for (unsigned int j = 0; j < table[i].size(); j++) {
				if (table[i][j] == element) {
					position.clear();
					position.push_back(i);
					position.push_back(j);
					break;
				}
			}
		}
		return position;
	}

	std::vector<int> Puzzle::PossibleMovements() { //funcao retorna avalia o estado e retorna um vetor contendo todas as posicoes possiveis 
		
		possibleMovements.clear();

		std::vector<int> position;

		position = FindElement(table, 0);
		if (position[0] == 0) {
			if (position[1] == 0) {
				possibleMovements.push_back(2);
				possibleMovements.push_back(4);

				return possibleMovements;
			}
			if (position[1] == 2) {
				possibleMovements.push_back(1);
				possibleMovements.push_back(4);
				return possibleMovements;
			}
			else {
				possibleMovements.push_back(1);
				possibleMovements.push_back(2);
				possibleMovements.push_back(4);
				return possibleMovements;
			}
		}
		if (position[0] == 2) {
			if (position[1] == 0) {
				possibleMovements.push_back(2);
				possibleMovements.push_back(3);
				return possibleMovements;
			}
			if (position[1] == 2) {
				possibleMovements.push_back(1);
				possibleMovements.push_back(3);
				return possibleMovements;
			}
			else {
				possibleMovements.push_back(1);
				possibleMovements.push_back(2);
				possibleMovements.push_back(3);
				return possibleMovements;
			}
		}
		if (position[1] == 0) {
			possibleMovements.push_back(2);
			possibleMovements.push_back(3);
			possibleMovements.push_back(4);
			return possibleMovements;
		}
		if (position[1] == 2) {
			possibleMovements.push_back(1);
			possibleMovements.push_back(3);
			possibleMovements.push_back(4);
			return possibleMovements;
		}
		possibleMovements.push_back(1);
		possibleMovements.push_back(2);
		possibleMovements.push_back(3);
		possibleMovements.push_back(4);
		return possibleMovements;
	}

	double Puzzle::heuristic() { //heuristica do problema
		std::vector<int>  a, b;
		int k = 0;


		for (unsigned int i = 0; i < objective.size(); i++) {
			for (unsigned int j = 0; j < objective[i].size(); j++) {
				if (table[i][j] != 0)
				{
					a = FindElement(table, table[i][j]);
					b = FindElement(objective, table[i][j]);;
					k = k + abs(a[0] - b[0]) + abs(a[1] - b[1]);
				}
			}
		}
		return k;
	}

	void Puzzle::PrintMatrix(std::vector<std::vector<int> > a) {
		for (unsigned int i = 0; i < a.size(); i++) {
			for (unsigned int j = 0; j < a[i].size(); j++) {
				std::cout << a[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
