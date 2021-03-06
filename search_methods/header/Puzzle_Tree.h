#pragma once
#include"../../problem/header/puzzle.h"
#include <vector>
#include <unordered_map>

class PuzzleTree
{
public:

	inline PuzzleTree();

	inline ~PuzzleTree();

	inline Puzzle get_father(Puzzle x);

	inline Puzzle get_root();

	inline int get_deepth() { return maxDeepth; };
	
	inline void delete_member(Puzzle x);

	inline void insert(Puzzle member);

	inline std::vector<Puzzle> get_children(Puzzle x);

private:

	std::unordered_map<std::string, Puzzle> tree;
	int maxDeepth = 0;

	inline std::string hash_key(std::vector<int> x);
};
