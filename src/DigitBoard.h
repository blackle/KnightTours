#pragma once
#include "DigitCell.h"
#include <iostream>

class Solver;

class DigitBoard {
public:
	explicit DigitBoard(int width, int height, Solver* s);

	int width() const;
	int height() const;

	DigitCell at(int i, int j) const;

	friend std::ostream& operator<<(std::ostream& os, const DigitBoard& db);

private:
	const int m_width;
	const int m_height;
	Solver* m_solver;
	std::vector<DigitCell> m_cells;
};
