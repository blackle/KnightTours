#pragma once
#include <cryptominisat5/cryptominisat.h>
#include <vector>
#include "Variable.h"
#include <iostream>

class Solver;

class SudokuCell
{
public:
	explicit SudokuCell(Solver* s);

	Variable at(size_t i) const;
	const VariableList& all() const;
	static size_t length() { return 9; }

	uint8_t to_int() const;
	void assume(uint8_t val) const;

	Solver* solver() const;

	friend std::ostream& operator<<(std::ostream& os, const SudokuCell& cell);

private:
	Solver* m_solver;
	VariableList m_vars;
};
