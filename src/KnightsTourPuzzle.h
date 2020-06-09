#pragma once
#include "NumberedCell.h"
#include <iostream>

class Solver;

class KnightsTourPuzzle {
public:
	explicit KnightsTourPuzzle(int width, int height, Solver* s);

	int width() const;
	int height() const;

	NumberedCell at(int i, int j) const;

	friend std::ostream& operator<<(std::ostream& os, const KnightsTourPuzzle& kt);

private:
	const int m_width;
	const int m_height;
	Solver* m_solver;
	std::vector<NumberedCell> m_cells;

	void constrain_knight_movement(int i, int j, int t, int tnew);
};
