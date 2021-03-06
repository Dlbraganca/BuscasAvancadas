#include"header/Puzzle_Tree.h"

PuzzleTree::PuzzleTree() { //criando a arvore
}

void PuzzleTree::insert(Puzzle member) {
	std::vector<int> movements = member.get_movements();
	std::string key = hash_key(movements);
	tree[key] = member;
	if (maxDeepth < movements.size())
	{
		maxDeepth = movements.size();
	}
}

PuzzleTree::~PuzzleTree() {};

Puzzle PuzzleTree::get_father(Puzzle x) { //retorna o pai do no
	std::vector<int> fatherMovements = x.get_movements();
	std::string key;
	fatherMovements.pop_back();
	key = hash_key(fatherMovements);
	return tree[key];
}

std::vector<Puzzle> PuzzleTree::get_children(Puzzle x) {
	std::vector<int> movements = x.get_movements();
	std::vector<int> possibleMovements = { 1,2,3,4 };
	std::vector<Puzzle> children;
	std::string key;
	for (size_t i = 0; i < possibleMovements.size(); i++)
	{
		std::vector<int> child = movements;
		child.push_back(possibleMovements[i]);
		key = hash_key(child);
		if (tree.find(key) != tree.end())
		{
			children.push_back(tree[key]);
		}
	}
	return children;
}

Puzzle PuzzleTree::get_root() { //retorna a raiz da arvore
	return tree["root"];
}

	std::string PuzzleTree::hash_key(std::vector<int> movements) {
		std::string key;
		if (movements.size() != 0)
		{
			for (size_t i = 0; i < movements.size(); i++)
			{
				key.push_back(movements[i]);
			}
		}
		else
		{
			key = "root";
		}
		return key;
	}

	void PuzzleTree::delete_member(Puzzle x) {
		std::vector<int> movements = x.get_movements();
		std::string key = hash_key(movements);
		tree.erase(key);
	}