﻿#include"./header/GeneticAbel.h"

GeneticAbel::GeneticAbel() {};
GeneticAbel::GeneticAbel(Puzzle PROBLEM) {
	problem = PROBLEM;
	result = Main(problem);
}
GeneticAbel::~GeneticAbel() {};

Puzzle GeneticAbel::get_result() {
	return result;
}
void GeneticAbel::PrintVector(std::vector<int> x) {
	for (int i = 0; i < x.size(); i++)
	{
		std::cout << x[i];
	}
	std::cout << std::endl;
}

void GeneticAbel::PrintMatrix(std::vector<std::vector<int> > a) {
	for (unsigned int i = 0; i < a.size(); i++) {
		for (unsigned int j = 0; j < a[i].size(); j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

Puzzle GeneticAbel::Reproduce(Puzzle x, Puzzle y) {

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::vector<int> newMoviments;
	std::vector<int> x1 = x.get_movements();
	std::vector<int> x2 = x.get_movements();
	std::vector<int> y1 = y.get_movements();
	std::vector<int> y2 = y.get_movements();
	int Nx = x.get_movements().size();
	int Yx = x.get_movements().size();
	int min = Nx;
	int max = Yx;
	if (Nx > Yx)
	{
		min = Yx;
		max = Nx;
	}
	for (size_t i = 0; i < min; i++)
	{
		std::uniform_real_distribution <double> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
		double r = distribution(generator);
		if (r >= 0.5)
		{
			if (x1.size() > i)
			{
				newMoviments.push_back(x1[i]);
			}
			else
			{
				newMoviments.push_back(0);
			}
		}
		else
		{
			if (y1.size() > i)
			{
				newMoviments.push_back(y1[i]);
			}
			else
			{
				newMoviments.push_back(0);
			}
		}
	}
	Puzzle child1(x.get_table(), x.get_objective(), newMoviments);
	newMoviments.clear();
	for (size_t i = 0; i < max; i++)
	{
		if (i > x2.size() - 1)
		{
			x2.push_back(0);
		}
		if (i > y2.size() - 1)
		{
			y2.push_back(0);
		}
	}
	std::uniform_real_distribution <double> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
	double r = distribution(generator);
	for (size_t i = 0; i < max; i++)
	{
		if (r >= 0.5)
		{
			newMoviments.push_back(x2[i]);
		}
		else
		{
			newMoviments.push_back(y2[i]);
		}
	}
	Puzzle child2(x.get_table(), x.get_objective(), newMoviments);
	r = distribution(generator);
	if (r >= 0.5)
	{
		return child1;
	}
	else
	{
		return child2;
	}
	return child2;
}

Puzzle GeneticAbel::Mutate(Puzzle x) {

	int vectorPosition, moviment;
	std::vector<int> possibleMovements = x.get_possibleMovements();
	int value;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution <double> distribution(0, 1); // cria uma distribuicao uniforme com os valores min e max 
	double r = distribution(generator);
	if (r >= 0.5)
	{
		std::uniform_int_distribution <int> distribution_1(0, possibleMovements.size() - 1); // cria uma distribuicao uniforme com os valores min e max 
		int choosenMovement = distribution(generator);
		x.Action(choosenMovement);
	}
	else
	{
		x.get_movements().pop_back();
		x.perform_movements(x.get_movements());
	}
	return x;
}

std::vector<Puzzle> GeneticAbel::CreatePopulation(int deepth, int populationSize) {

	std::vector<Puzzle> population;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	while (population.size() < populationSize) //cria a populacao
	{
		Puzzle newPerson = problem;

		for (unsigned int j = 0; j < deepth; j++)// cria a partir do estado inicial uma sequencia de movimentos aelatorios validos
		{
			std::vector<int> movements = newPerson.get_possibleMovements();
			std::uniform_int_distribution <int> distribution(0, movements.size() - 1);
			newPerson = Puzzle(newPerson, movements[distribution(generator)]);
		}
		population.push_back(newPerson); //insere essa sequencia de movimenos
	}
	return population;
}

Puzzle GeneticAbel::Main(Puzzle problem) {
	std::vector<int> newMoviments;
	std::vector<Puzzle> newPopulation;
	std::vector<Puzzle> population;
	Puzzle x, y;
	Puzzle child;
	int randNum;
	Puzzle bestChild;
	int fitness = -10000;
	clock_t tbegin = clock(), tnow = 0;
	int populationSize = 20;
	int deepth = 5;
	double pMutate = 0.05;
	double pCrossover = 0.8;
	int searchTime = 10000000;//temo maximo da busca
	int maxTime = 1000;//tempo maximo da busca por cada profundidade

	Puzzle result = problem;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	while (!result.is_objetive() && (tnow - tbegin) < searchTime)
	{
		population = CreatePopulation(deepth, populationSize);
		result = GeneticSearch(population, deepth, maxTime, pMutate, pCrossover);
		population.clear();
		std::cout << "-------MELHOR RESULTADO-----------\n";
		PrintMatrix(result.get_table());
		std::cout << "---------MOVIMENTOS---------\n";
		PrintVector(result.get_movements());
		std::cout << "--------HEURISTICA--------\n" << result.get_heuristic() << std::endl;
		deepth++;
		tnow = clock();
	}
	return result;
}

Puzzle GeneticAbel::GeneticSearch(std::vector<Puzzle> population, int deepth, int maxTime, double pMutate, double pCrossover) {
	std::vector<int> newMoviments;
	std::vector<Puzzle> newPopulation;
	Puzzle x, y;
	Puzzle child;
	int randNum;
	Puzzle bestChild;
	int fitness = -10000;
	clock_t tbegin;
	tbegin = clock(); // get  begin time
	unsigned int populationSize = 20;
	int bestHeuristic = 1000;
	int bestIndividual = 0;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);

	while (int(difftime(clock(), tbegin)) < maxTime) //enquanto o tempo for maior que o estipulado
	{
		//	while (population.size() < 20)
		//	{
		//		for (unsigned int j = 0; j < deepth; j++)
		//		{
		//			std::uniform_int_distribution <int> distribution(1, 4); // cria uma distribuicao normal com os valores min e max 
		//			newMoviments.push_back(distribution(generator));
		//		}
		//		Puzzle newPerson = problem;
		//		newPerson.perform_movements(newMoviments);
		//		if (newPerson.get_table()[0][0] != 11)
		//		{
		//			population.push_back(newPerson);
		//			newPerson.~newPerson();
		//		}
		//		newMoviments.clear();
		//	}
			/// <abel>
		std::vector<Puzzle> selectedPopulation;
		for (size_t i = 0; i < population.size(); i++)
		{
			std::uniform_int_distribution <int> distribution(0, population.size() - 1); // cria uma distribuicao uniforme com os valores min e max 
			randNum = distribution(generator); //gera o n�mero aleatorio
			x = population[randNum]; //seleciona um individuo aleatorio da populacao
			randNum = distribution(generator); //gera o n�mero aleatorio
			y = population[randNum]; //seleciona um individuo aleatorio da populacao
			if (x.get_heuristic() > y.get_heuristic())
			{
				selectedPopulation.push_back(x);
			}
			else
			{
				selectedPopulation.push_back(y);
			}
		}
		/// </abel>

		for (size_t i = 0; i < population.size(); i++)
		{

			std::uniform_int_distribution <int> distribution(0, selectedPopulation.size() - 1); // cria uma distribuicao uniforme com os valores min e max 
			randNum = distribution(generator); //gera o n�mero aleatorio
			x = selectedPopulation[randNum]; //seleciona um individuo aleatorio da populacao
			randNum = distribution(generator); //gera o n�mero aleatorio
			y = selectedPopulation[randNum]; //seleciona um individuo aleatorio da populacao
			//selecao pro roleta ou amostragem aleatoria universal
			//selecao por torneio ->melhor pro Abel
			std::uniform_real_distribution<double>realDist(0, 1);; //valores inteiros de 0 a 100%
			double r = realDist(generator);

			if (r <= pCrossover) //probabilidade de 10% de ocorrer uma muta��o
			{
				child = Reproduce(x, y);
			}
			else
			{
				r = realDist(generator);
				if (r <= 0.5)
				{
					child = x;
				}
				else
				{
					child = y;
				}
			}
			/*std::cout << "-------NOVO FILHO-----------\n";
			PrintMatrix(child.get_table());
			std::cout << "---------MOVIMENTOS---------\n";
			PrintVector(child.get_movements());
			std::cout << "--------HEURISTICA--------\n" << child.get_heuristic() << std::endl;*/
			r = realDist(generator); //valores inteiros de 0 a 100%

			if (randNum <= pMutate) //probabilidade de 10% de ocorrer uma muta��o
			{
				child = Mutate(child);
			}
			if (child.get_heuristic() > fitness) // salva o melhor estado gerado
			{
				bestChild = child;
				fitness = child.get_heuristic();
			}

			if (fitness == 0) //se chegar no estado objetivo retorna o estado
			{
				return bestChild;
			}

			newPopulation.push_back(child); //caso nao adiciona esse novo filho na populacao gerada
		}
		bestHeuristic = population[0].get_heuristic();
		for (size_t i = 0; i < population.size(); i++)
		{
			if (population[i].get_heuristic() > bestHeuristic)
			{
				bestIndividual = i;
			}
		}
		int worseHeuristic = newPopulation[0].get_heuristic();
		size_t worseIndividual = 0;
		for (size_t i = 0; i < newPopulation.size(); i++)
		{
			if (newPopulation[i].get_heuristic() < worseHeuristic)
			{
				worseIndividual = i;
			}
		}
		newPopulation[worseIndividual] = population[bestIndividual];
		//selectedPopulation.push_back(population[bestIndividual]);
		population = newPopulation;
		newPopulation.clear();
		for (int i = 0; i < population.size(); i++)
		{
			if (population[i].get_heuristic() > bestHeuristic)
			{
				bestHeuristic = i;
			}
		}
		std::cout << "-------NOVO FILHO-----------\n";
		PrintMatrix(population[bestIndividual].get_table());
		std::cout << "---------MOVIMENTOS---------\n";
		PrintVector(population[bestIndividual].get_movements());
		std::cout << "--------HEURISTICA--------\n" << population[bestIndividual].get_heuristic() << std::endl;
	}

	return population[bestIndividual];
}