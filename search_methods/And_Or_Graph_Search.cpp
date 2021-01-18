#include".\header\And_Or_Graph_Search.h"

	AndOrGraphSearch::AndOrGraphSearch(Puzzle PROBLEM) {
		problem = PROBLEM;
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

	std::vector<int> AndOrGraphSearch::Or_Search(Puzzle state, Puzzle problem, std::vector<int> path) {
		
		std::vector<int>actions = state.get_possibleMovements();
		std::vector < std::vector<int>>plan;
		std::vector<int> res;
		if (state.is_objetive())
		{
			return res;
		}
		if (State_on_path(state, path))
		{
			return res;
		}
		while (!actions.empty())
		{
			plan = And_Search(Result(state, actions), problem, path);
		}
		return res;
	}

	std::vector<std::vector<int>> AndOrGraphSearch::And_Search(std::vector<Puzzle> states, Puzzle problem, std::vector<int> path) {
		
		std::vector<std::vector<int>> plan;
		
		for (size_t i = 0; i < states.size(); i++)
		{
			plan[i] = Or_Search(states[i], problem, path);
			if (Falure(states[i], plan[i]))
			{
				plan.erase(plan.begin() + i);
			}
		}
		return plan;
	}
