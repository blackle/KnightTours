#pragma once
#include "ChessCell.h"
#include <optional>
#include <iostream>

class Solver;

class KnightsTourPuzzle {
public:
	explicit KnightsTourPuzzle(Solver* s);

	ChessCell at(size_t i, size_t j) const;
	Solver* solver() const;

	friend std::ostream& operator<<(std::ostream& os, const KnightsTourPuzzle& kt);

private:
	Solver* m_solver;
	std::vector<ChessCell> m_cells;

	void constrain_knight_movement(int i, int j, int t, int tnew);
};
