#pragma once
#include "SudokuCell.h"
#include <iostream>

class Solver;

class SudokuPuzzle {
public:
	explicit SudokuPuzzle(Solver* s);

	SudokuCell at(size_t i, size_t j) const;

	friend std::ostream& operator<<(std::ostream& os, const SudokuPuzzle& sp);

private:
	Solver* m_solver;
	std::vector<SudokuCell> m_cells;

	void constrain_cells(const std::vector<SudokuCell>& cells);
};
