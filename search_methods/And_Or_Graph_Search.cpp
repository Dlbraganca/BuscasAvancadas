#include"./header/And_Or_Graph_Search.h"

	AndOrGraphSearch::AndOrGraphSearch(Puzzle PROBLEM) {
		problem = PROBLEM;
		std::vector<Puzzle> path;
		PuzzleTree newPlan();
		Or_Search(problem, problem, path);
	}
	AndOrGraphSearch::~AndOrGraphSearch(){};

	bool AndOrGraphSearch::State_on_path(Puzzle state, std::vector<int> path) {
		
		Puzzle newState = problem;

		for (size_t i = 0; i < path.size(); i++)
		{
			newState = Puzzle(newState, path[i]);
			if (state.is_equal(newState))
			{
				return true;
			}
		}
		return false;
	}

	bool AndOrGraphSearch::Falure(Puzzle s, std::vector<int> plan) { //retorna verdadeiro se � encontrado o objetivo e falso se nao
		
		Puzzle newState = problem;

		for (size_t i = 0; i < plan.size(); i++)
		{
			newState = Puzzle(newState, plan[i]);
		}
		return !newState.is_objetive();
	}

	std::vector<Puzzle> AndOrGraphSearch::Result(Puzzle state, std::vector<int> actions) {
		
		std::vector<Puzzle> result;
		
		for (size_t i = 0; i < actions.size(); i++)
		{
			Puzzle newState(state, actions[i]);
			result.push_back(newState);
		}
		return result;
	}

	PuzzleTree AndOrGraphSearch::Or_Search(Puzzle state, Puzzle problem, std::vector<Puzzle> path) {
		
		std::vector<int>actions = state.get_all_actions(); //retorna todas as acoes possivels (1,2,3,4)

		if (state.is_objetive())
		{
			return plan;
		}
		for (size_t i = 0; i < path.size(); i++)
		{
			if (state.is_equal(path[i]))
			{
				return {};
			}
			
		}
		//para cada acao no problema ->
		for (size_t i = 0; i < actions.size(); i++)
		{
			int action = actions[i];
			std::vector<int> movements = state.get_movements();
			movements.push_back(action);
			path.push_back(state);
			PuzzleTree newPlan = And_Search(state.possible_results(action), problem, path);
			//plan.children.push_back(newPlan);
			if (true)
			{
				Puzzle newState(state, action);
				PuzzleTree newPlan2;
				//newPlan.last = &plan;
				//newPlan2.root = newState;
				//newPlan.children.push_back(newPlan);
			}
		}
		return {};
	}

	PuzzleTree AndOrGraphSearch::And_Search(std::vector<Puzzle> states, Puzzle problem, std::vector<Puzzle> path) {
		
		
		for (size_t i = 0; i < states.size(); i++)
		{
			PuzzleTree newPlan;
			//newPlan.root = states[i];
			//.children.push_back(Or_Search(states[i], problem, path));
			if (true)
			{
				return {};
			}
		}
		return plan;
	}

	
