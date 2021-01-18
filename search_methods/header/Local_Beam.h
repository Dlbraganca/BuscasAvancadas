#pragma once
#ifndef LOCAL_BEAM_H
#define LOCAL_BEAM_H
#include<vector>
#include<algorithm>
#include"../../problem/header/puzzle.h"


class LocalBeam
{
public:

	inline LocalBeam();
	inline LocalBeam(Puzzle Problem);
	inline ~LocalBeam();
	inline Puzzle get_result();

private:
	Puzzle problem;
	Puzzle result;
	inline Puzzle Main(Puzzle current);

};
#endif